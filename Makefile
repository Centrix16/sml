ct = gcc
dbg_flags = -O0 -g -Wall -o
flags = -Wall -o
src = sml.c
libs = -lm
out = sml

all:
	$(ct) $(dbg_flags) $(out) $(src)
rm:
	rm -rf $(out)
release:
	$(ct) $(flags) $(out) $(src)
