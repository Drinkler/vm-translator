CC = gcc
BUILD ?= debug

SRCDIR = src
INCDIR = include
BUILDDIR = build/$(BUILD)
BINDIR = bin/$(BUILD)
TARGET = $(BINDIR)/VMTranslator

CFLAGS_COMMON = -std=c2x -Wall -Wextra -I$(INCDIR)
ifeq ($(BUILD), release)
	CFLAGS += $(CFLAGS_COMMON) -O3
else
	CFLAGS += $(CFLAGS_COMMON) -O0 -g
endif

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))

.PHONY: all clean debug release

all: $(TARGET)

debug:
	$(MAKE) BUILD=debug   all

release:
	$(MAKE) BUILD=release all

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build bin
