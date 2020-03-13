###############################################################
# Program:
#     Assignment 06, NODE
#     Brother Kirby, CS235
# Authors:
#     Andres Rodriguez, Pedro Bastos, Fangyi Li
#
# Summary:
#     This is a implementation of doubly linked lists. As
#     example, the insertion sort was implemented.
#
# Coding Time:
#     Pair Programming: 2 hours
#     Andres: 5 hours 
#     Pedro:  4 hours
#     Fangyi: 3 hours
#
# The most difficult part:
#       Andres:  How yo understand pointers, and how to update it.
#       Pedro:   Pointer that were update was the most difficult part.
#       Fangyi:  Insert function was pretty annoying
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h assignment06.o 
	g++ -o a.out assignment06.o -g
	tar -cf assignment06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment06.o      : the driver program
#      <anything else?>
##############################################################
assignment06.o: node.h assignment06.cpp sortInsertion.h
	g++ -c assignment06.cpp -g
