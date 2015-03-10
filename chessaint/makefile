ifeq ($(MAKELEVEL), 0)
error:
	@echo "Error : this makefile must be called from another makefile"
.PHONY : error
else
ifeq ($(BUILDTYPE), debug)

CFLAGS+=$(DEBUGCFLAGS) -MD
target: $(MAKECMDGOALS)
.PHONY : target

else
ifeq ($(BUILDTYPE), release)
target: $(MAKECMDGOALS)
.PHONY : target
else
error:
	@echo "Error : wrong buildtype : $(BUILDTYPE)"
.PHONY : error
endif
endif
endif

OUTPUTDIR=$(BUILDDIR)/$(BUILDTYPE)

DEP=$(patsubst src/%.c,$(OUTPUTDIR)/%.d,$(wildcard src/*.c))
OBJS=$(patsubst src/%.c,$(OUTPUTDIR)/%.o,$(wildcard src/*.c))

all : $(DEP) $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/${BUILDTYPE}$(EXECUTABLENAME) $(OBJS)
	echo "Creating binary file in : $(BINDIR)"
.PHONY : all

$(OUPUTDIR)/%.d : src/%.c
	$(CC) -MDE $<
	echo "Listing dependencies $(@F)"


#-include $(DEP) 

clean :
	rm -f $(OBJS)
	echo "Cleaning $(BUILDTYPE) directory"
.PHONY : clean

cleanbin :
	rm -f $(BINDIR)/${BUILDTYPE}$(EXECUTABLENAME)
	echo "Suppressing $(BUILDTYPE) binary"
.PHONY : cleanbin
