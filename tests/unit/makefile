ifeq ($(MAKELEVEL), 0)
error:
	printf "\033[0;31m"
	printf "Error : this makefile must be called from another makefile\n"
	printf "\033[0m"
.PHONY : error
else
ifeq ($(BUILDTYPE), debug)
else
ifeq ($(BUILDTYPE), release)
else
error:
	printf "\033[0;31m"
	printf "Error : wrong buildtype : $(BUILDTYPE)\n"
	printf "\033[0m"
.PHONY : error
endif
endif
endif

DIRTOTEST:=$(BUILDDIR)/$(BUILDTYPE)
OUTPUTDIR:=$(BUILDDIR)/tests

PROJECTOBJS:=$(filter-out $(DIRTOTEST)/main.o, $(wildcard $(DIRTOTEST)/*.o))
TESTSSRC:=$(wildcard src/*.c)
TESTSINCLUDE:=$(wildcard include/*.h)
TESTSOBJS:=$(patsubst src/%.c,$(OUTPUTDIR)/%.o,$(TESTSSRC))

CINCLUDE:=-I $(CURDIR) -I ../../chessaint

all : $(TESTSOBJS) $(PROJECTOBJS)
	printf "\033[0;32m"
	printf "Creating $(TESTSNAME)\n"
	printf "\033[0m"
	$(CC) $(CFLAGS) -o $(BINDIR)/${BUILDTYPE}${TESTSNAME} $(PROJECTOBJS) $(TESTSOBJS) $(LDFLAGS)
.PHONY : all

-include $(DEPENDIR)/$(TESTSOBJS:.o=.d)

$(OUTPUTDIR)/%.o : src/%.c
	printf "\033[0;35m"
	printf "Creating object file $(@F)\n"
	printf "\033[0m"
	$(CC) $(CINCLUDE) $(CFLAGS) -c $< -o $@
	$(CC) $(CINCLUDE) -MM -MF $(DEPENDIR)/$*.d $<

clean :
	printf "\033[0;33m"
	printf "Cleaning $(BUILDTYPE) directory\n"
	printf "\033[0m"
	rm -f $(TESTSOBJS)
.PHONY : clean

cleanbin :
	printf "\033[0;33m"
	printf "Suppressing $(BUILDTYPE) binaries\n"
	printf "\033[0m"
	rm -f $(BINDIR)/${BUILDTYPE}${TESTSNAME}
.PHONY : cleanbin

lint :
	$(LINT) $(TESTSSRC)
	$(LINT) $(TESTSINCLUDE)
.PHONY : lint

