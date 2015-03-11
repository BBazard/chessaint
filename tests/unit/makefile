ifeq ($(MAKELEVEL), 0)
error:
	@echo "Error : this makefile must be called from another makefile"
.PHONY : error
else
ifeq ($(BUILDTYPE), debug)
else
ifeq ($(BUILDTYPE), release)
else
error:
	@echo "Error : wrong buildtype : $(BUILDTYPE)"
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
	echo "Creating $(TESTSNAME)"
.PHONY : all

-include $(DEPENDIR)/$(TESTSOBJS:.o=.d)

$(OUTPUTDIR)/%.o : src/%.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) -MF $(DEPENDIR)/$*.d $< 
	echo "Creating object file $(@F)"

clean :
	rm -f $(TESTSOBJS)
	echo "Cleaning $(BUILDTYPE) directory"
.PHONY : clean

cleanbin :
	rm -f $(BINDIR)/${BUILDTYPE}${TESTSNAME}
	echo "Suppressing $(BUILDTYPE) binaries"
.PHONY : cleanbin

