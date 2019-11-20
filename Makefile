PROG = test
CC = g++
CPPFLAGS = -I/home/matt/Documents/Com_theory/ -I/home/matt/Documents/Com_theory/dists -I/home/matt/Documents/Com_theory/NetworkQueues -I/home/matt/Documents/Com_theory/NetworkQueues/Utilities
OBJS = main.o ./dists/uniform.o ./dists/exp.o ./dists/poisson.o ./NetworkQueues/MM1.o ./NetworkQueues/Utilities/Buffer.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

poisson.o: ./dists/poisson.h
	$(CC) $(CPPFLAGS) -c poisson.cpp

uniform.o : ./dists/uniform.h
	$(CC) $(CPPFLAGS) -c uniform.cpp

exp.o : ./dists/exp.h
	$(CC) $(CPPFLAGS) -c exp.cpp

buffer.o : ./NetworkQueues/Utilities/Buffer.home
	$(CC) $(CPPFLAGS) -c ./NetworkQueues/Utilities/Buffer.cpp

MM1.o : ./NetworkQueues/MM1.h ./NetworkQueues/Utilities/Buffer.h ./NetworkQueues/Utilities/Customer.h exp.o
	$(CC) $(CPPFLAGS) -c ./NetworkQueues/MM1.cpp

main.o : ./dists/uniform.o ./dists/exp.o main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm -f core $(PROG) $(OBJS)
