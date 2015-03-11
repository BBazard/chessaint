export CC=gcc
export DEBUGCFLAGS=-g
export CFLAGS=-Wall -Wextra -ansi -std=c99
export LDFLAGS=-lcunit

export TRUNK=$(shell pwd)
export PROJECTDIR=$(TRUNK)/chessaint
export TESTSDIR=$(TRUNK)/tests/unit
export BINDIR=$(TRUNK)/bin
export BUILDDIR=$(TRUNK)/build
export DEPENDIR=$(BUILDDIR)/dependencies
export DOCDIR=$(TRUNK)/docs

export EXECUTABLENAME="chessaint"
export TESTSNAME="runtests"

export MAKE=make -se

export BUILDTYPE=debug

default : debugtests
	echo "All built"
	echo ""
	#echo -e "\033[0;31mThanks for using ChessAint's makefiles !\033[0m"
.PHONY : default

all : alltests doc
.PHONY : all

.SILENT :

release :
	$(MAKE) -C $(PROJECTDIR) all BUILDTYPE=release
.PHONY : release

debug :
	$(MAKE) -C $(PROJECTDIR) all BUILDTYPE=debug
.PHONY : debug

alltests : releasetests debugtests
.PHONY : alltests

releasetests : release
	$(MAKE) -C $(TESTSDIR) BUILDTYPE=release
.PHONY : releasetests

debugtests : debug
	$(MAKE) -C $(TESTSDIR) BUILDTYPE=debug
.PHONY : debugtests


doc :
	doxygen $(DOCDIR)/doxyfile
.PHONY : doc


cleanall : cleandep cleanbin cleandoc
.PHONY : cleanall

clean :
	$(MAKE) -C $(PROJECTDIR) clean BUILDTYPE=release
	$(MAKE) -C $(PROJECTDIR) clean BUILDTYPE=debug
	$(MAKE) -C $(TESTSDIR) clean BUILDTYPE=release
	$(MAKE) -C $(TESTSDIR) clean BUILDTYPE=debug
.PHONY : clean

cleanbin :
	$(MAKE) -C $(PROJECTDIR) cleanbin BUILDTYPE=release
	$(MAKE) -C $(PROJECTDIR) cleanbin BUILDTYPE=debug
	$(MAKE) -C $(TESTSDIR) cleanbin BUILDTYPE=release
	$(MAKE) -C $(TESTSDIR) cleanbin BUILDTYPE=debug
.PHONY : cleanbin

cleandep : clean
	rm -f $(DEPENDIR)/*.d
	echo "Deleting dependencies"
.PHONY : cleandep

cleandoc :
	rm -rf $(DOCDIR)/html
	echo "Deleting doc"
.PHONY : cleandoc

