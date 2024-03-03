# Netlink Example (ip link set up dev <dev_name>)

This code perform the same thing what `ip link set up dev <DEV_NAME>` command does with the netlink codes.

## Dependencies

This code has some dependecies to libraries. If you are new to netlink socket programming you may have problem. But shortly you can install basic netlink libraries. You can install `libnl-3-dev` and `libnl-route-3-dev` packages.

The other thing you have to do is the compile `iproute2`. You can download `iproute2` source code from [here](https://github.com/shemminger/iproute2). You can follow its `README.md` and compile the code. Basically just run the `make` command.
## Compile

`iproute2` package has essential libraries in it. We have to `copy` the related library to necessary folders. First we need to copy `/iproute2/include/libnetlink.h` to `/usr/local/include`. Then we need `lib64` file in `/usr/local` if you dont have this folder in `/usr/local` then you have to create it with `mkdir /usr/local/lib64`. 

After the compilation completed with `iproute2` you need to copy `/iproute2/lib/libnetlink.a` to `/usr/local/lib64`.

These are the dependent compilation. Now it is time to compile our code. For do this type this command.

```bash
make all
```

## Run

You have to have network interface named `eth0` and it's state must be `down`. You can change this names in code with changing `dev` and `state` variables in `line28-29` in `iplinkset_updev.c`. 

```bash
sudo ./iplinkset_updev
```

## Results

```bash
Interface eth0 set up
```

Before running the code :

```bash
6: eth0: <BROADCAST,NOARP> mtu 1500 qdisc noqueue state DOWN group default qlen 1000
    link/ether 2e:a8:a2:8e:98:3d brd ff:ff:ff:ff:ff:ff
```

After running the code :

```bash
6: eth0: <BROADCAST,NOARP,UP,LOWER_UP> mtu 1500 qdisc noqueue state UNKNOWN group default qlen 1000
    link/ether 2e:a8:a2:8e:98:3d brd ff:ff:ff:ff:ff:ff
    inet6 fe80::2ca8:a2ff:fe8e:983d/64 scope link 
       valid_lft forever preferred_lft forever
```

## Clean

```bash
make clean
```