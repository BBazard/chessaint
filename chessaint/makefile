ifeq ($(MAKELEVEL), 0)
error:
	@echo "Error : this makefile must be called from another makefile"
else

OBJS=$(BUILDDIR)/astar.o $(BUILDDIR)/chessboard.o $(BUILDDIR)/generate.o $(BUILDDIR)/graph.o $(BUILDDIR)/heuristic.o $(BUILDDIR)/ingui.o $(BUILDDIR)/list.o $(BUILDDIR)/main.o $(BUILDDIR)/notations.o $(BUILDDIR)/outgui.o $(BUILDDIR)/uci.o

all : $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(EXECUTABLENAME) $(OBJS) ; echo "Creating binary file in : $(BINDIR)"
.PHONY : all

$(BUILDDIR)/astar.o : src/astar.c include/astar.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/astar.o -c src/astar.c
	echo "Creating object astar.o"

$(BUILDDIR)/chessboard.o : src/chessboard.c include/chessboard.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/chessboard.o -c src/chessboard.c
	echo "Creating object chessboard.o"

$(BUILDDIR)/generate.o : src/generate.c include/generate.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/generate.o -c src/generate.c
	echo "Creating object generate.o"

$(BUILDDIR)/graph.o : src/graph.c include/graph.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/graph.o -c src/graph.c
	echo "Creating object graph.o"

$(BUILDDIR)/heuristic.o : src/heuristic.c include/heuristic.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/heuristic.o -c src/heuristic.c
	echo "Creating object heuristic.o"

$(BUILDDIR)/ingui.o : src/ingui.c include/ingui.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/ingui.o -c src/ingui.c
	echo "Creating object ingui.o"

$(BUILDDIR)/list.o : src/list.c include/list.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/list.o -c src/list.c
	echo "Creating object list.o"

$(BUILDDIR)/main.o : src/main.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)/main.o -c src/main.c
	echo "Creating object main.o"

$(BUILDDIR)/notations.o : src/notations.c include/notations.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/notations.o -c src/notations.c
	echo "Creating object notations.o"

$(BUILDDIR)/outgui.o : src/outgui.c include/outgui.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/outgui.o -c src/outgui.c
	echo "Creating object outgui.o"

$(BUILDDIR)/uci.o : src/uci.c include/uci.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/uci.o -c src/uci.c
	echo "Creating object uci.o"

clean :
	rm -f $(OBJS) ; echo "Cleaning release directory"
.PHONY : clean

cleanbin :
	rm -f $(BINDIR)/$(EXECUTABLENAME) ; echo "Suppressing release binary"
.PHONY : cleanbin

endif

