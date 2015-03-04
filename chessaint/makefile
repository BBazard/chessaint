CC=gcc
OPT=
FLAGS=
LIBS=
BINDIR=.
BUILDDIR=.
OBJS=$(BUILDDIR)/astar.o $(BUILDDIR)/chessboard.o $(BUILDDIR)/generate.o $(BUILDDIR)/graph.o $(BUILDDIR)/heuristic.o $(BUILDDIR)/ingui.o $(BUILDDIR)/list.o $(BUILDDIR)/main.o $(BUILDDIR)/notations.o $(BUILDDIR)/outgui.o $(BUILDDIR)/uci.o

all : $(OBJS)
	@( $(CC) $(OPT) -o $(BINDIR)/chessaint $(OBJS) ; echo "Creating binary file in : " ; echo $(BINDIR) )

$(BUILDDIR)/astar.o : src/astar.c include/astar.h
	@$(CC) $(OPT) -o $(BUILDDIR)/astar.o -c src/astar.c
	@echo "Creating object astar.o"

$(BUILDDIR)/chessboard.o : src/chessboard.c include/chessboard.h
	@$(CC) $(OPT) -o $(BUILDDIR)/chessboard.o -c src/chessboard.c
	@echo "Creating object chessboard.o"

$(BUILDDIR)/generate.o : src/generate.c include/generate.h
	@$(CC) $(OPT) -o $(BUILDDIR)/generate.o -c src/generate.c
	@echo "Creating object generate.o"

$(BUILDDIR)/graph.o : src/graph.c include/graph.h
	@$(CC) $(OPT) -o $(BUILDDIR)/graph.o -c src/graph.c
	@echo "Creating object graph.o"

$(BUILDDIR)/heuristic.o : src/heuristic.c include/heuristic.h
	@$(CC) $(OPT) -o $(BUILDDIR)/heuristic.o -c src/heuristic.c
	@echo "Creating object heuristic.o"

$(BUILDDIR)/ingui.o : src/ingui.c include/ingui.h
	@$(CC) $(OPT) -o $(BUILDDIR)/ingui.o -c src/ingui.c
	@echo "Creating object ingui.o"

$(BUILDDIR)/list.o : src/list.c include/list.h
	@$(CC) $(OPT) -o $(BUILDDIR)/list.o -c src/list.c
	@echo "Creating object list.o"

$(BUILDDIR)/main.o : src/main.c
	@$(CC) $(OPT) -o $(BUILDDIR)/main.o -c src/main.c
	@echo "Creating object main.o"

$(BUILDDIR)/notations.o : src/notations.c include/notations.h
	@$(CC) $(OPT) -o $(BUILDDIR)/notations.o -c src/notations.c
	@echo "Creating object notations.o"

$(BUILDDIR)/outgui.o : src/outgui.c include/outgui.h
	@$(CC) $(OPT) -o $(BUILDDIR)/outgui.o -c src/outgui.c
	@echo "Creating object outgui.o"

$(BUILDDIR)/uci.o : src/uci.c include/uci.h
	@$(CC) $(OPT) -o $(BUILDDIR)/uci.o -c src/uci.c
	@echo "Creating object uci.o"

clean :
	@(rm $(OBJS) $(BINDIR)/chessaint 2> /dev/null ; echo "Cleaning dev directory" || true)
