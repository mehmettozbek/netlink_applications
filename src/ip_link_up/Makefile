UNAME_S := $(shell uname -s)
ifneq ($(UNAME_S),Linux)
$(error Linux not detected, quitting)
endif
CC = gcc

EXE = iplinkset_updev
OBJS = $(EXE).o



NLCFLAGS = $(shell pkg-config --cflags libnl-route-3.0)
CFLAGS = -g -O0 -W -Wall $(NLCFLAGS)
NLLIBS = $(shell pkg-config --libs libnl-route-3.0)
LIBS = $(NLLIBS) -lnetlink -lmnl

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) -L/usr/local/lib64 -L/lib/x86_64-linux-gnu

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXE)