#MAKEFILE

all: gra.o a_star.o
	g++ -O3 -o main main.cpp gra.o a_star.o

main.o:
	g++ -O3 -c main.cpp

gra.o:
	g++ -O3 -c gra.cpp

a_star.o:
	g++ -O3 -c a_star.cpp

clean:
	rm *.o main main.exe