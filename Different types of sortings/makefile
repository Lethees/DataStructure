###############################################################
# Program:
#     Assignment 11, Sorts
#     Brother Kirby, CS 235
# Author:
#     Andres Rodriguez, Pedro Bastos, Fangyi Li
# Summary:
#      This programming assignment will create a survey for many
#      sorting algorithms.
# Coding Time:
#     Pair Programming: 1.5 hours
#     Andres: 4 hours 
#     Pedro:  6 hours
#     Fangyi: 5 hours
# The most difficult part:
#       Andres: Like Pedro said, the most difficult part was to understand
#               and decide how to apply the pseudocode in the book.
#               Also, the most sort algorithm difficult was the merge
#       Pedro: The most difficult part was to adjust indices to
#              fit C++ terminology. However, the pseudocode for Merge
#              sort needs a review.
#       Fangyi: I didn't know how to do the quickSort. Generally I feel this 
#              assignment is pretty straight forward as well
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment11.o
	g++ -o a.out assignment11.o -g
	tar -cf assignment11.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment11.o     : the driver program
##############################################################
assignment11.o: assignment11.cpp sortValue.h \
		sortBinary.h sortInsertion.h sortHeap.h sortBubble.h \
		sortSelection.h sortMerge.h sortQuick.h
	g++ -c assignment11.cpp -g

