CC = g++ -std=c++11
CFLAGS = -Wall -O3 --std=c++11

main.exe : main.o ../../Random/random.o ../../Librerie/Integral_m.o
	$(CC) ../../Random/random.o ../../Librerie/Integral_m.o main.o -o main.exe
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
../../Random/random.o : ../../Random/random.cpp ../../Random/random.h
	$(CC) -c ../../Random/random.cpp -o ../../Random/random.o $(CFLAGS)
../../Librerie/Integral_m.o : ../../Librerie/Integral_m.cpp ../../Librerie/Integral_m.hpp
	$(CC) -c ../../Librerie/Integral_m.cpp -o ../../Librerie/Integral_m.o
clean :
	rm *.o main.exe seed.out
