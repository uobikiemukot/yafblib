CC ?= gcc
AR ?= ar
#CC ?= clang

VERSION   = 1
MINOR_VER = 1.0.0
PREFIX = /usr

NAME = libyafb
SHARED = $(NAME).so.$(MINOR_VER)
STATIC = $(NAME).so.$(MINOR_VER)

SHARED_CFLAGS = -shared -Wl,-soname=$(NAME).so.$(VERSION) -o $(NAME).so.$(MINOR_VER)
STATIC_CFLAGS = rcus $(NAME).a
CFLAGS = -fPIC

HDR = yafblib.h util.h
SRC = yafblib.c util.c openbsd.c netbsd.c linux.c freebsd.c
OBJ = yafblib.o util.o openbsd.o netbsd.o linux.o freebsd.o

all: static shared

.c.o: $*.c $*.h
	$(CC) $(CFLAGS) -c $<

shared: $(OBJ) $(HDR)
	$(CC) $(SHARED_CFLAGS) $(OBJ)

static: yafblib.o $(OBJ) $(HDR)
	$(AR) $(STATIC_CFLAGS) $(OBJ)

install-static:
	install -m644 yafblib.h $(PREFIX)/include/yafblib.h
	install -m644 $(NAME).a $(PREFIX)/lib/$(NAME).a

install-shared:
	install -m644 yafblib.h $(PREFIX)/include/yafblib.h
	install -m755 $(NAME).so.$(MINOR_VER) $(PREFIX)/lib/$(NAME).so.$(MINOR_VER)
	ln -sf $(PREFIX)/lib/$(NAME).so.$(MINOR_VER) $(PREFIX)/lib/$(NAME).so.$(VERSION)

clean:
	rm -f $(NAME).so.$(MINOR_VER) $(NAME).a *.o *.gch
