ifeq ($(MAKELEVEL), 0)
error:
	printf "\033[0;31m"
	printf "Error : this makefile must be called from another makefile\n"
	printf "\033[0m"
.PHONY : error
else

CFULLFLAGS:=$(CFLAGS)

ifeq ($(BUILDTYPE), debug)

CFULLFLAGS+=$(DEBUGCFLAGS)

target: $(MAKECMDGOALS)
.PHONY : target

else
ifeq ($(BUILDTYPE), release)

target: $(MAKECMDGOALS)
.PHONY : target

else
error:
	printf "\033[0;31m"
	printf "Error : wrong buildtype : $(BUILDTYPE)\n"
	printf "\033[0m"
.PHONY : error
endif
endif
endif

OUTPUTDIR:=$(BUILDDIR)/$(BUILDTYPE)

OBJS:=$(patsubst src/%.c,$(OUTPUTDIR)/%.o,$(wildcard src/*.c))

CINCLUDE:=-I $(CURDIR) 

all : $(OBJS)
	printf "\033[0;32m"
	printf "Creating binary file in : $(BINDIR)\n"
	printf "\033[0m"
	$(CC) $(CFULLFLAGS) -o $(BINDIR)/${BUILDTYPE}$(EXECUTABLENAME) $(OBJS)
.PHONY : all

-include $(DEPENDIR)/$(OBJS:.o=.d)

$(OUTPUTDIR)/%.o : src/%.c
	printf "\033[0;35m"
	printf "Creating object file $(@F)\n"
	printf "\033[0m"
	$(CC) $(CINCLUDE) $(CFULLFLAGS) -c $< -o $@
	$(CC) $(CINCLUDE) -MM -MF $(DEPENDIR)/$*.d $<

clean :
	printf "\033[0;33m"
	printf "Cleaning $(BUILDTYPE) directory\n"
	printf "\033[0m"
	rm -f $(OBJS)
.PHONY : clean

cleanbin :
	printf "\033[0;33m"
	printf "Suppressing $(BUILDTYPE) binary\n"
	printf "\033[0m"
	rm -f $(BINDIR)/${BUILDTYPE}$(EXECUTABLENAME)
.PHONY : cleanbin

