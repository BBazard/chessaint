export CC=gcc
export DEBUGCFLAGS=-g
export CFLAGS=-Wall -Wextra -ansi -std=c99
export LDFLAGS=-lcunit

export TRUNK=$(shell pwd)
export PROJECTDIR=$(TRUNK)/chessaint
export TESTSDIR=$(TRUNK)/tests/unit
export BINDIR=$(TRUNK)/bin
export BUILDDIR=$(TRUNK)/build
export DOCDIR=$(TRUNK)/docs

export EXECUTABLENAME="chessaint"
export TESTSNAME="runtests"

export MAKE=make -seC

export BUILDTYPE=debug

default : debug tests
	echo "All built"
	echo ""
	echo "Thanks for using ChessAint's makefiles !"
.PHONY : default

all : release debug tests doc
.PHONY : all

.SILENT :

release :
	$(MAKE) $(PROJECTDIR) all BUILDTYPE=release
.PHONY : release

debug :
	$(MAKE) $(PROJECTDIR) all BUILDTYPE=debug
.PHONY : debug

tests :
	$(MAKE) $(TESTSDIR) BUILDTYPE=tests
.PHONY : tests

doc :
	doxygen $(DOCDIR)/doxyfile
.PHONY : doc

cleandoc :
	rm -rf $(DOCDIR)/html
	echo "Deleting doc"
.PHONY : cleandoc

nodoc:
.PHONY : nodoc

cleanall : clean cleanbin cleandoc
.PHONY : cleanall

clean :
	$(MAKE) $(PROJECTDIR) clean BUILDTYPE=release
	$(MAKE) $(PROJECTDIR) clean BUILDTYPE=debug
	$(MAKE) $(TESTSDIR) clean BUILDTYPE=tests
.PHONY : clean

cleanbin :
	$(MAKE) $(PROJECTDIR) cleanbin BUILDTYPE=release
	$(MAKE) $(PROJECTDIR) cleanbin BUILDTYPE=debug
	$(MAKE) $(TESTSDIR) cleanbin BUILDTYPE=tests
.PHONY : cleanbin

noclean :
.PHONY : noclean
