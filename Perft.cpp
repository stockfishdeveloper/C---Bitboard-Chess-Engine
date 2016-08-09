#include "Perft.h"
#include "Search.h"
int Root_Perft(int depth)
{
    if(depth == 0) return 1;
    Bitboard nodes = 0;
    pos.Current_Turn ? Generate_White_Moves(false, &pos) : Generate_Black_Moves(false, &pos);
    for(int i = 0; i < pos.numlegalmoves; i++)
    {
        pos.Make_Move(pos.LegalMoves[i]);
        for( int h = 0; h < 64; h++)
        {
            if(GeneralBoard[h] & pos.LegalMoves[i].From)
            {
                cout << PlayerMoves[h];
            }
        }
        for( int h = 0; h < 64; h++)
        {
            if(GeneralBoard[h] & pos.LegalMoves[i].To)
            {
            	cout  << PlayerMoves[h];
            	if(pos.LegalMoves[i].Promotion)
            	{
            		switch(pos.LegalMoves[i].PromotionType)
                    	{
                    		case WN:
                    			cout << "n";
                    			break;
                    		case WB:
                    			cout << "b";
                    			break;
                    		case WR:
                    			cout << "r";
                    			break;
                    		case WQ:
                    			cout << "q";
                    			break;
                    		case BN:
                    			cout << "n";
                    			break;
							case BB:
                    			cout << "b";
                    			break;
                    		case BR:
                    			cout << "r";
                    			break;
                    		case BQ:
                    			cout << "q";
                    			break;
						}
				}
				cout << ": ";
            }
        }
        int f = nodes;
        nodes += Perft(&pos, depth - 1);
        cout << nodes - f << endl;
        pos.Undo_Move(pos.LegalMoves[i]);
    }
    return nodes;

}
int Perft(Position* posit, int depth)
{
	if (depth == 0) return 1;
    Position position(posit);
    Bitboard nodes = 0;
    position.Current_Turn ? Generate_White_Moves(false, &position) : Generate_Black_Moves(false, &position);
    for(int i = 0; i < position.numlegalmoves; i++)
    {
        position.Make_Move(position.LegalMoves[i]);
        nodes += Perft(&position, depth - 1);
        position.Undo_Move(position.LegalMoves[i]);
    }
    return nodes;
}
