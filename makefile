export CC:=gcc
export LD:=$(CC)
export MAKEDEPEND:=gcc

export CFLAGS+=-Wall -Wextra -std=c99
export LDFLAGS:=-lgmp

TRUNK:=$(CURDIR)
PROJECTDIR:=$(TRUNK)/chessaint
TESTSDIR:=$(TRUNK)/tests/unit
DOCDIR:=$(TRUNK)/docs

export BINDIR:=$(TRUNK)/bin
export BUILDDIR:=$(TRUNK)/build
export DEPENDIR:=$(BUILDDIR)/dependencies
export LOGDIR:=$(BUILDDIR)/logs

export EXECUTABLENAME:="chessaint"
export TESTSNAME:="runtests"

MAKE:=make -se
export LOGS:=2>&1 | tee
BUILDTYPE:=debug
export LINT:=$(TRUNK)/../cpplint.py

# Target-specific variables
debug : CFLAGS+=-g
release : CFLAGS+=-O3
debugtests : LDFLAGS+=-lcunit 
debugtests : CFLAGS+=-g
releasetests : LDFLAGS+=-lcunit 

default : debugtests lint
	printf "\033[0;30m"
	printf "All built\n\n"
	printf "Thanks for using ChessAInt's makefiles !\n"
	printf "\033[0m"
.PHONY : default

all : alltests lint doc
.PHONY : all

.SILENT :

release :
	$(MAKE) -C $(PROJECTDIR) all BUILDTYPE:=release
.PHONY : release

debug :
	$(MAKE) -C $(PROJECTDIR) all BUILDTYPE:=debug
.PHONY : debug

alltests : releasetests debugtests
.PHONY : alltests

releasetests : release
	$(MAKE) -C $(TESTSDIR) BUILDTYPE:=release
.PHONY : releasetests

debugtests : debug
	$(MAKE) -C $(TESTSDIR) BUILDTYPE:=debug
.PHONY : debugtests


doc :
	printf "\033[0;34m"
	printf "Generating Documentation\n"
	doxygen $(DOCDIR)/config/main.cfg
	doxygen $(DOCDIR)/config/wrapper.cfg
	cat $(LOGDIR)/docwarnings
	printf "\033[0m"
.PHONY : doc

lint :
	printf "\033[0;36m"
	printf "Lint in progress\n"
	$(MAKE) -i -C $(PROJECTDIR) $@ BUILDTYPE:=$(BUILDTYPE) | grep -vE "^Done"
	$(MAKE) -i -C $(TESTSDIR) $@ BUILDTYPE:=$(BUILDTYPE) | grep -vE "^Done"
	printf "\033[0m"
.PHONY : lint

cleanall : cleandep cleanbin cleandoc cleanlog
.PHONY : cleanall

clean :
	$(MAKE) -C $(PROJECTDIR) $@ BUILDTYPE:=release
	$(MAKE) -C $(PROJECTDIR) $@ BUILDTYPE:=debug
	$(MAKE) -C $(TESTSDIR) $@ BUILDTYPE:=release
	$(MAKE) -C $(TESTSDIR) $@ BUILDTYPE:=debug
.PHONY : clean

cleanbin :
	$(MAKE) -C $(PROJECTDIR) $@ BUILDTYPE:=release
	$(MAKE) -C $(PROJECTDIR) $@ BUILDTYPE:=debug
	$(MAKE) -C $(TESTSDIR) $@ BUILDTYPE:=release
	$(MAKE) -C $(TESTSDIR) $@ BUILDTYPE:=debug
	rm -f $(BINDIR)/uciLogs.txt
.PHONY : cleanbin

cleanlog :
	printf "\033[0;33m"
	printf "Deleting log files\n"
	printf "\033[0m"
	rm -f $(LOGDIR)/*
.PHONY : cleanlog

cleandep : clean
	printf "\033[0;33m"
	printf "Deleting dependencies\n"
	printf "\033[0m"
	rm -f $(DEPENDIR)/*.d
.PHONY : cleandep

cleandoc :
	printf "\033[0;33m"
	printf "Deleting doc\n"
	printf "\033[0m"
	rm -rf $(DOCDIR)/build/*
	rm -rf $(DOCDIR)/html
.PHONY : cleandoc

