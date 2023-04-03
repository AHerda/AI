#MAKEFILE

all: gra.o a_star.o main.o
	g++ -pedantic -Wall -fsanitize=address -O3 -o main main.o gra.o a_star.o

main.o:
	g++ -pedantic -Wall -fsanitize=address -O3 -c main.o main.cpp

gra.o:
	g++ -pedantic -Wall -fsanitize=address -O3 -c gra.o gra.cpp

a_star.o:
	g++ -pedantic -Wall -fsanitize=address -O3 -c a_star.o a_star.cpp

clean:
	rm *.o

clean_all:
	rm *.o main