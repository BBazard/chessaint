CC=gcc
OPT=
FLAGS=
LIBS=
BINDIR=.
BUILDDIR=.
OBJS=$(BUILDDIR)/astar.o $(BUILDDIR)/chessboard.o $(BUILDDIR)/generate.o $(BUILDDIR)/graph.o $(BUILDDIR)/heuristic.o $(BUILDDIR)/ingui.o $(BUILDDIR)/list.o $(BUILDDIR)/main.o $(BUILDDIR)/notations.o $(BUILDDIR)/outgui.o $(BUILDDIR)/uci.o

build : $(OBJS)
	$(CC) $(OPT) -o $(BINDIR)/chessaint $(OBJS)

buildclean : build clean

$(BUILDDIR)/astar.o : src/astar.c include/astar.h
	$(CC) $(OPT) -o $(BUILDDIR)/astar.o -c src/astar.c

$(BUILDDIR)/chessboard.o : src/chessboard.c include/chessboard.h
	$(CC) $(OPT) -o $(BUILDDIR)/chessboard.o -c src/chessboard.c

$(BUILDDIR)/generate.o : src/generate.c include/generate.h
	$(CC) $(OPT) -o $(BUILDDIR)/generate.o -c src/generate.c

$(BUILDDIR)/graph.o : src/graph.c include/graph.h
	$(CC) $(OPT) -o $(BUILDDIR)/graph.o -c src/graph.c

$(BUILDDIR)/heuristic.o : src/heuristic.c include/heuristic.h
	$(CC) $(OPT) -o $(BUILDDIR)/heuristic.o -c src/heuristic.c

$(BUILDDIR)/ingui.o : src/ingui.c include/ingui.h
	$(CC) $(OPT) -o $(BUILDDIR)/ingui.o -c src/ingui.c

$(BUILDDIR)/list.o : src/list.c include/list.h
	$(CC) $(OPT) -o $(BUILDDIR)/list.o -c src/list.c

$(BUILDDIR)/main.o : src/main.c
	$(CC) $(OPT) -o $(BUILDDIR)/main.o -c src/main.c

$(BUILDDIR)/notations.o : src/notations.c include/notations.h
	$(CC) $(OPT) -o $(BUILDDIR)/notations.o -c src/notations.c

$(BUILDDIR)/outgui.o : src/outgui.c include/outgui.h
	$(CC) $(OPT) -o $(BUILDDIR)/outgui.o -c src/outgui.c

$(BUILDDIR)/uci.o : src/uci.c include/uci.h
	$(CC) $(OPT) -o $(BUILDDIR)/uci.o -c src/uci.c

clean :
	rm $(OBJS)
