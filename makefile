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
export LOGS=2>&1 | tee -a $(BUILDDIR)/log

export BUILDTYPE=debug

default : debugtests
	echo -e "\033[0;31mAll built\033[0m"
	echo ""
	echo -e "\033[0;31mThanks for using ChessAint's makefiles !\033[0m"
.PHONY : default

all : alltests doc
.PHONY : all

.SILENT :

release :
	$(MAKE) -C $(PROJECTDIR) all BUILDTYPE=release $(LOGS)
.PHONY : release

debug :
	$(MAKE) -C $(PROJECTDIR) all BUILDTYPE=debug $(LOGS)
.PHONY : debug

alltests : releasetests debugtests
.PHONY : alltests

releasetests : release
	$(MAKE) -C $(TESTSDIR) BUILDTYPE=release $(LOGS)
.PHONY : releasetests

debugtests : debug
	$(MAKE) -C $(TESTSDIR) BUILDTYPE=debug $(LOGS)
.PHONY : debugtests


doc :
	doxygen $(DOCDIR)/doxyfile
.PHONY : doc


cleanall : cleandep cleanbin cleandoc cleanlog
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

cleanlog :
	rm -f $(BUILDDIR)/log
	echo -e "\033[0;33mDeleting log file\033[0m"
.PHONY : cleanlog

cleandep : clean
	rm -f $(DEPENDIR)/*.d
	echo -e "\033[0;33mDeleting dependencies\033[0m"
.PHONY : cleandep

cleandoc :
	rm -rf $(DOCDIR)/html
	echo -e "\033[0;33mDeleting doc\033[0m"
.PHONY : cleandoc

