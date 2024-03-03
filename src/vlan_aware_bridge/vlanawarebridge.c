#include <netlink/netlink.h>
#include <netlink/route/link.h>
#include <netlink/route/link/bridge.h>
#include <netlink/route/link/bridge_info.h>
#include <netlink/route/link/vlan.h>
#include <netlink/attr.h>
#include <netlink/route/rtnl.h>
#include <linux/if_bridge.h>
#include <linux/netlink.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <linux/rtnetlink.h>
#include <libnetlink.h>
#include <net/if.h>
#include <linux/if_ether.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdbool.h>
#include <asm/types.h>

struct rtnl_handle rth = { .fd = -1 };

static int add_vlan_info_range(struct nlmsghdr *n, int reqsize, __u16 vid_start, int16_t vid_end, __u16 flags) {
	
    struct bridge_vlan_info vinfo = {};
	vinfo.flags = flags;
	vinfo.vid = vid_start;
	if (vid_end != -1) {
		/* send vlan range start */
		addattr_l(n, reqsize, IFLA_BRIDGE_VLAN_INFO, &vinfo, sizeof(vinfo));
		vinfo.flags &= ~BRIDGE_VLAN_INFO_RANGE_BEGIN;

		/* Now send the vlan range end */
		vinfo.flags |= BRIDGE_VLAN_INFO_RANGE_END;
		vinfo.vid = vid_end;
		addattr_l(n, reqsize, IFLA_BRIDGE_VLAN_INFO, &vinfo, sizeof(vinfo));
	}
    else
		addattr_l(n, reqsize, IFLA_BRIDGE_VLAN_INFO, &vinfo, sizeof(vinfo));

	return 0;
}

int vlan_aware_bridge()
{

	const char *d = NULL;
	int vid = -1;
	unsigned short flags = 0;
	unsigned int ifindex = 0;
	d = "eth0";
	vid = 10;

	struct {
		struct nlmsghdr		n;
		struct ifinfomsg	ifm;
		char				buf[1024];
	} req = {
		.n.nlmsg_len	= NLMSG_LENGTH(sizeof(struct ifinfomsg)),
		.n.nlmsg_flags	= NLM_F_REQUEST,
		.n.nlmsg_type	= RTM_SETLINK,
		.ifm.ifi_family	= PF_BRIDGE,
	};
	struct rtattr *afspec;
	struct bridge_vlan_info	vinfo = {};
	/* ASSIGNMENTS */
	flags 		|= BRIDGE_FLAGS_MASTER;
	vinfo.flags |= BRIDGE_VLAN_INFO_PVID;
	vinfo.flags |= BRIDGE_VLAN_INFO_UNTAGGED;

	if (d == NULL || vid == -1) {
		fprintf(stderr, "Device and VLAN ID are required arguments.\n");
		return -1;
	}

	ifindex = if_nametoindex("eth0");
	req.ifm.ifi_index = ifindex;

	if (req.ifm.ifi_index == 0) {
		fprintf(stderr, "Cannot find bridge device \"%s\"\n", d);
		return -1;
	}

	if (vid >= 4096) {
		fprintf(stderr, "Invalid VLAN ID \"%hu\"\n", vid);
		return -1;
	}

	afspec = addattr_nest(&req.n, sizeof(req), IFLA_AF_SPEC);

	if (flags)
		addattr16(&req.n, sizeof(req), IFLA_BRIDGE_FLAGS, flags);

	add_vlan_info_range(&req.n, sizeof(req), vid, -1, vinfo.flags);
	addattr_nest_end(&req.n, afspec);

	if (rtnl_talk(&rth, &req.n, 0) < 0) {
		printf("Failed to talk to netlink\n");
		return -1;
	}

	rtnl_close(&rth);
	return 0;
}

int main()
{
	struct nl_cache *link_cache;
	struct nl_sock *sk;
	int err;
	sk = nl_socket_alloc();

	if ((err = nl_connect(sk, NETLINK_ROUTE)) < 0) {
		nl_perror(err, "Unable to connect socket");
		return err;
	}

	if ((err = rtnl_link_alloc_cache(sk, AF_UNSPEC, &link_cache)) < 0) {
		nl_perror(err, "Unable to allocate cache");
		return err;
	}

	if (rtnl_open(&rth, 0) < 0) {
		fprintf(stderr, "Cannot open rtnetlink\n");
		return EXIT_FAILURE;
	}

	//rtnl_set_strict_dump(&rth);

	/*if (rtnl_linkdump_req(&rth, AF_UNSPEC) < 0) {
		perror("Cannot send dump request");
		exit(1);
	}*/
	vlan_aware_bridge();
	nl_cache_free(link_cache);
	nl_socket_free(sk);
}
