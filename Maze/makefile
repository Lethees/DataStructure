###############################################################
# Program:
#     Assignment 13, Graph
#     Brother Kirby, CS235
# Author:
#     Pedro Bastos, Fangy Li, Andres Rodriguez
# Summary:
#     Pedro: 
#     Fangy: 8 hrs
#	    Andres: 3 hours
#     Pedro: 
#	    Andres: The graph implementation.
#     Fangyi: findPath hurts a lot.
#	  
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment13.o graph.o maze.o
	g++ -o a.out assignment13.o graph.o maze.o -g
	tar -cf assignment13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment13.o     : the driver program
#      graph.o            : the graph code
#      maze.o             : the maze reading and solving code
##############################################################
assignment13.o: graph.h vertex.h assignment13.cpp
	g++ -c assignment13.cpp -g -std=c++11

graph.o: graph.h set.h vertex.h graph.cpp
	g++ -c graph.cpp -g -std=c++11

maze.o: maze.cpp maze.h vertex.h graph.h
	g++ -c maze.cpp -g -std=c++11
