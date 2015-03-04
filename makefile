CC=gcc
OPT=-g
FLAGS=
LIBS=
BINDIR=bin
BUILDDIR=build

all : dev

dev :
	(cd chessaint ; make all BINDIR=${BINDIR} BUILDDIR=${BUILDDIR}/dev CC=${CC} OPT=${OPT})

test :
	(cd tests ; make all BINDIR=${BINDIR} BUILDDIR=${BUILDDIR}/test CC=${CC})

clean : 
	(cd chessaint ; make clean BUILDDIR=${BUILDDIR}/dev)
	(cd tests ; make clean BUILDDIR=${BUILDDIR}/test)
