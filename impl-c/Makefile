# Makefile standalone de libgerarion-core (export gt-core).
# Generado por tools/export_module.py de verared/gerarion v3.3.0 (2026-11-19).
# Núcleo TCJ+GUS: sin malloc, sin reloj de SO, sin tabla TAI-UTC, sin
# dependencias externas. Compilable con GCC y Clang (C11, -Werror).

NAME = gerarion-core
MAJOR = 3
MINOR = 3
PATCH = 0

PREFIX ?= /usr/local
INCLUDEDIR ?= $(PREFIX)/include
LIBDIR ?= $(PREFIX)/lib
PKGCONFDIR ?= $(LIBDIR)/pkgconfig

CC ?= cc
CFLAGS ?= -std=gnu11 -O2 -Wall -Wextra -pedantic
PICFLAGS ?= -fPIC

SRC = core/gus_core.c
HDRS = core/gus_core.h

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
SO_LDFLAGS = -shared
else
SO_LDFLAGS = -shared -Wl,-soname,lib$(NAME).so.$(MAJOR)
endif

.PHONY: all smoke clean install pkgconfig

all: libgerarion-core.a libgerarion-core.so.$(MAJOR) gerarion-core.pc

libgerarion-core.a: $(SRC) $(HDRS)
	$(CC) $(CFLAGS) -c $(SRC) -o gus_core.a.o
	ar rcs $@ gus_core.a.o
	rm -f gus_core.a.o

libgerarion-core.so.$(MAJOR): $(SRC) $(HDRS)
	$(CC) $(CFLAGS) $(PICFLAGS) $(SO_LDFLAGS) -o $@ $(SRC)

gerarion-core.pc: gerarion-core.pc.in
	sed -e 's|@PREFIX@|$(PREFIX)|g' \
		-e 's|@VERSION@|$(MAJOR).$(MINOR).$(PATCH)|g' \
		gerarion-core.pc.in > $@

pkgconfig: gerarion-core.pc

# Humo: núcleo compilado y ejecutado en total aislamiento.
smoke: libgerarion-core.a
	$(CC) $(CFLAGS) -I. -o smoke.c.bin smoke.c ./libgerarion-core.a
	./smoke.c.bin

install: all
	install -d $(DESTDIR)$(INCLUDEDIR)/gerarion/core $(DESTDIR)$(LIBDIR) $(DESTDIR)$(PKGCONFDIR)
	install -m 644 core/gus_core.h $(DESTDIR)$(INCLUDEDIR)/gerarion/core/
	install -m 644 libgerarion-core.a libgerarion-core.so.$(MAJOR) $(DESTDIR)$(LIBDIR)/
	ln -sf libgerarion-core.so.$(MAJOR) $(DESTDIR)$(LIBDIR)/libgerarion-core.so
	install -m 644 gerarion-core.pc $(DESTDIR)$(PKGCONFDIR)/

clean:
	rm -f libgerarion-core.a libgerarion-core.so.$(MAJOR) gerarion-core.pc smoke.c.bin gus_core.a.o *.o
