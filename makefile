.PHONY: all clean

all: graph

graph: main.c algo.c edge.c node.c graph.h
	gcc -Wall main.c -o graph

clean:
	rm -f graph