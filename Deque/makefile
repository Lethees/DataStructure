###############################################################
# Program:
#     Assignment 04, Deque
#     Brother Kirby, CS235
#
# Authors:
#     Andres Rodriguez, Pedro Bastos, Fangyi Li
#
# Summary:
#     This is a implementation of deque with an application to control a lab 
#     support wait list.
#
# Coding Time:
#     Pair Programming: 2 hours
#     Andres: 5 hours
#     Pedro: 8 hours
#     Fangyi: 8 hours
#
# The most difficult part:
#       Andres: I implemented my own version of the dequeue class,
#       however didn't work with now serving.
#       Pedro:  The worst part was to validate all normalize generic function.
#       Fangyi: I implemented my own version of the deque as well and the nowServing as well,
#               too bad that we still have problem with scheduling time together since we are
#               everywhere, I attached my nowServing in the tar file as well
###############################################################


##############################################################
# The main rule
##############################################################
a.out: deque.h assignment04.o nowServing.o request.o \
	supervisor.o
	g++ -o a.out assignment04.o nowServing.o \
	request.o supervisor.o
	tar -cf assignment04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment04.o : the driver program
#      nowServing.o    : the logic for the now serving program
#      supervisor.o      : a helper class for nor serving program
#      request.o          : request data from user 
##############################################################
assignment04.o: deque.h assignment04.cpp
	g++ -c assignment04.cpp -std=c++11

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp -std=c++11

request.o: request.h request.cpp deque.h
	g++ -c request.cpp -std=c++11

supervisor.o: supervisor.h supervisor.cpp deque.h
	g++ -c supervisor.cpp -std=c++11
 
nowServingFangyi Li.o: nowServing.h nowServingFangyi Li.cpp deque.h
	g++ -c supervisor.cpp -std=c++11
   
clean:
	rm -f *.o a.out *.tar
