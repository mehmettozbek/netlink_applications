UNAME_S := $(shell uname -s)
ifneq ($(UNAME_S),Linux)
$(error Linux not detected, quitting)
endif
CC = gcc

EXE = bridge_setvlanfilt
OBJS = $(EXE).o

EXE2 = bridge_masterinterface
OBJS2 = $(EXE2).o

NLCFLAGS = $(shell pkg-config --cflags libnl-route-3.0)
CFLAGS = -g -O0 -W -Wall $(NLCFLAGS)
NLLIBS = $(shell pkg-config --libs libnl-route-3.0)
LIBS =  $(NLLIBS) -lnl-3 -lnl-route-3 -lnetlink -lmnl

bridgesetvlanfilt: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) -L/usr/local/lib64 -L/lib/x86_64-linux-gnu

bridgemasterinterface: $(EXE2)

$(EXE2): $(OBJS2)
	$(CC) $(CFLAGS) -o $@ $(OBJS2) $(LIBS) -L/usr/local/lib64 -L/lib/x86_64-linux-gnu


.PHONY: clean

clean:
	rm -f $(OBJS) $(EXE) $(OBJS2) $(EXE2)