CC ?= gcc
#CC ?= clang

CFLAGS  ?= -std=c99 -pedantic -Wall -Wextra -O3 -s -pipe
LDFLAGS ?=

DST = sample

HDR = fb/util.h fb/common.h fb/openbsd.h fb/netbsd.h fb/linux.h fb/freebsd.h fb/color.h
SRC = $(DST).c

all: $(DST)

$(DST): $(SRC) $(HDR)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(DST)
