PROG = test
CC = g++
CPPFLAGS = -I./dists -I./NetworkQueues -I./NetworkQueues/Utilities -I./matplotlib-cpp/ -I/usr/include/python2.7 -lpython2.7
OBJS = main.o ./dists/uniform.o ./dists/exp.o ./dists/poisson.o ./NetworkQueues/MM1.o ./NetworkQueues/Utilities/Buffer.o 
PYHTON = -lpython2.7

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(PYHTON)

poisson.o: ./dists/poisson.h
	$(CC) $(CPPFLAGS) -c ./dists/poisson.cpp

uniform.o : ./dists/uniform.h
	$(CC) $(CPPFLAGS) -c ./dists/uniform.cpp

exp.o : ./dists/exp.h
	$(CC) $(CPPFLAGS) -c ./dists/exp.cpp

buffer.o : ./NetworkQueues/Utilities/Buffer.home
	$(CC) $(CPPFLAGS) -c ./NetworkQueues/Utilities/Buffer.cpp

MM1.o : ./NetworkQueues/MM1.h ./NetworkQueues/Utilities/Buffer.h ./NetworkQueues/Utilities/Customer.h exp.o
	$(CC) $(CPPFLAGS) -c ./NetworkQueues/MM1.cpp

main.o : ./dists/uniform.o ./dists/exp.o main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm -f core $(PROG) $(OBJS)
