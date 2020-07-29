CC = gcc
LIBCTM_VER = 0.1
LIBCTM_NAME = libctm-$(LIBCTM_VER).so
.PHONY: clean all lib

all: lib

lib: ctm.o
	mkdir ./lib
	$(CC) -Wall -I./include -shared -o ./lib/$(LIBCTM_NAME) ctm.o

ctm.o:
	$(CC) -Wall -I./include -c -fPIC src/ctm.c -o ctm.o

clean:
	rm *.o ./lib/*.so
