all: Chess

Chess: C:/src/Experiments/Main.o C:/src/Experiments/MakeMove.o C:/src/Experiments/Search.o C:/src/Experiments/UCI.o C:/src/Experiments/MoveLegalityTesting.o C:/src/Experiments/Eval.o C:/src/Experiments/MoveGen.o C:/src/Experiments/Bitboard.o
	g++ C:/src/Experiments/Main.o C:/src/Experiments/MakeMove.o C:/src/Experiments/Search.o C:/src/Experiments/UCI.o C:/src/Experiments/MoveLegalityTesting.o C:/src/Experiments/Eval.o C:/src/Experiments/MoveGen.o C:/src/Experiments/Bitboard.o -o C:/src/Experiments/Chess.exe

C:/src/Experiments/Main.o: C:/src/Experiments/Main.cpp
	g++ -c C:/src/Experiments/Main.cpp	

C:/src/Experiments/MakeMove.o: C:/src/Experiments/MakeMove.cpp
	g++ -c C:/src/Experiments/MakeMove.cpp	
	
C:/src/Experiments/Search.o: C:/src/Experiments/Search.cpp
	g++ -c C:/src/Experiments/Search.cpp
		
C:/src/Experiments/UCI.o: C:/src/Experiments/UCI.cpp
	g++ -c -std=gnu++11 C:/src/Experiments/UCI.cpp
		
C:/src/Experiments/MoveLegalityTesting.o: C:/src/Experiments/MoveLegalityTesting.cpp
	g++ -c C:/src/Experiments/MoveLegalityTesting.cpp	
	
C:/src/Experiments/Eval.o: C:/src/Experiments/Eval.cpp
	g++ -c C:/src/Experiments/Eval.cpp	
	
C:/src/Experiments/MoveGen.o: C:/src/Experiments/MoveGen.cpp
	g++ -c C:/src/Experiments/Movegen.cpp
		
C:/src/Experiments/Bitboard.o: C:/src/Experiments/Bitboard.cpp
	g++ -c C:/src/Experiments/Bitboard.cpp
	
clean:
	rm *o C:/src/Experiments/Chess

