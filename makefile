export CC=gcc
export OPT=-g
export CFLAGS=$(OPT)
export LDFLAGS=

CLEAN=noclean
DOC=nodoc

export TRUNK=$(shell pwd)
export RELEASEDIR=$(TRUNK)/chessaint
export TESTSDIR=$(TRUNK)/tests/unit
export BINDIR=$(TRUNK)/bin
export BUILDDIR=$(TRUNK)/build

export DOCDIR=$(TRUNK)/docs

export EXECUTABLENAME="chessaint"
export TESTSNAME="runtests"

all : release tests $(CLEAN) $(DOC)
	echo "All built, build directory status : $(CLEAN)"
	echo ""
	echo "Thanks for using ChessAint's makefiles !"
.PHONY : all

.SILENT :

release :
	make -seC $(RELEASEDIR) BUILDDIR=$(BUILDDIR)/release
.PHONY : release

tests :
	make -seC $(TESTSDIR) BUILDDIR=$(BUILDDIR)/tests
.PHONY : tests

doc :
	doxygen $(DOCDIR)/doxyfile
.PHONY : doc

nodoc:
.PHONY : nodoc

clean :
	make -seC $(RELEASEDIR) clean BUILDDIR=$(BUILDDIR)/release
	make -seC $(TESTSDIR) clean BUILDDIR=$(BUILDDIR)/tests
.PHONY : clean

cleanall : clean
	make -seC $(RELEASEDIR) cleanbin
	make -seC $(TESTSDIR) cleanbin
.PHONY : cleanall

noclean :
.PHONY : noclean
