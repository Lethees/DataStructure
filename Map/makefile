###############################################################
# Program:
#     Assignment 10, Map
#     Brother Kirby, CS 235
# Author:
#     Andres Rodriguez, Pedro Bastos, Fangyi Li
# Summary:
#      This programming assignment will create a map with key, value pair stored in a binary 
#      search tree data structure with Red-Black balance.
# Coding Time:
#     Pair Programming: 1.5 hours
#     Andres: 5 hours 
#     Pedro:  6 hours.
#     Fangyi: 4 hours
# The most difficult part:
#       Andres:The insert function of map.h and how to understand the pair
#       Pedro: This is a straightforward assignment. The most difficult part was to organize C++ code 
#              to fit all language formalities.
#       Fangyi:This one is pretty ez, so I don't know which part seems harder than the other parts.
#              That's also the reason that we didn't really spend too much time doing it.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment10.o wordCount.o
	g++ -o a.out assignment10.o wordCount.o -std=c++11
	tar -cf assignment10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment10.o : the driver program
#      wordCount.o    : the wordCount() function
##############################################################
assignment10.o: pair.h map.h bst.h assignment10.cpp
	g++ -c assignment10.cpp -std=c++11

wordCount.o: map.h bst.h wordCount.h wordCount.cpp 
	g++ -c wordCount.cpp -std=c++11
