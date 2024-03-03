# Netlink Example (ip link show)

This is a simple example of the code that performs same operation with the `ip link show` command.

## Compile

```bash
make all
```

## Run

```bash
./iplinkshow
```

## Results

```bash
user@CSRPxVDP:~/iplinkshow_netlink$ sudo ./iplinkshow 
1: lo, mtu 65536, master 0, unknown, 00:00:00:00:00:00
2: ens33, mtu 1500, master 0, up, 00:0c:29:f6:c2:c5
3: docker0, mtu 1500, master 0, down, 02:42:87:b1:f1:42 bridge
50: eth1, mtu 1500, master 84, unknown, d2:62:cf:63:88:f7
84: br0, mtu 1500, master 0, up, 1a:cf:13:07:3e:7c bridge
85: eth0, mtu 1500, master 84, unknown, 1a:cf:13:07:3e:7c
```

## Clean

```bash
make clean
```
