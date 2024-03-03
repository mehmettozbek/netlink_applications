#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <link.h>
#include "netlink/route/link.h"
#include "netlink/route/addr.h"

int main() 
{
    char *name = "eth0";
    char *ipv4prefix = "192.168.230.130/24";
    struct nl_sock *nl_sk = nl_socket_alloc();

    if (nl_sk == NULL) {
        fprintf(stderr, "nl_socket_alloc failed\n");
        exit(EXIT_FAILURE);
    }

    int result = nl_connect(nl_sk, NETLINK_ROUTE);

    if (result < 0) {
        nl_perror(result, "nl_connect");
        exit(EXIT_FAILURE);
    }

    struct nl_cache *link_cache;
    result = rtnl_link_alloc_cache(nl_sk, AF_UNSPEC, &link_cache);
    if (result < 0) {
        nl_perror(result, "rtnl_link_alloc_cache");
        exit(EXIT_FAILURE);
    }

    struct rtnl_link *link = rtnl_link_get_by_name(link_cache, name);
    if (link == NULL) {
        fprintf(stderr, "rtnl_link_get_by_name: %s not found.\n", name);
        exit(EXIT_FAILURE);
    }

    int ifindex = rtnl_link_get_ifindex(link);
    if (ifindex == 0) {
        fprintf(stderr, "rtnl_link_get_ifindex failed\n");
        exit(EXIT_FAILURE);
    }

    printf("%s had index %d\n", name, ifindex);

    struct nl_addr *ipv4_addr;
    result = nl_addr_parse(ipv4prefix, AF_INET, &ipv4_addr);
    if (result < 0) {
        nl_perror(result, "nl_addr_parse");
        exit(EXIT_FAILURE);
    }

    struct rtnl_addr *addr = rtnl_addr_alloc();
    if (addr == NULL) {
        fprintf(stderr, "rtnl_addr_alloc failed\n");
        exit(EXIT_FAILURE);
    }

    rtnl_addr_set_ifindex(addr, ifindex);
    result = rtnl_addr_set_local(addr, ipv4_addr);
    if (result < 0) {
        nl_perror(result, "rtnl_addr_set_local");
        exit(EXIT_FAILURE);
    }

    result = rtnl_addr_add(nl_sk, addr, NLM_F_CREATE | NLM_F_EXCL);
    if (result < 0) {
        nl_perror(result, "rtnl_addr_add");
        exit(EXIT_FAILURE);
    }

    rtnl_addr_put(addr);
    nl_socket_free(nl_sk);
}
