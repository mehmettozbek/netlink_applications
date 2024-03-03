# Netlink Example (bridge vlan add vid <VID> dev <ETH> pvid untagged)

This is a simple example of the code that performs same operation with `bridge vlan add vid 10 dev eth0 pvid untagged`. There is pre-condition in this code. There must be interface named `eth0` and it must be enslaved with bridge name `br0`. If not you can see the error like `RTNETLINK: Operation not supported`. 

## Compile

```bash
make all
```

## Run

```bash
./vlanawarebridge_netlink
```

## Results

Before running the code the results looks like this :

```bash
user@CSRPxVDP:~$ ip a
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
50: eth1: <BROADCAST,NOARP,UP,LOWER_UP> mtu 1500 qdisc noqueue master br0 state UNKNOWN group default qlen 1000
    link/ether d2:62:cf:63:88:f7 brd ff:ff:ff:ff:ff:ff
    inet 192.168.1.12/24 scope global eth1
       valid_lft forever preferred_lft forever
    inet6 fe80::d062:cfff:fe63:88f7/64 scope link 
       valid_lft forever preferred_lft forever
84: br0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default qlen 1000
    link/ether 1a:cf:13:07:3e:7c brd ff:ff:ff:ff:ff:ff
    inet6 fe80::5486:f5ff:fec7:cd2/64 scope link 
       valid_lft forever preferred_lft forever
85: eth0: <BROADCAST,NOARP,UP,LOWER_UP> mtu 1500 qdisc noqueue master br0 state UNKNOWN group default qlen 1000
    link/ether 1a:cf:13:07:3e:7c brd ff:ff:ff:ff:ff:ff
    inet 192.168.1.11/24 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::18cf:13ff:fe07:3e7c/64 scope link 
       valid_lft forever preferred_lft forever
user@CSRPxVDP:~$ bridge vlan show
port	vlan ids
docker0	 1 PVID Egress Untagged

eth1	 1 PVID Egress Untagged

br0	 1 PVID Egress Untagged

eth0	 1 PVID Egress Untagged
```

After running the code the results will look like this :

```bash
user@CSRPxVDP:~/vlanawarebridge_netlink$ sudo ./vlanawarebridge_netlink 
user@CSRPxVDP:~/vlanawarebridge_netlink$ ip a
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
50: eth1: <BROADCAST,NOARP,UP,LOWER_UP> mtu 1500 qdisc noqueue master br0 state UNKNOWN group default qlen 1000
    link/ether d2:62:cf:63:88:f7 brd ff:ff:ff:ff:ff:ff
    inet 192.168.1.12/24 scope global eth1
       valid_lft forever preferred_lft forever
    inet6 fe80::d062:cfff:fe63:88f7/64 scope link 
       valid_lft forever preferred_lft forever
84: br0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default qlen 1000
    link/ether 1a:cf:13:07:3e:7c brd ff:ff:ff:ff:ff:ff
    inet6 fe80::5486:f5ff:fec7:cd2/64 scope link 
       valid_lft forever preferred_lft forever
85: eth0: <BROADCAST,NOARP,UP,LOWER_UP> mtu 1500 qdisc noqueue master br0 state UNKNOWN group default qlen 1000
    link/ether 1a:cf:13:07:3e:7c brd ff:ff:ff:ff:ff:ff
    inet 192.168.1.11/24 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::18cf:13ff:fe07:3e7c/64 scope link 
       valid_lft forever preferred_lft forever
user@CSRPxVDP:~/vlanawarebridge_netlink$ bridge vlan show
port	vlan ids
docker0	 1 PVID Egress Untagged

eth1	 1 PVID Egress Untagged

br0	 1 PVID Egress Untagged

eth0	 1 Egress Untagged
	 10 PVID Egress Untagged

user@CSRPxVDP:~/vlanawarebridge_netlink$ 

```

## Clean

```bash
make clean
```
