# Netlink Example (ip addr flush)

This is a simple example of the code that performs same with the `ip addr flush` command does.

## Compile 

```bash
make all
```

## Run

```bash
./ipaddrflush
```

## Results

Running `ip a` command before run the code.

```bash
user@CSRPxVDP:~/ipaddrflush_netlink$ ip a
8: eth0: <BROADCAST,NOARP,UP,LOWER_UP> mtu 1500 qdisc noqueue state UNKNOWN group default qlen 1000
    link/ether 96:2f:19:20:8f:b5 brd ff:ff:ff:ff:ff:ff
    inet 192.168.230.130/24 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::942f:19ff:fe20:8fb5/64 scope link 
       valid_lft forever preferred_lft forever
```

After running the code.

```bash
user@CSRPxVDP:~/ipaddrflush_netlink$ ip a
8: eth0: <BROADCAST,NOARP,UP,LOWER_UP> mtu 1500 qdisc noqueue state UNKNOWN group default qlen 1000
    link/ether 96:2f:19:20:8f:b5 brd ff:ff:ff:ff:ff:ff
    inet6 fe80::942f:19ff:fe20:8fb5/64 scope link 
       valid_lft forever preferred_lft forever
```

## Clean

```bash
make clean
```
