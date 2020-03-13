###############################################################
# Program:
#     Assignment 02, STACK
#     Brother Kirby, CS235
# Author:
#     Fangyi Li
# Summary:
#      implement the stack data structure and use it to 
#      convert an infix mathematical expression (4 + 8 * 3) 
#      into a postfix one (4 8 3 * +).    
# Time:
#     5h
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h assignment02.o infix.o 
	g++ -o a.out assignment02.o infix.o 
	tar -cf assignment02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment02.o : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
assignment02.o: stack.h infix.h assignment02.cpp
	g++ -c assignment02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp

