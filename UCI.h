int CheckUci();
int MakeMove();

inline int CheckUci()
{
	bool Is_Fen = false;
	int Parse_Fen(string Fen);
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

else if (Is_Fen)
{
Parse_Fen(UciCommand); 
Is_Fen = false;
}

else if (UciCommand == "fen")
Is_Fen = true; 
 

else if(UciCommand == "go") 
MakeMove();

Log << UciCommand << endl;
}

return 0;
}


int Parse_Fen(string Fen)
{
Bitboard Current_Rank = 72057594037927936;
char Current_Square;
for(int h = 0; h < (Fen.length()); h++)
{
	Current_Square = Fen[h];
	

cout << Fen << endl;
switch(Current_Square)
{
	case '1':
		Current_Rank *= 2;
		break;
	case '2':
		Current_Rank *= 4;
		break;
	case '3':
	    Current_Rank *= 8;
	    break;
	case '4':
		Current_Rank *= 16;
		break;
	case '5':
		Current_Rank *= 32;
		break;
	case '6':
		Current_Rank *= 64;
		break;
	case '7':
		Current_Rank *= 128;
		break;
	case '8':
		Current_Rank *= 256;
		break;
    case 'K':
    	White_King = Current_Rank;
    	White_Pieces |= Current_Rank;
    	break;
    case 'k':
    	Black_King = Current_Rank;
    	Black_Pieces |= Current_Rank;
    	break;
    case 'Q':
    	White_Queens |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	break;
    case 'q':
    	Black_Queens |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	break;
    case 'R':
    	White_Rooks |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	break;
    case 'r':
    	Black_Rooks |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	break;
    case 'B':
    	White_Bishops |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	break;
    case 'b':
    	Black_Bishops |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	break;
    case 'N':
    	White_Knights |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	break;
    case 'n':
    	Black_Knights |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	break;
    case 'P':
    	White_Pawns |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	break;
    case 'p':
    	Black_Pawns |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	break;
    case '/':
    	Current_Rank /= 32768;
		break;
}

char Curr_Turn;
cin >> Curr_Turn;
if(Curr_Turn == 'w')
Current_Turn = true;
else
Current_Turn = false;
cout << White_Pieces;	
}
	
	return 0;
}






























int MakeMove()
{
	
if(Current_Turn)
	{
Generate_White_Knight_Moves();//Generates White Knight moves
Generate_White_King_Moves();//Generates White King moves
Generate_White_Pawn_Moves();//Generates White Pawn moves
Generate_White_Rook_Moves();//Generates White Rook moves
Generate_White_Bishop_Moves();//Generates White Bishop moves
Generate_White_Queen_Moves();//Generates White Queen moves
MakeWhiteMove();//Plays White's moves out on the internal bitboards
}
else 
{
Generate_Black_Knight_Moves();//Generates Black Knight moves
Generate_Black_King_Moves();//Generates Black King moves
Generate_Black_Pawn_Moves();//Generates Black Pawn moves
Generate_Black_Rook_Moves();//Generates Black Rook moves
Generate_Black_Bishop_Moves();//Generates Black Bishop moves
Generate_Black_Queen_Moves();//Generates Black Queen moves
MakeBlackMove();//Plays Black's moves out on the internal bitboards
}
   
    return 0;
}

