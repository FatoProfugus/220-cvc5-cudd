all: bool_test0.o demorgans.o real0.o real1.o
	g++ -std=c++17 bool_test0.o -o bool_test0 -lcvc5
	g++ -std=c++17 demorgans.o -o demorgans -lcvc5
	g++ -std=c++17 real0.o -o real0 -lcvc5
	g++ -std=c++17 real1.o -o real1 -lcvc5

bool_test0: bool_test0.o
	g++ -std=c++17 bool_test0.o -o bool_test0 -lcvc5

bool_test0.o: bool_test0.cpp
	g++ -std=c++17 -c bool_test0.cpp -lcvc5

demorgans: demorgans.o
	g++ -std=c++17 demorgans.o -o demorgans -lcvc5

demorgans.o: demorgans.cpp
	g++ -std=c++17 -c demorgans.cpp -lcvc5

real0: real0.o
	g++ -std=c++17 real0.o -o real0 -lcvc5

real0.o: real0.cpp
	g++ -std=c++17 -c real0.cpp -lcvc5

real1: real1.o
	g++ -std=c++17 real1.o -o real1 -lcvc5

real1.o: real1.cpp
	g++ -std=c++17 -c real1.cpp -lcvc5

clean:
	rm *.o

spotless:
	rm bool_test0
	rm demorgans
	rm real0
	rm real1
	rm *.o
