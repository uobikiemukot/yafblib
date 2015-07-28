CC ?= gcc
#CC ?= clang

CFLAGS  ?= -std=c99 -pedantic -Wall -Wextra -O3 -s -pipe
LDFLAGS ?=

DST = sample

HDR = include/util.h include/yafblib.h include/openbsd.h include/netbsd.h include/linux.h include/freebsd.h
SRC = $(DST).c

all: $(DST)

$(DST): $(SRC) $(HDR)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(DST)
