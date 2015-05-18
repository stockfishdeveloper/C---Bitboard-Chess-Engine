all: Ex

Ex: Ex.o
	g++ Ex.o -o Ex

Ex.o: Ex.cpp
	g++ -c Ex.cpp

clean:
	rm *o Ex

