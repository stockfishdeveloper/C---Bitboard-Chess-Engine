int CheckUci();
int MakeMove();

inline int CheckUci()
{
	
	string UciCommand;
	
while (cin >> UciCommand)
{
	if(UciCommand == "uci")
	{
cout << "id name Chess\n";
cout << "id author David Cimbalista\n";
cout << "uciok\n";
}
else if(UciCommand == "isready")
cout << "readyok\n";

else if(UciCommand == "quit")
exit(0);

else if (UciCommand == "ucinewgame") 
; 

else if(UciCommand == "startpos")
{
White_Pieces = 65535;
Black_Pieces = 18446462598732840960ULL;
White_King = 16;
Black_King = 1152921504606846976;
White_Queens = 8;
White_Rooks = 129;
White_Bishops = 36;
White_Knights = 66;
White_Pawns = 65280;
Black_Queens = 576460752303423488;
Black_Rooks = 9295429630892703744ULL;
Black_Bishops = 2594073385365405696;
Black_Knights = 4755801206503243776;
Black_Pawns = 71776119061217280;
Current_Turn = true;
}

else if(UciCommand == "go") 
MakeMove();


else
Dave << UciCommand << endl;
}

return 0;
}

int MakeMove()
{
	
//CheckUci();



//Keep making moves until one side loses or the game is a draw

	if(Current_Turn == true)
	{
Generate_White_Knight_Moves();//Generates White Knight moves
Generate_White_King_Moves();//Generates White King moves
Generate_White_Pawn_Moves();//Generates White Pawn moves
Generate_White_Rook_Moves();//Generates White Rook moves
Generate_White_Bishop_Moves();//Generates White Bishop moves
Generate_White_Queen_Moves();//Generates White Queen moves
MakeWhiteMove();//Plays White's moves out on the internal bitboards
}
else if(Current_Turn == false)
{
Generate_Black_Knight_Moves();//Generates Black Knight moves
Generate_Black_King_Moves();//Generates Black King moves
Generate_Black_Pawn_Moves();//Generates Black Pawn moves
Generate_Black_Rook_Moves();//Generates Black Rook moves
Generate_Black_Bishop_Moves();//Generates Black Bishop moves
Generate_Black_Queen_Moves();//Generates Black Queen moves
MakeBlackMove();//Plays Black's moves out on the internal bitboards
}


//So that we can see the reult
   // char f;
    //cin >> f;
    
    return 0;
}
