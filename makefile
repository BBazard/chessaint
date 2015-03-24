export CC?=gcc
export CFLAGS+=-Wall -Wextra -std=c99
export LDFLAGS+=-lcunit

export DEBUGCFLAGS:=-g

TRUNK:=$(CURDIR)
PROJECTDIR:=$(TRUNK)/chessaint
TESTSDIR:=$(TRUNK)/tests/unit
DOCDIR:=$(TRUNK)/docs

export BINDIR:=$(TRUNK)/bin
export BUILDDIR:=$(TRUNK)/build
export DEPENDIR:=$(BUILDDIR)/dependencies

export EXECUTABLENAME:="chessaint"
export TESTSNAME:="runtests"

MAKE:=make -se
LOGS:=2>&1 | tee -a $(BUILDDIR)/log
export LINT:=$(TRUNK)/../cpplint.py

BUILDTYPE:=debug

default : debugtests lint
	printf "\033[0;30m"
	printf "All built\n\n"
	printf "Thanks for using ChessAInt's makefiles !\n"
	printf "\033[0m"
.PHONY : default

all : alltests doc lint
.PHONY : all

.SILENT :

release :
	$(MAKE) -C $(PROJECTDIR) all BUILDTYPE:=release $(LOGS)
.PHONY : release

debug :
	$(MAKE) -C $(PROJECTDIR) all BUILDTYPE:=debug $(LOGS)
.PHONY : debug

alltests : releasetests debugtests
.PHONY : alltests

releasetests : release
	$(MAKE) -C $(TESTSDIR) BUILDTYPE:=release $(LOGS)
.PHONY : releasetests

debugtests : debug
	$(MAKE) -C $(TESTSDIR) BUILDTYPE:=debug $(LOGS)
.PHONY : debugtests


doc :
	printf "\033[0;34m"
	printf "Generating Documentation\n"
	doxygen $(DOCDIR)/doxyfile
	printf "\033[0m"
.PHONY : doc

lint :
	printf "\033[0;36m"
	printf "Lint in progress\n"
	$(MAKE) -i -C $(PROJECTDIR) $@ BUILDTYPE:=$(BUILDTYPE)
	$(MAKE) -i -C $(TESTSDIR) $@ BUILDTYPE:=$(BUILDTYPE)
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
.PHONY : cleanbin

cleanlog :
	printf "\033[0;33m"
	printf "Deleting log file\n"
	printf "\033[0m"
	rm -f $(BUILDDIR)/log
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
	rm -rf $(DOCDIR)/html
	rm -rf $(DOCDIR)/man
.PHONY : cleandoc

