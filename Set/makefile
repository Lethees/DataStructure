###############################################################
# Program:
#     Assignment 05, Set
#     Brother Kirby, CS235
#
# Authors:
#     Andres Rodriguez, Pedro Bastos, Fangyi Li
#
# Summary:
#     This is a implementation of set with the game Go Fish
#     as example using set data structure.
#
# Coding Time:
#     Pair Programming: 2 hours
#     Andres: 5 hours
#     Pedro: 6 hours
#     Fangyi: 4 hours
#
# The most difficult part:
#       Andres: my most dificult part was understand the find() functions.
#       also insert() and erase methods. 
#       Pedro:  My difficult part was to insert and delete itens from set.
#       Fangyi: My the difficult part was implementing the operators of the set.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment05.o goFish.o card.o
	g++ -o a.out assignment05.o goFish.o card.o
	tar -cf assignment05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment05.o : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
assignment05.o: set.h goFish.h assignment05.cpp
	g++ -c assignment05.cpp -std=c++11

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c goFish.cpp -std=c++11

card.o: card.h card.cpp
	g++ -c card.cpp -std=c++11

clean:
	rm -f *.o *.tar a.out
