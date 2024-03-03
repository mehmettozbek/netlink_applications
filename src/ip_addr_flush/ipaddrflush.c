#include <stdio.h>
#include <netlink/netlink.h>
#include <netlink/socket.h>
#include <netlink/route/route.h>
#include <netlink/route/link.h>
#include <netlink/route/addr.h>
#include <linux/netlink.h>

int main()
{
	struct nl_sock *sk;
	struct nl_cache *link_cache;
	int err;

	sk = nl_socket_alloc();
	err = nl_connect(sk,NETLINK_ROUTE);

	if (err < 0) {
		printf("nl_connect() failed");
		return 1;
	}

	err = rtnl_link_alloc_cache(sk, AF_UNSPEC, &link_cache);

	if (err < 0) {
		printf("rtnl_link_alloc_cache() failed");
		return 1;
	}

	struct rtnl_link *l_veth;
	l_veth = rtnl_link_get_by_name(link_cache, "eth0");
	if(l_veth == NULL) {
		printf("Could not get link information");
		return 1;
	}

	if (err) {
		printf("Unable to determine ip address");
		return 1;
	}

	struct rtnl_addr *flush_addr;
	flush_addr = rtnl_addr_alloc();
	rtnl_addr_set_ifindex(flush_addr, rtnl_link_get_ifindex(l_veth));
	rtnl_addr_set_family(flush_addr, AF_INET);
	err = rtnl_addr_delete(sk, flush_addr, 0);

	if (err < 0) {
		printf("Could not flush address");
		return 1;
	}

	rtnl_addr_put(flush_addr);
	rtnl_link_put(l_veth);
	nl_cache_free(link_cache);
	nl_close(sk);
	nl_socket_free(sk);

	return 0;
}
