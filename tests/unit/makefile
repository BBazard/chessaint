ifeq ($(MAKELEVEL), 0)
error:
	printf "\033[0;31m"
	printf "Error : this makefile must be called from another makefile\n"
	printf "\033[0m"
.PHONY : error
endif

DIRTOTEST:=$(BUILDDIR)/objs
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
	$(LD) $(CFLAGS) -o $(BINDIR)/${TESTSNAME} $(PROJECTOBJS) $(TESTSOBJS) $(LDFLAGS)
.PHONY : all

-include $(DEPENDIR)/$(TESTSOBJS:.o=.d)

$(OUTPUTDIR)/%.o : src/%.c
	printf "\033[0;35m"
	printf "Creating object file $(@F)\n"
	printf "\033[0m"
	$(CC) $(CINCLUDE) $(CFLAGS) -c $< -o $@ $(LOGS) -a $(LOGDIR)/ccwarnings
	$(MAKEDEPEND) $(CINCLUDE) -MM -MF $(DEPENDIR)/$*.d $<

clean :
	printf "\033[0;33m"
	printf "Cleaning directory\n"
	printf "\033[0m"
	rm -f $(OUTPUTDIR)/*.o
.PHONY : clean

cleanbin :
	printf "\033[0;33m"
	printf "Suppressing binaries\n"
	printf "\033[0m"
	rm -f $(BINDIR)/${TESTSNAME}
.PHONY : cleanbin

lint :
	$(LINT) $(TESTSSRC) $(LOGS) -a $(LOGDIR)/lint
	$(LINT) --root=trunk $(TESTSINCLUDE) $(LOGS) -a $(LOGDIR)/lint
.PHONY : lint

