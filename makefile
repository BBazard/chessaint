CC=gcc
OPT=-g
CFLAGS=
LIBS=
CURDIR=$(shell pwd)
DEVDIR=chessaint
TESTDIR=tests/unit
BINDIR=bin
BUILDDIR=build
CLEAN=noclean

all : initdir dev test $(CLEAN)
	echo "All built, build directory status : $(CLEAN)"
	echo ""
	echo "Thanks for using ChessAint's makefiles !"

.PHONY : all dev test clean cleanall noclean initdir

.SILENT :

dev : initdir
	make -sC $(DEVDIR) BINDIR=${CURDIR}/${BINDIR} BUILDDIR=${CURDIR}/${BUILDDIR}/dev CC=${CC} OPT=${OPT}

test : initdir
	make -sC $(TESTDIR) BINDIR=${CURDIR}/${BINDIR} BUILDDIR=${CURDIR}/${BUILDDIR}/test CC=${CC}

clean : 
	make -sC $(DEVDIR) clean BUILDDIR=${CURDIR}/${BUILDDIR}/dev
	make -sC $(TESTDIR) clean BUILDDIR=${CURDIR}/${BUILDDIR}/test

cleanall : clean
	make -skC $(DEVDIR) cleanbin BINDIR=${CURDIR}/${BINDIR}
	make -skC $(TESTDIR) cleanbin BINDIR=${CURDIR}/${BINDIR}
	(rmdir $(BUILDDIR)/dev 2> /dev/null ; rmdir $(BUILDDIR)/test 2> /dev/null ; echo "Suppressing dev and test directory" || true)

noclean :

initdir :
	(mkdir $(BUILDDIR)/dev 2> /dev/null ; mkdir $(BUILDDIR)/test 2> /dev/null ; echo "Creating $(BUILDDIR)/dev and $(BUILDDIR)/test") || true
