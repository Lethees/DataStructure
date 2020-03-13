###############################################################
# Program:
#     Assignment 03, Stocks
#     Brother Kirby, CS235
#
# Authors:
#     Andres Rodriguez, Pedro Bastos, Fangyi Li
#
# Summary:
#     This is a implementation of deque with a stock market
#     application. 
#
# Coding Time:
#     Pair Programming: 2 hours
#     Andres: 4 hours
#     Pedro: 10 hours
#     Fangyi: 8 hours
#
# The most difficult part: 
#       Andres: I implemented my own version of the queue class,
#       this version pass the test 1, but run with floating point 
#       exception. The worst was to implement the stock market part.  
#       Pedro:  The worst part is to know what is the output
#           required by the test sets.      
#       Fangyi: I implemented my own version of the queue as well since this
#              is the first week for us tho. I have to say it is pretty weird
#              for me using numPop and numPush instead of using head, tail, and the
#              numberItems... 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h assignment03.o dollars.o stock.o transaction.o \
	portfolio.o 
	g++ -o a.out assignment03.o dollars.o stock.o \
	transaction.o portfolio.o \
	-std=c++11
	tar -cf assignment03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      assignment03.o : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
#      transaction.o  : the logic for transaction
#      portfolio.o    : The logic ofr stock portfolio
##############################################################
assignment03.o: queue.h assignment03.cpp
	g++ -c assignment03.cpp  -std=c++11

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp  -std=c++11

stock.o: stock.h stock.cpp queue.h
	g++ -c stock.cpp  -std=c++11

transaction.o: transaction.h transaction.cpp
	g++ -c transaction.cpp  -std=c++11

portfolio.o: purchase.h portfolio.h portfolio.cpp
	g++ -c portfolio.cpp  -std=c++11

clean:
	rm -f *.o a.out *.tar
