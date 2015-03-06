export CC=gcc
export OPT=-g
export CFLAGS=${OPT}
export LDFLAGS=

CLEAN=noclean

export TRUNK=$(shell pwd)
export RELEASEDIR=${TRUNK}/chessaint
export TESTSDIR=${TRUNK}/tests/unit
export BINDIR=${TRUNK}/bin
export BUILDDIR=${TRUNK}/build

all : release tests $(CLEAN)
	echo "All built, build directory status : $(CLEAN)"
	echo ""
	echo "Thanks for using ChessAint's makefiles !"
.PHONY : all

.SILENT :

release :
	make -seC $(RELEASEDIR) BUILDDIR=${BUILDDIR}/release
.PHONY : release

tests :
	make -seC $(TESTSDIR) BUILDDIR=${BUILDDIR}/tests
.PHONY : tests

clean :
	make -seC $(RELEASEDIR) clean BUILDDIR=${BUILDDIR}/release
	make -seC $(TESTSDIR) clean BUILDDIR=${BUILDDIR}/tests
.PHONY : clean

cleanall : clean
	make -seC $(RELEASEDIR) cleanbin
	make -seC $(TESTSDIR) cleanbin
.PHONY : cleanall

noclean :
.PHONY : noclean
