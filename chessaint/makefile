ifeq ($(MAKELEVEL), 0)
error:
	@echo "Error : this makefile must be called from another makefile"
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
	@echo "Error : wrong buildtype : $(BUILDTYPE)"
.PHONY : error
endif
endif
endif

OUTPUTDIR=$(BUILDDIR)/$(BUILDTYPE)

OBJS=$(patsubst src/%.c,$(OUTPUTDIR)/%.o,$(wildcard src/*.c))

all : $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/${BUILDTYPE}$(EXECUTABLENAME) $(OBJS)
	echo "Creating binary file in : $(BINDIR)"
.PHONY : all

-include $(DEPENDIR)/$(OBJS:.o=.d)

$(OUTPUTDIR)/%.o : src/%.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< -o $(DEPENDIR)/$*.d
	echo "Creating object file $(@F)"

clean :
	rm -f $(OBJS)
	echo "Cleaning $(BUILDTYPE) directory"
.PHONY : clean

cleanbin :
	rm -f $(BINDIR)/${BUILDTYPE}$(EXECUTABLENAME)
	echo "Suppressing $(BUILDTYPE) binary"
.PHONY : cleanbin
