CC=gcc
OPT=-g
FLAGS=
LIBS=
CURDIR=$(shell pwd)
BINDIR=bin
BUILDDIR=build

all : dev

dev :
	(cd chessaint ; make all BINDIR=${CURDIR}/${BINDIR} BUILDDIR=${CURDIR}/${BUILDDIR}/dev CC=${CC} OPT=${OPT})

test :
	(cd tests ; make all BINDIR=${CURDIR}/${BINDIR} BUILDDIR=${CURDIR}/${BUILDDIR}/test CC=${CC})

clean : 
	(cd chessaint ; make clean BUILDDIR=${CURDIR}/${BUILDDIR}/dev)
	(cd tests ; make clean BUILDDIR=${CURDIR}/${BUILDDIR}/test)

cleanall : clean
	(rmdir $(BUILDDIR)/dev ; rmdir $(BUILDDIR)/test)

initdir :
	(mkdir $(BUILDDIR)/dev ; mkdir $(BUILDDIR)/test)
