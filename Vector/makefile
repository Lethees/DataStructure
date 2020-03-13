###############################################################
# Program:
#     Assignment 01, Vector
#     Brother Kirby, CS235
# Author:
#     Fangyi Li
# Summary:
#     to write a class with the same functionality as the 
#     standard template library (STL) vector class.
# Time:
#     10h
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h assignment01.o
	g++ -o a.out assignment01.o -std=c++11
	tar -cf assignment01.tar vector.h assignment01.cpp makefile

##############################################################
# The individual components
#      assignment01.o     : the driver program
##############################################################
assignment01.o: vector.h assignment01.cpp
	g++ -c assignment01.cpp -std=c++11

