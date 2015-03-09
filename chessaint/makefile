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

OBJS=$(OUTPUTDIR)/astar.o $(OUTPUTDIR)/chessboard.o $(OUTPUTDIR)/generate.o $(OUTPUTDIR)/graph.o $(OUTPUTDIR)/heuristic.o $(OUTPUTDIR)/ingui.o $(OUTPUTDIR)/list.o $(OUTPUTDIR)/main.o $(OUTPUTDIR)/notations.o $(OUTPUTDIR)/outgui.o $(OUTPUTDIR)/uci.o

all : $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/${BUILDTYPE}$(EXECUTABLENAME) $(OBJS)
	echo "Creating binary file in : $(BINDIR)"
.PHONY : all

$(OUTPUTDIR)/astar.o : src/astar.c include/astar.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/astar.o -c src/astar.c
	echo "Creating object astar.o"

$(OUTPUTDIR)/chessboard.o : src/chessboard.c include/chessboard.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/chessboard.o -c src/chessboard.c
	echo "Creating object chessboard.o"

$(OUTPUTDIR)/generate.o : src/generate.c include/generate.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/generate.o -c src/generate.c
	echo "Creating object generate.o"

$(OUTPUTDIR)/graph.o : src/graph.c include/graph.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/graph.o -c src/graph.c
	echo "Creating object graph.o"

$(OUTPUTDIR)/heuristic.o : src/heuristic.c include/heuristic.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/heuristic.o -c src/heuristic.c
	echo "Creating object heuristic.o"

$(OUTPUTDIR)/ingui.o : src/ingui.c include/ingui.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/ingui.o -c src/ingui.c
	echo "Creating object ingui.o"

$(OUTPUTDIR)/list.o : src/list.c include/list.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/list.o -c src/list.c
	echo "Creating object list.o"

$(OUTPUTDIR)/main.o : src/main.c
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/main.o -c src/main.c
	echo "Creating object main.o"

$(OUTPUTDIR)/notations.o : src/notations.c include/notations.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/notations.o -c src/notations.c
	echo "Creating object notations.o"

$(OUTPUTDIR)/outgui.o : src/outgui.c include/outgui.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/outgui.o -c src/outgui.c
	echo "Creating object outgui.o"

$(OUTPUTDIR)/uci.o : src/uci.c include/uci.h
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)/uci.o -c src/uci.c
	echo "Creating object uci.o"

clean :
	rm -f $(OBJS)
	echo "Cleaning $(BUILDTYPE) directory"
.PHONY : clean

cleanbin :
	rm -f $(BINDIR)/${BUILDTYPE}$(EXECUTABLENAME)
	echo "Suppressing $(BUILDTYPE) binary"
.PHONY : cleanbin
