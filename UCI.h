int CheckUci();
int MakeMove();
int Moves_Command();
int Parse_Moves(string First_Part, string Second_Part, char Promotion_Type);
int Parse_Moves(string First_Part, string Second_Part);
int Read_Fen(char Current_Square);
Bitboard Current_Rank = 72057594037927936;
bool White_Turn = true;
string UciCommand;
inline int CheckUci()
{
	bool Is_Fen = false;
	int Parse_Fen(string Fen);
		
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
Log << UciCommand << endl;
Parse_Fen(UciCommand); 
Is_Fen = false;
}

else if (UciCommand == "fen")
Is_Fen = true; 
 

else if(UciCommand == "go") 
MakeMove();

else if (UciCommand == "moves")
Moves_Command();

Log << UciCommand << endl;
}

return 0;
}


int Parse_Fen(string Fen)
{

char Current_Square;
for(int h = 0; h < (Fen.length()); h++)
{
	Current_Square = Fen[h];
	

Read_Fen(Current_Square);
}
//cout << White_Pieces;
char Curr_Turn;
cin >> Curr_Turn;
Log << Curr_Turn << endl;
if(Curr_Turn == 'w')
Current_Turn = true;
else
Current_Turn = false;
string Legal_Castling;
cin >> Legal_Castling;
Log << Legal_Castling << endl;
string En_Passant;
cin >> En_Passant;
Log << En_Passant << endl;
string Pawn_Moves;
cin >> Pawn_Moves;
Log << Pawn_Moves << endl;
string Move_Count;
cin >> Move_Count;
Log << Move_Count << endl;
	

	
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

int Read_Fen(char Current_Square)
{
	switch(Current_Square)
{
	case '1':
		if(!((Current_Rank * 2) & (A_Pawn_Mask)))
		Current_Rank *= 2;
		else
		Current_Rank *= 1;
		break;
	case '2':
		if(!((Current_Rank * 4) & (A_Pawn_Mask)))
		Current_Rank *= 4;
		else
		Current_Rank *= 2;
		break;
	case '3':
	    if(!((Current_Rank * 8) & (A_Pawn_Mask)))
		Current_Rank *= 8;
		else
		Current_Rank *= 4;
	    break;
	case '4':
		if(!((Current_Rank * 16) & (A_Pawn_Mask)))
		Current_Rank *= 16;
		else
		Current_Rank *= 8;
		break;
	case '5':
		if(!((Current_Rank * 32) & (A_Pawn_Mask)))
		Current_Rank *= 32;
		else
		Current_Rank *= 16;
		break;
	case '6':
		if(!((Current_Rank * 64) & (A_Pawn_Mask)))
		Current_Rank *= 64;
		else
		Current_Rank *= 32;
		break;
	case '7':
		if(!((Current_Rank * 128) & (A_Pawn_Mask)))
		Current_Rank *= 128;
		else
		Current_Rank *= 64;
		break;
	case '8':
		Current_Rank *= 128;
		break;
    case 'K':
    	White_King = Current_Rank;
    	White_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'k':
    	Black_King = Current_Rank;
    	Black_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'Q':
    	White_Queens |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'q':
    	Black_Queens |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'R':
    	White_Rooks |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'r':
    	Black_Rooks |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'B':
    	White_Bishops |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'b':
    	Black_Bishops |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'N':
    	White_Knights |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'n':
    	Black_Knights |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'P':
    	White_Pawns |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'p':
    	Black_Pawns |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case '/':
    	Current_Rank /= 32768;
		break;
}
return 0;
}

int Moves_Command()
{ 
	char First_Part[5];
	char Second_Part[5];
	char Promotion_Type;
	while(First_Part != "go")
	{
		cin.get();
		cin.get(First_Part, 3);
		cout << First_Part << endl;
		string F = "go";
		//cin.get(); 
		if(First_Part == F)
		{
		cout << "Dave!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		break;
		}
		cin.get(Second_Part, 3);
		cout << Second_Part << endl;
		if(Second_Part == "a8" || Second_Part == "b8" || Second_Part == "c8" || Second_Part == "d8" || Second_Part == "e8" || Second_Part == "f8" || Second_Part == "g8" || Second_Part == "h8")
		{
			cin >> Promotion_Type;
			Parse_Moves(First_Part, Second_Part, Promotion_Type);
		}
		
		else
		{
			cout << "Doing Pieces...." << endl;
			Parse_Moves(First_Part, Second_Part);
			cout << "Done with pieces...." << endl;
			
		}
		White_Turn ^= 1;
		cout << "Whose turn:" << White_Turn << endl;
		
	}
	cout << "White Pieces:" << White_Pieces << endl;
	cout << "Black Pieces:" << Black_Pieces << endl;
	UciCommand = "go";
	
	
	return 0;		
}

int Parse_Moves(string First, string Second)
{
	Bitboard From;
	Bitboard To;
	for(int i = 0; i < 64; i++)
	{
		if(PlayerMoves[i] == First)
		From = GeneralBoard[i];
	}
	for(int i = 0; i < 64; i++)
	{
		if(PlayerMoves[i] == Second)
		To = GeneralBoard[i];
	}
	if(White_Turn)
	{
		cout << "It's White's turn..." << endl;
		White_Pieces ^= From;
		White_Pieces |= To;
		if(White_Rooks & From)
		{
		White_Rooks ^= From;
		White_Rooks |= To;
	    }
	    if(White_Knights & From)
		{
		White_Knights ^= From;
		White_Knights |= To;
	    }
	    if(White_Bishops & From)
		{
		White_Bishops ^= From;
		White_Bishops |= To;
	    }
	    if(White_Pawns & From)
		{
		White_Pawns ^= From;
		White_Pawns |= To;
	    }
	    if(White_King & From)
		{
		White_King ^= From;
		White_King |= To;
	    }
	    if(White_Queens & From)
		{
		White_Queens ^= From;
		White_Queens |= To;
	    }
	}
	else
	{
		Black_Pieces ^= From;
		Black_Pieces |= To;
		if(Black_Rooks & From)
		{
		Black_Rooks ^= From;
		Black_Rooks |= To;
	    }
	    if(Black_Knights & From)
		{
		Black_Knights ^= From;
		Black_Knights |= To;
	    }
	    if(Black_Bishops & From)
		{
		Black_Bishops ^= From;
		Black_Bishops |= To;
	    }
	    if(Black_Pawns & From)
		{
		Black_Pawns ^= From;
		Black_Pawns |= To;
	    }
	    if(Black_King & From)
		{
		Black_King ^= From;
		Black_King |= To;
	    }
	    if(Black_Queens & From)
		{
		Black_Queens ^= From;
		Black_Queens |= To;
	    }
		
	}
return 0;	
}




int Parse_Moves(string First, string Second, char Promotion_Type)
{
	Bitboard From;
	Bitboard To;
	for(int i = 0; i < 64; i++)
	{
		if(PlayerMoves[i] == First)
		From = GeneralBoard[i];
	}
	for(int i = 0; i < 64; i++)
	{
		if(PlayerMoves[i] == Second)
		To = GeneralBoard[i];
	}
	if(White_Turn)
	{
		White_Pieces ^= From;
		White_Pieces |= To;
		if(White_Rooks & From)
		{
		White_Rooks ^= From;
		White_Rooks |= To;
	    }
	    if(White_Knights & From)
		{
		White_Knights ^= From;
		White_Knights |= To;
	    }
	    if(White_Bishops & From)
		{
		White_Bishops ^= From;
		White_Bishops |= To;
	    }
	    if(White_Pawns & From)
		{
		White_Pawns ^= From;
		White_Pawns |= To;
	    }
	    if(White_King & From)
		{
		White_King ^= From;
		White_King |= To;
	    }
	    if(White_Queens & From)
		{
		White_Queens ^= From;
		White_Queens |= To;
	    }
	}
	else
	{
		Black_Pieces ^= From;
		Black_Pieces |= To;
		if(Black_Rooks & From)
		{
		Black_Rooks ^= From;
		Black_Rooks |= To;
	    }
	    if(Black_Knights & From)
		{
		Black_Knights ^= From;
		Black_Knights |= To;
	    }
	    if(Black_Bishops & From)
		{
		Black_Bishops ^= From;
		Black_Bishops |= To;
	    }
	    if(Black_Pawns & From)
		{
		Black_Pawns ^= From;
		Black_Pawns |= To;
	    }
	    if(Black_King & From)
		{
		Black_King ^= From;
		Black_King |= To;
	    }
	    if(Black_Queens & From)
		{
		Black_Queens ^= From;
		Black_Queens |= To;
	    }
		
	}
return 0;	
}
