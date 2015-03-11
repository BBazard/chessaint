ifeq ($(MAKELEVEL), 0)
error:
	@echo -e "\033[0;31mError : this makefile must be called from another makefile\033[0m"
.PHONY : error
else
ifeq ($(BUILDTYPE), debug)

CFLAGS+=$(DEBUGCFLAGS)
target: $(MAKECMDGOALS)
.PHONY : target

else
ifeq ($(BUILDTYPE), release)
target: $(MAKECMDGOALS)
.PHONY : target
else
error:
	@echo -e "\033[0;31mError : wrong buildtype : $(BUILDTYPE)\033[0m"
.PHONY : error
endif
endif
endif

OUTPUTDIR=$(BUILDDIR)/$(BUILDTYPE)

OBJS=$(patsubst src/%.c,$(OUTPUTDIR)/%.o,$(wildcard src/*.c))

all : $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/${BUILDTYPE}$(EXECUTABLENAME) $(OBJS)
	echo -e "\033[0;32mCreating binary file in : $(BINDIR)\033[0m"
.PHONY : all

-include $(DEPENDIR)/$(OBJS:.o=.d)

$(OUTPUTDIR)/%.o : src/%.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) -MF $(DEPENDIR)/$*.d $<
	echo -e "\033[0;35mCreating object file $(@F)\033[0m"

clean :
	rm -f $(OBJS)
	echo -e "\033[0;33mCleaning $(BUILDTYPE) directory\033[0m"
.PHONY : clean

cleanbin :
	rm -f $(BINDIR)/${BUILDTYPE}$(EXECUTABLENAME)
	echo -e "\033[0;33mSuppressing $(BUILDTYPE) binary\033[0m"
.PHONY : cleanbin
