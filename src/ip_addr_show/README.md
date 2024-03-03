# Netlink Example (ip address show)

This is a simple example of the code that performs same with the `ip address show` command does.

## Prerequisites

In order to compile this code you need `libnl-route-3.0` package. If not installed it can be an error that the header file `netlink/netlink.h` is missing. You can use the package manager of your operating system to search for and install the package. For example, on Ubuntu, you can use the following command:

```bash
sudo apt-get install libnl-3-dev libnl-genl-3-dev libnl-route-3-dev
```

Once you have installed the package, you need to add the directory containing `libnl-route-3.0.pc` file to the `PKG_CONFIG_PATH` environment variable. This variable is used by the `pkg-config` tool to locate package information.

```bash
export PKG_CONFIG_PATH=/path/to/libnl-route-3.0.pc:$PKG_CONFIG_PATH
```

Replace `/path/to` with actual path to the direcotory containing `libnk-route-3.0.pc`. Typically, this file is located in the `libnl-route-3.0` package's development package directory. You can use the `find` command to search for the `libnl-route-3.0.pc` file on your system. Open a terminal and run the following command:

```bash
find / -name libnl-route-3.0.pc 2>/dev/null
```

## Compile

```bash
make
```

## Run

```bash
chmod +x run.sh
./run.sh
```

## Results

```bash
1: lo
    inet 127.0.0.1/8 scope host
    inet6 ::1 scope host
2: ens33
    inet 192.168.230.136/24 brd 192.168.230.255 scope global
    inet6 fe80::56e5:6837:a8c5:2677/64 scope link
3: virbr0
    inet 192.168.122.1/24 brd 192.168.122.255 scope global
4: virbr0-nic
5: docker0
    inet 172.17.0.1/16 brd 172.17.255.255 scope global
```

## Clean

```bash
make clean
``` 