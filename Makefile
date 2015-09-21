all: Chess

Chess: Main.o MakeMove.o Search.o UCI.o MoveLegalityTesting.o Eval.o MoveGen.o Bitboard.o
	g++ Main.o MakeMove.o Search.o UCI.o MoveLegalityTesting.o Eval.o MoveGen.o Bitboard.o -o Chess.exe

Main.o: Main.cpp
	g++ -c Main.cpp	

MakeMove.o: MakeMove.cpp
	g++ -c MakeMove.cpp	
	
Search.o: Search.cpp
	g++ -c Search.cpp
		
UCI.o: UCI.cpp
	g++ -c -std=gnu++11 UCI.cpp
		
MoveLegalityTesting.o: MoveLegalityTesting.cpp
	g++ -c MoveLegalityTesting.cpp	
	
Eval.o: Eval.cpp
	g++ -c Eval.cpp	
	
MoveGen.o: MoveGen.cpp
	g++ -c Movegen.cpp
		
Bitboard.o: Bitboard.cpp
	g++ -c Bitboard.cpp
	
clean:
	rm *o Chess

