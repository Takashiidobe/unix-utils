CFLAGS = -std=c99 -D_POSIX_C_SOURCE=200809L
DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -Os
BUILD_DIR = build
SRC_DIR = src
LIB_DIR = lib

SRCS = $(shell find $(SRC_DIR)/ -type f -name "*.c")
LIBS = $(shell find $(LIB_DIR)/ -type f -name "*.c")
PROGS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%,$(SRCS))

all: $(PROGS)

build/%: $(SRC_DIR)/%.c $(LIBS)
	mkdir -p $(dir $@) 
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $(LIBS) $< -o $@$(VERSION)$(SUFFIX)

clean:
	rm -r $(BUILD_DIR)

test:
	shellspec

define HELP_TEXT
make                  build all utils
make test             run tests for utils 
endef

export HELP_TEXT

help:
	@echo "$$HELP_TEXT"
