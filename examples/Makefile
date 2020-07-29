# Useful to run `make filename.c`, and it will lookup `filename.ctm`,
# transpile it into `filename.c`

RKTM=$(shell which rktm)
LIBCTM_VER=0.1
TARGETS=$(foreach ctmfile,$(wildcard *.ctm),$(basename $(ctmfile)))
C_TARGETS=$(foreach tgt, $(TARGETS),$(tgt).c)
.PHONY: clean all c

all: $(TARGETS)

c: $(C_TARGETS)

$(TARGETS) : % : %.c
	gcc $< -o $@ -I../include -L../lib -lctm-$(LIBCTM_VER)

%.c: %.ctm
	$(RKTM) $^

clean:
	rm $(C_TARGETS)
	rm $(TARGETS)

# If libctm is compiled but not installed, remember to run
# `$ export LD_LIBRARY_PATH=../lib` or to wherever the library
# is compiled, otherwise it will not be found.
