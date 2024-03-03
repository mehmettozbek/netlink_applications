UNAME_S := $(shell uname -s)
ifneq ($(UNAME_S),Linux)
$(error Linux not detected, quitting)
endif

CC = gcc
EXE = ipaddressshow
OBJS = $(BIN_DIR)/$(EXE).o
NLCFLAGS = $(shell pkg-config --cflags libnl-route-3.0)
CFLAGS = -g -O0 -W -Wall $(NLCFLAGS)
NLLIBS = $(shell pkg-config --libs libnl-route-3.0)
LIBS = $(NLLIBS)
BIN_DIR = bin

YELLOW = \033[1;33m
RED = \033[1;31m
GREEN = \033[1;32m
RESET = \033[0m

all: $(BIN_DIR)/$(EXE)

$(BIN_DIR)/$(EXE): $(BIN_DIR)/$(EXE).o
	@echo "$(YELLOW)Linking $(EXE)...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS) || (echo "$(RED)Linking failed.$(RESET)" && false)
	@echo "$(GREEN)Linking completed.$(RESET)"

$(BIN_DIR)/$(EXE).o: $(EXE).c | $(BIN_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $< || (echo "$(RED)Compiling failed.$(RESET)" && false)
	@echo "$(GREEN)Compilation completed.$(RESET)"

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

.PHONY: clean

clean:
	@echo "$(YELLOW)Cleaning...$(RESET)"
	@rm -f $(OBJS) $(BIN_DIR)/$(EXE)
	@echo "$(GREEN)Cleaned.$(RESET)"