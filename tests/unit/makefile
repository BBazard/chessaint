ifeq ($(MAKELEVEL), 0)
error:
	@echo -e "\033[0;31mError : this makefile must be called from another makefile\033[0m"
.PHONY : error
else
ifeq ($(BUILDTYPE), debug)
else
ifeq ($(BUILDTYPE), release)
else
error:
	@echo -e "\033[0;31mError : wrong buildtype : $(BUILDTYPE)\033[0m"
.PHONY : error
endif
endif
endif

DIRTOTEST=$(BUILDDIR)/$(BUILDTYPE)
OUTPUTDIR=$(BUILDDIR)/tests

PROJECTOBJS=$(filter-out $(DIRTOTEST)/main.o, $(wildcard $(DIRTOTEST)/*.o))
TESTSOBJS=$(patsubst src/%.c,$(OUTPUTDIR)/%.o,$(wildcard src/*.c))

all : $(TESTSOBJS) $(PROJECTOBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/${BUILDTYPE}${TESTSNAME} $(PROJECTOBJS) $(TESTSOBJS) $(LDFLAGS)
	echo -e "\033[0;32mCreating $(TESTSNAME)\033[0m"
.PHONY : all

-include $(DEPENDIR)/$(TESTSOBJS:.o=.d)

$(OUTPUTDIR)/%.o : src/%.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) -MF $(DEPENDIR)/$*.d $<
	echo -e "\033[0;35mCreating object file $(@F)\033[0m"

clean :
	rm -f $(TESTSOBJS)
	echo -e "\033[0;33mCleaning $(BUILDTYPE) directory\033[0m"
.PHONY : clean

cleanbin :
	rm -f $(BINDIR)/${BUILDTYPE}${TESTSNAME}
	echo -e "\033[0;33mSuppressing $(BUILDTYPE) binaries\033[0m"
.PHONY : cleanbin
