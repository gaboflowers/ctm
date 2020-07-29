CC = gcc
DESTDIR=/usr
LIBCTM_VER = 0.1
LIBCTM_NAME = libctm-$(LIBCTM_VER).so
.PHONY: clean all lib install

all: lib

lib: ctm.o
	mkdir -p ./lib
	$(CC) -Wall -I./include -shared -o ./lib/$(LIBCTM_NAME) ctm.o

ctm.o:
	$(CC) -Wall -I./include -c -fPIC src/ctm.c -o ctm.o

clean:
	rm *.o ./lib/*.so
	rmdir ./lib

install: lib
	mkdir -p $(DESTDIR)/lib $(DESTDIR)/include
	cp ./include/*.h $(DESTDIR)/include
	cp ./lib/$(LIBCTM_NAME) $(DESTDIR)/lib/$(LIBCTM_NAME)
	ln -s -f $(DESTDIR)/lib/$(LIBCTM_NAME) $(DESTDIR)/lib/libctm.so
