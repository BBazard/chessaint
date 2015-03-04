CC=gcc
OPT=-g
FLAGS=
LIBS=
CURDIR=$(shell pwd)
DEVDIR=chessaint
TESTDIR=tests/unit
BINDIR=bin
BUILDDIR=build
CLEAN=noclean

all : initdir dev test $(CLEAN)
	@( echo "Build finished, build directory status : " ; echo $(CLEAN) )

dev :
	@(cd $(DEVDIR) ; make all BINDIR=${CURDIR}/${BINDIR} BUILDDIR=${CURDIR}/${BUILDDIR}/dev CC=${CC} OPT=${OPT})

test :
	@(cd $(TESTDIR) ; make all BINDIR=${CURDIR}/${BINDIR} BUILDDIR=${CURDIR}/${BUILDDIR}/test CC=${CC})

.PHONY : clean cleanall noclean

clean : 
	@(cd $(DEVDIR) ; make clean BUILDDIR=${CURDIR}/${BUILDDIR}/dev)
	@(cd $(TESTDIR) ; make clean BUILDDIR=${CURDIR}/${BUILDDIR}/test)

cleanall : clean
	@(rmdir $(BUILDDIR)/dev 2> /dev/null ; rmdir $(BUILDDIR)/test 2> /dev/null ; echo "Suppressing dev and test directory" || true)

noclean :
	@:

initdir :
	@(mkdir $(BUILDDIR)/dev 2> /dev/null ; mkdir $(BUILDDIR)/test 2> /dev/null ; echo "Creating $(BUILDDIR)/dev and $(BUILDDIR)/test" || true)
