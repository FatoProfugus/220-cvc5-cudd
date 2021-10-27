all: demorgans.o
	g++ -std=c++17 demorgans.o -o demorgans -lcvc5

demorgans: demorgans.o
	g++ -std=c++17 demorgans.o -o demorgans -lcvc5

demorgans.o: demorgans.cpp
	g++ -std=c++17 -c demorgans.cpp -lcvc5

clean:
	rm *.o

spotless:
	rm *.o
	rm demorgans
