CC=gcc
OPT=-g
FLAGS=
LIBS=
BINDIR=.
BUILDDIR=.
OBJS=
BIN=

all : $(OBJS)

.PHONY : all clean cleanbin

.SILENT :

# # # # # # # # # # # # #

# HERE THE OBJS TO MAKE #

# # # # # # # # # # # # #

clean :
	(rm $(OBJS) 2> /dev/null ; echo "Cleaning test directory" || true)

cleanbin :
	(rm $(BIN) 2> /dev/null ; echo "Suppressing test binaries" || true)
