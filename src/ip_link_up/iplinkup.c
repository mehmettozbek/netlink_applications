#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <net/if.h>
#include <libnetlink.h>
#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

struct iplink_req {
	struct nlmsghdr			n;
	struct ifinfomsg		i;
	char					buf[1024];
};

int main()
{
	const char *dev = NULL;
	const char *state = NULL;
	struct iplink_req req;
	struct rtnl_handle rth;
	unsigned int ifindex = 0;
	int len = 0;

	dev = "eth0";
	state = "up";
	ifindex = if_nametoindex(dev);

	if (!ifindex) {
		printf("Invalid device\n");
		exit(1);
	}

	if (strcasecmp(state,"up")) {
		printf("Invalid device state\n");
		exit(1);
	}

	len = strlen(dev);
	if(len > IF_NAMESIZE)
		printf("Interface name too long\n");

	if (rtnl_open(&rth, 0)) {
		printf("Cannot open rtnetlink\n");
		exit(1);
	}

	memset(&req, 0, sizeof(req));
	req.n.nlmsg_len		= NLMSG_LENGTH(sizeof(struct ifinfomsg));
	req.n.nlmsg_flags	= NLM_F_REQUEST;
	req.n.nlmsg_type	= RTM_NEWLINK;
	req.i.ifi_family	= AF_UNSPEC;
	req.i.ifi_index		= ifindex;
	req.i.ifi_change	|= IFF_UP;

	if(!strcasecmp(state, "up"))
		req.i.ifi_flags |= IFF_UP;
	else
		req.i.ifi_flags &= ~IFF_UP;

	addattr_l(&req.n, sizeof(req), IFLA_IFNAME, dev, len);

	if(rtnl_talk(&rth, &req.n, 0) < 0) {
		printf("Failed to talk to netlink!\n");
		exit(1);
	}

	rtnl_close(&rth);
	printf("Interface %s set %s\n", dev, state);
}
