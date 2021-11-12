CFLAGS = -std=c99 -D_POSIX_C_SOURCE=200809L -g -O0
RELEASE_FLAGS = -O2
BUILD_DIR = build
RELEASE_DIR = release 
SRC_DIR = src
LIB_DIR = lib
STRIP = strip
SUFFIX =
VERSION =

SRCS = $(shell find $(SRC_DIR)/ -type f -name "*.c")
LIBS = $(shell find $(LIB_DIR)/ -type f -name "*.c")
PROGS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%,$(SRCS))
RELEASE_PROGS = $(patsubst $(SRC_DIR)/%.c,$(RELEASE_DIR)/%,$(SRCS))

all: $(PROGS)

build/%: $(SRC_DIR)/%.c $(LIBS)
	mkdir -p $(dir $@) 
	$(CC) $(CFLAGS) $(LIBS) $< -o $@$(VERSION)$(SUFFIX)

clean:
	rm -r $(BUILD_DIR)
	rm -r $(RELEASE_DIR)

release: $(RELEASE_PROGS)

release/%: $(SRC_DIR)/%.c $(LIBS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LIBS) $(RELEASE_FLAGS) $< -o $@$(VERSION)$(SUFFIX)

test:
	shellspec

define HELP_TEXT
make                  build all utils
make release          build all utils for release
make test             run tests for utils 
endef

export HELP_TEXT

help:
	@echo "$$HELP_TEXT"
