CC=gcc
OPT=-g
FLAGS=
LIBS=
BINDIR=
BUILDIR=../bin/
OBJS=$(BUILDIR)astar.o $(BUILDIR)chessboard.o $(BUILDIR)generate.o $(BUILDIR)graph.o $(BUILDIR)heuristic.o $(BUILDIR)ingui.o $(BUILDIR)list.o $(BUILDIR)main.o $(BUILDIR)notations.o $(BUILDIR)outgui.o $(BUILDIR)uci.o

build : $(OBJS)

$(BUILDIR)astar.o : src/astar.c include/astar.h
	$(CC) $(OPT) -o astar.o -c src/astar.c

$(BUILDIR)chessboard.o : src/chessboard.c include/chessboard.h
	$(CC) $(OPT) -o chessboard.o -c src/chessboard.c

$(BUILDIR)generate.o : src/generate.c include/generate.h
	$(CC) $(OPT) -o generate.o src/generate.c

$(BUILDIR)graph.o : src/graph.c include/graph.h
	$(CC) $(OPT) -o graph.o src/graph.c

$(BUILDIR)heuristic.o : src/heuristic.c include/heuristic.h
	$(CC) $(OPT) -o heuristic.o src/heuristic.c

$(BUILDIR)ingui.o : src/ingui.c include/ingui.h
	$(CC) $(OPT) -o ingui.o -c src/ingui.c

$(BUILDIR)list.o : src/list.c include/list.h
	$(CC) $(OPT) -o list.o -c src/list.c

$(BUILDIR)main.o : src/main.c
	$(CC) $(OPT) -o main.o -c src/main.c

$(BUILDIR)notations.o : src/notations.c include/notations.h
	$(CC) $(OPT) -o notations.o -c src/notations.c

$(BUILDIR)outgui.o : src/outgui.c include/outgui.h
	$(CC) $(OPT) -o outgui.o -c src/outgui.c

$(BUILDIR)uci.o : src/uci.c include/uci.h
	$(CC) $(OPT) -o uci.o -c src/uci.c
