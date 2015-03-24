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

OUTPUTDIR:=$(BUILDDIR)/$(BUILDTYPE)

SRC:=$(wildcard src/*.c)
INCLUDE:=$(wildcard include/*.h)
OBJS:=$(patsubst src/%.c,$(OUTPUTDIR)/%.o,$(SRC))

INCLUDEFLAGS:=-I $(CURDIR) 

all : $(OBJS)
	printf "\033[0;32m"
	printf "Creating binary file in : $(BINDIR)\n"
	printf "\033[0m"
	$(LD) $(CFLAGS) -o $(BINDIR)/${BUILDTYPE}$(EXECUTABLENAME) $(OBJS) $(LDFLAGS)
.PHONY : all

-include $(DEPENDIR)/$(OBJS:.o=.d)

$(OUTPUTDIR)/%.o : src/%.c
	printf "\033[0;35m"
	printf "Creating object file $(@F)\n"
	printf "\033[0m"
	$(CC) $(INCLUDEFLAGS) $(CFLAGS) -c $< -o $@ $(LOGS) -a $(LOGDIR)/ccwarnings
	$(MAKEDEPEND) $(INCLUDEFLAGS) -MM -MF $(DEPENDIR)/$*.d $<

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

lint :
	$(LINT) $(SRC) $(LOGS) -a $(LOGDIR)/lint
	$(LINT) $(INCLUDE) $(LOGS) -a $(LOGDIR)/lint
.PHONY : lint

