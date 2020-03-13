###############################################################
# Program:
#     Assignment 09, Binary Search Tree
#     Brother Kirby, CS235
# Author:
#     Andres Rodriguez, Pedro Bastos, Fangyi Li
# Summary:
#      This programming assignment will be to create the binary 
#      tree data structure with Red-Black balance.
# Coding Time:
#     Pair Programming: 1.5 hours
#     Andres: 2 hours 
#     Pedro:  12 hours.
#     Fangyi: 14 hours
#
# The most difficult part:
#       Andres: This week was particulalry hard for me, I tryed to 
#               implement the BST class without exit. Also the RB was 
# 				hard for understand the logic. 
#       Pedro:  Most difficult part was to predict all cases
#               for insert/delete nodes, specially after RB
#               balancing.
#       Fangyi: I tried so many different way to solve the rotation, but failed.
#               I am just not so good with algorithms, tears.
###############################################################


##############################################################
# The main rule
##############################################################
a.out: assignment09.o
	g++ -o a.out assignment09.o -std=c++11
	tar -cf assignment09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment09.o     : the driver program
##############################################################
assignment09.o: bst.h assignment09.cpp
	g++ -c assignment09.cpp -std=c++11

