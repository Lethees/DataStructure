###############################################################
# Program:
#     Assignment 12, Hash
#     Brother Kirby, CS 235
# Author:
#     Andres Rodriguez, Pedro Bastos, Fangyi Li
# Summary:
#      This programming assignment will create and validate
#      a hash table.
# Coding Time:
#     Pair Programming: 1.5 hours
#     Andres: 5 hours 
#     Pedro:  6 hours
#     Fangyi: 9 hours
# The most difficult part:
#       Andres: The spell-check and the beggining of the 
#               hash class, specially how to chain the data inside 
#               the table.
#       Pedro: No difficult part at all.
#       Fangyi: SpellCheck bugged me off a bit, 
#              the hash itself wasn't pretty hard.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment12.o spellCheck.o
	g++ -o a.out assignment12.o spellCheck.o -std=c++11
	tar -cf assignment12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment12.o     : the driver program
#      spellCheck.o       : the spell-check program and driver
##############################################################
assignment12.o: hash.h assignment12.cpp list.h
	g++ -c assignment12.cpp -std=c++11

spellCheck.o: hash.h spellCheck.h spellCheck.cpp
	g++ -c spellCheck.cpp -std=c++11

