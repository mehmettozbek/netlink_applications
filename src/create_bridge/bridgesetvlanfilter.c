#include <netlink/netlink.h>
#include <netlink/route/link.h>
#include <netlink/route/link/bridge.h>
#include <netlink/route/link/bridge_info.h>
#include <linux/netlink.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <linux/rtnetlink.h>
#include <libnetlink.h>
#include <net/if.h>

#define TEST_BRIDGE_NAME "br0"

static int create_bridge(struct nl_sock *sk, struct nl_cache *link_cache, const char *name) {
	struct rtnl_link *link;
	int err	;
	link = rtnl_link_alloc();
	if ((err = rtnl_link_set_type(link, "bridge")) < 0) {
		rtnl_link_put(link);
		return err;
	}
	rtnl_link_set_name(link, name);
	/* COMMENT IT IF YOU WANT TO DISABLE VLAN FILTERING = 0 */
	rtnl_link_bridge_set_vlan_filtering(link, 1);

	if ((err = rtnl_link_add(sk, link, NLM_F_CREATE)) < 0) {
		return err;
	}
	rtnl_link_put(link);

	return 0;
}

int main()
{
	struct rtnl_link *link;
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

	if ((err = create_bridge(sk, link_cache, TEST_BRIDGE_NAME)) < 0) {
		nl_perror(err, "Unable to allocate testbridge");
		return err;
	}

	nl_cache_refill(sk, link_cache);
	link = rtnl_link_get_by_name(link_cache, TEST_BRIDGE_NAME);

	if(rtnl_link_is_bridge(link) == 0) {
		fprintf(stderr, "Link is not a bridge\n");
		return -2;
	}

	nl_cache_refill(sk, link_cache);
	rtnl_link_put(link);
	nl_cache_free(link_cache);
	nl_socket_free(sk);

	return 0;
}
