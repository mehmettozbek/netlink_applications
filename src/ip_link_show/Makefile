UNAME_S := $(shell uname -s)
ifneq ($(UNAME_S),Linux)
$(error Linux not detected, quitting)
endif
CC = gcc

EXE = iplinkshow
OBJS = $(EXE).o

NLCFLAGS = $(shell pkg-config --cflags libnl-route-3.0)
CFLAGS = -g -O0 -W -Wall $(NLCFLAGS)
NLLIBS = $(shell pkg-config --libs libnl-route-3.0)
LIBS = $(NLLIBS)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXE)