CC=gcc
OPT=-g
FLAGS=
LIBS=
BINDIR=../bin/
BUILDIR=../build/
OBJS=$(BUILDIR)astar.o $(BUILDIR)chessboard.o $(BUILDIR)generate.o $(BUILDIR)graph.o $(BUILDIR)heuristic.o $(BUILDIR)ingui.o $(BUILDIR)list.o $(BUILDIR)main.o $(BUILDIR)notations.o $(BUILDIR)outgui.o $(BUILDIR)uci.o

build : $(OBJS)

cleanall : build clean

$(BUILDIR)astar.o : src/astar.c include/astar.h
	$(CC) $(OPT) -o $(BUILDIR)astar.o -c src/astar.c

$(BUILDIR)chessboard.o : src/chessboard.c include/chessboard.h
	$(CC) $(OPT) -o $(BUILDIR)chessboard.o -c src/chessboard.c

$(BUILDIR)generate.o : src/generate.c include/generate.h
	$(CC) $(OPT) -o $(BUILDIR)generate.o -c src/generate.c

$(BUILDIR)graph.o : src/graph.c include/graph.h
	$(CC) $(OPT) -o $(BUILDIR)graph.o -c src/graph.c

$(BUILDIR)heuristic.o : src/heuristic.c include/heuristic.h
	$(CC) $(OPT) -o $(BUILDIR)heuristic.o -c src/heuristic.c

$(BUILDIR)ingui.o : src/ingui.c include/ingui.h
	$(CC) $(OPT) -o $(BUILDIR)ingui.o -c src/ingui.c

$(BUILDIR)list.o : src/list.c include/list.h
	$(CC) $(OPT) -o $(BUILDIR)list.o -c src/list.c

$(BUILDIR)main.o : src/main.c
	$(CC) $(OPT) -o $(BUILDIR)main.o -c src/main.c

$(BUILDIR)notations.o : src/notations.c include/notations.h
	$(CC) $(OPT) -o $(BUILDIR)notations.o -c src/notations.c

$(BUILDIR)outgui.o : src/outgui.c include/outgui.h
	$(CC) $(OPT) -o $(BUILDIR)outgui.o -c src/outgui.c

$(BUILDIR)uci.o : src/uci.c include/uci.h
	$(CC) $(OPT) -o $(BUILDIR)uci.o -c src/uci.c

clean :
	rm $(OBJS)
