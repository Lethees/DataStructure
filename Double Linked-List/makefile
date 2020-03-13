###############################################################
# Program:
#     Assignment 07, LIST
#     Brother Kirby, CS235
# Author:
#     Andres Rodriguez, Pedro Bastos, Fangyi Li
# Summary:
#      This programming assignment will be to create the list 
#      data structure and use it to implement a program to find 
#      very large Fibonacci #numbers.
# Coding Time:
#     Pair Programming: 1.5 hours
#     Andres: 3 hours 
#     Pedro:  10 hours
#     Fangyi: 8 hours
#
# The most difficult part:
#       Andres: The most difficult part was the fibonacci. I agree 
#               with Fangyi about the help of Pedro. 
#       Pedro: The most difficult part was to figure a way to 
#       sum two number using WholeNumber class. Unfortunately
#       we're nit able to finish the extras.
#       Fangyi: Fibonacci was pretty hard for all of us. The program broke
#       down when it ran till the 215th number, but now it works. We could
#       probably not figure that out without Pedro.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h assignment07.o fibonacci.o
	g++ -o a.out assignment07.o fibonacci.o -g  -std=c++11
	tar -cf assignment07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment07.o : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
##############################################################
assignment07.o: list.h assignment07.cpp
	g++ -c assignment07.cpp -g  -std=c++11

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	g++ -c fibonacci.cpp -g  -std=c++11

