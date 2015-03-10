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

TESTSOBJS=$(OUTPUTDIR)/cunit_chessboard.o $(OUTPUTDIR)/chessboard_suite.o
PROJECTOBJS=$(DIRTOTEST)/chessboard.o

all : $(TESTSOBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/${BUILDTYPE}${TESTSNAME} $(PROJECTOBJS) $(TESTSOBJS) $(LDFLAGS)
	echo "Creating $(TESTSNAME)"
.PHONY : all

$(OUTPUTDIR)/cunit_chessboard.o : src/cunit_chessboard.c 
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/cunit_chessboard.o -c src/cunit_chessboard.c
	echo "Creating cunit_chessboard.o"

$(OUTPUTDIR)/chessboard_suite.o : src/chessboard_suite.c include/chessboard_suite.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/chessboard_suite.o -c src/chessboard_suite.c
	echo "Creating chessboard_suite.o"


clean :
	rm -f $(TESTSOBJS)
	echo "Cleaning $(BUILDTYPE) directory"
.PHONY : clean

cleanbin :
	rm -f $(BINDIR)/${BUILDTYPE}${TESTSNAME}
	echo "Suppressing $(BUILDTYPE) binaries"
.PHONY : cleanbin

