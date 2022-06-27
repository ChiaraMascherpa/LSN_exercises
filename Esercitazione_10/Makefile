CC = mpicxx
CFLAGS = -Wall -O3 --std=c++11

main.exe : main.o ../Random/random.o travelling_salesman.o
	$(CC) ../Random/random.o travelling_salesman.o main.o -o main.exe
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
circle.exe : ../Random/random.o circle.cpp
	$(CC) ../Random/random.o circle.cpp -o circle.exe
square.exe : ../Random/random.o square.cpp
	$(CC) ../Random/random.o square.cpp -o square.exe
travelling_salesman.o : travelling_salesman.cpp travelling_salesman.hpp ../Random/random.o
	g++ -c travelling_salesman.cpp -o travelling_salesman.o
../Random/random.o : ../Random/random.cpp ../Random/random.h
	$(CC) -c ../Random/random.cpp -o ../Random/random.o $(CFLAGS)

clean :
	rm *.o main.exe seed.out
