OPTIONS = -O3  -Wall 

all: build/theanswer

debug: OPTIONS = -O0 -g
debug:
	build/theanswer

build/theanswer: main.cpp build/root.o build/power.o myfunctions.hpp
	g++ ${OPTIONS} main.cpp build/root.o build/power.o -o build/theanswer

build/root.o: root.cpp myfunctions.hpp
	g++ ${OPTIONS} -c root.cpp -o build/root.o

build/power.o: power.cpp
	g++ ${OPTIONS} -c power.cpp -o build/power.o

clean:
	rm build/theanswer build/*.o
