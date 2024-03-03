#  Netlink Example (ip link add br0 type bridge)

This is a simple example of the code that performs same with the `ip link add <bridgename> type bridge` command does.

## Create Bridge with  VLAN Filtering Enabled

This code is about the create a network bridge and enable the vlan filtering feature. You can disable it with `iproute2` command or comment the `line 27` in `bridge_setvlanfilt.c`. In order to enable vlan filtering `3.7 release of libnl library` is not supported for my environment. So I remove all netlink related packages in my system and changed the symbol versioning file.

```diff
diff --git a/configure.ac b/configure.ac
index b6bdcec..bbd3282 100644
--- a/configure.ac
+++ b/configure.ac
@@ -6,7 +6,7 @@
 # copied from glib
 m4_define([libnl_major_version], [3])
-m4_define([libnl_minor_version], [7])
+m4_define([libnl_minor_version], [8])
 m4_define([libnl_micro_version], [0])
 m4_define([libnl_git_sha], [m4_esyscmd([ ( [ -d ./.git/ ] && [ "$(readlink -f ./.git/)" = "$(readlink -f "$(git rev-parse --git-dir 2>/dev/null)" 2>/dev/null)" ] && git rev-parse --verify -q HEAD 2>/dev/null ) || true ])])
```

 Finally I build the library from the source. You can do it and follow the steps from [here](https://www.linuxfromscratch.org/blfs/view/svn/basicnet/libnl.html).

### Compile

```bash
make bridgesetvlanfilt
```

### Run

```bash
./bridge_setvlanfilt
```

### Results

Before running the code type `ip -d link show br0` command. You can see vlan_filtering is equal to 0.

```bash
user@CSRPxVDP:~/createbridge_netlink$ ip -d link show br0
45: br0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether 8e:aa:2d:3e:66:c7 brd ff:ff:ff:ff:ff:ff promiscuity 0 
    bridge forward_delay 1500 hello_time 200 max_age 2000 ageing_time 30000 stp_state 0 priority 32768 vlan_filtering 0 vlan_protocol 802.1Q bridge_id 8000.0:0:0:0:0:0 designated_root 8000.0:0:0:0:0:0 root_port 0 root_path_cost 0 topology_change 0 topology_change_detected 0 hello_timer    0.00 tcn_timer    0.00 topology_change_timer    0.00 gc_timer    0.00 vlan_default_pvid 1 vlan_stats_enabled 0 group_fwd_mask 0 group_address 01:80:c2:00:00:00 mcast_snooping 1 mcast_router 1 mcast_query_use_ifaddr 0 mcast_querier 0 mcast_hash_elasticity 16 mcast_hash_max 4096 mcast_last_member_count 2 mcast_startup_query_count 2 mcast_last_member_interval 100 mcast_membership_interval 26000 mcast_querier_interval 25500 mcast_query_interval 12500 mcast_query_response_interval 1000 mcast_startup_query_interval 3124 mcast_stats_enabled 0 mcast_igmp_version 2 mcast_mld_version 1 nf_call_iptables 0 nf_call_ip6tables 0 nf_call_arptables 0 addrgenmode eui64 numtxqueues 1 numrxqueues 1 gso_max_size 65536 gso_max_segs 65535 
```

After run the compiled code type `ip -d link show br0`. You can see vlan_filtering is equal to 1.

```bash
user@CSRPxVDP:~/createbridge_netlink$ ip -d link show br0
45: br0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether 8e:aa:2d:3e:66:c7 brd ff:ff:ff:ff:ff:ff promiscuity 0 
    bridge forward_delay 1500 hello_time 200 max_age 2000 ageing_time 30000 stp_state 0 priority 32768 vlan_filtering 1 vlan_protocol 802.1Q bridge_id 8000.0:0:0:0:0:0 designated_root 8000.0:0:0:0:0:0 root_port 0 root_path_cost 0 topology_change 0 topology_change_detected 0 hello_timer    0.00 tcn_timer    0.00 topology_change_timer    0.00 gc_timer    0.00 vlan_default_pvid 1 vlan_stats_enabled 0 group_fwd_mask 0 group_address 01:80:c2:00:00:00 mcast_snooping 1 mcast_router 1 mcast_query_use_ifaddr 0 mcast_querier 0 mcast_hash_elasticity 16 mcast_hash_max 4096 mcast_last_member_count 2 mcast_startup_query_count 2 mcast_last_member_interval 100 mcast_membership_interval 26000 mcast_querier_interval 25500 mcast_query_interval 12500 mcast_query_response_interval 1000 mcast_startup_query_interval 3124 mcast_stats_enabled 0 mcast_igmp_version 2 mcast_mld_version 1 nf_call_iptables 0 nf_call_ip6tables 0 nf_call_arptables 0 addrgenmode eui64 numtxqueues 1 numrxqueues 1 gso_max_size 65536 gso_max_segs 65535 
```

### Clean

```bash
make clean
```

##  Create Bridge with  set Interface to master

This code is setting the network interface to the bridge with master type.

### Compile

```bash
make bridgemasterinterface
```

### Run

```bash
./bridge_masterinterface
```

### Results

Before running the code type `ip a` command. You can see eth0 is not mastered with br0.


```bash
user@CSRPxVDP:~/createbridge_netlink$ ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: ens33: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 00:0c:29:f6:c2:c5 brd ff:ff:ff:ff:ff:ff
    inet 192.168.230.133/24 scope global ens33
       valid_lft forever preferred_lft forever
    inet6 fe80::20c:29ff:fef6:c2c5/64 scope link 
       valid_lft forever preferred_lft forever
3: docker0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc noqueue state DOWN group default 
    link/ether 02:42:87:b1:f1:42 brd ff:ff:ff:ff:ff:ff
    inet 172.17.0.1/16 brd 172.17.255.255 scope global docker0
       valid_lft forever preferred_lft forever
5: eth0: <BROADCAST,NOARP,UP,LOWER_UP> mtu 1500 qdisc noqueue state UNKNOWN group default qlen 1000
    link/ether 6a:0f:6a:a5:4f:c1 brd ff:ff:ff:ff:ff:ff
    inet 192.168.1.11/24 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::680f:6aff:fea5:4fc1/64 scope link 
       valid_lft forever preferred_lft forever
46: br0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether 1a:2c:e6:38:49:79 brd ff:ff:ff:ff:ff:ff
```

After code is run. The results are changed.

```bash
user@CSRPxVDP:~/createbridge_netlink$ ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: ens33: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 00:0c:29:f6:c2:c5 brd ff:ff:ff:ff:ff:ff
    inet 192.168.230.133/24 scope global ens33
       valid_lft forever preferred_lft forever
    inet6 fe80::20c:29ff:fef6:c2c5/64 scope link 
       valid_lft forever preferred_lft forever
3: docker0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc noqueue state DOWN group default 
    link/ether 02:42:87:b1:f1:42 brd ff:ff:ff:ff:ff:ff
    inet 172.17.0.1/16 brd 172.17.255.255 scope global docker0
       valid_lft forever preferred_lft forever
5: eth0: <BROADCAST,NOARP,UP,LOWER_UP> mtu 1500 qdisc noqueue master br0 state UNKNOWN group default qlen 1000
    link/ether 6a:0f:6a:a5:4f:c1 brd ff:ff:ff:ff:ff:ff
    inet 192.168.1.11/24 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::680f:6aff:fea5:4fc1/64 scope link 
       valid_lft forever preferred_lft forever
47: br0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether 6a:0f:6a:a5:4f:c1 brd ff:ff:ff:ff:ff:ff
```

### Clean

```bash
make clean
```
