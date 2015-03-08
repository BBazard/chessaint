ifeq ($(MAKELEVEL), 0)
error:
	@echo "Error : this makefile must be called from another makefile"
else

ifneq ($(BUILDTYPE), tests)
error:
	@echo "Error : wrong buildtype : $(BUILDTYPE)"
else

OUTPUTDIR=$(BUILDDIR)/$(BUILDTYPE)

OBJS=$(OUTPUTDIR)/cunit_chessboard.o $(OUTPUTDIR)/chessboard_suite.o $(OUTPUTDIR)/chessboard.o

all : $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(TESTSNAME) $(OBJS) $(LDFLAGS)
	echo "Creating chessboard.tests"
.PHONY : all

$(OUTPUTDIR)/cunit_chessboard.o : src/cunit_chessboard.c 
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/cunit_chessboard.o -c src/cunit_chessboard.c
	echo "Creating cunit_chessboard.o"

$(OUTPUTDIR)/chessboard_suite.o : src/chessboard_suite.o include/chessboard_suite.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/chessboard_suite.o -c src/chessboard_suite.c
	echo "Creating chessboard_suite.o"

$(OUTPUTDIR)/chessboard.o : $(TRUNK)/chessaint/src/chessboard.c $(TRUNK)/chessaint/include/chessboard.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/chessboard.o -c $(TRUNK)/chessaint/src/chessboard.c
	echo "Creating chessboard.o"


clean :
	rm -f $(OBJS)
	echo "Cleaning $(BUILDTYPE) directory"
.PHONY : clean

cleanbin :
	rm -f $(BINDIR)/$(TESTSNAME)
	echo "Suppressing $(BUILDTYPE) binaries"
.PHONY : cleanbin

endif
endif

