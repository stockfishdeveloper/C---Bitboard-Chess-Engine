#include "Bitboard.h"
#include "Search.h"
typedef unsigned long long int Bitboard;
using namespace std;
//This is an array containing one bit set in each bitboard corresponding to the index of the array; the square A1 is the first (0th) element
const Bitboard GeneralBoard[64] =
{
    1, 2, 4, 8, 16, 32, 64, 128,
    256, 512, 1024, 2048, 4096, 8192, 16384, 32768,
    65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608,
    16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648LL,
    4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888,
    1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328,
    281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968,
    72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808ULL
};
Bitboard Eigth_Rank_White = 18374686479671623680ULL;//For masking out pawn pushes to the eagth rank for each side--white and black
Bitboard Eigth_Rank_Black = 255;//See last comment
Bitboard Seventh_Rank_White = 71776119061217280;//For masking out pawn pushes to the eagth rank for each side--white and black
Bitboard Seventh_Rank_Black = 65280;//See last comment
Bitboard CurrZobkey = 0;

//Contains the squares that a knight on a given index can move to. For example, the 0th element has the bits of b3 and c2 set
const Bitboard Knight_Lookup_Table[64] =
{
    132096, 329728, 659712, 1319424, 2638848, 5277696, 10489856, 4202496,
    33816580, 84410376, 168886289, 337772578, 675545156, 1351090312, 2685403152LL, 1075839008LL,
    8657044482, 21609056261, 43234889994, 86469779988, 172939559976, 345879119952, 687463207072, 275414786112,
    2216203387392, 5531918402816, 11068131838464, 22136263676928, 44272527353856, 88545054707712, 175990581010432, 70506185244672,
    567348067172352, 1416171111120896, 2833441750646784, 5666883501293568, 11333767002587136, 22667534005174272, 45053588738670592, 18049583422636032,
    145241105196122112, 362539804446949376, 725361088165576704, 1450722176331153408, 2901444352662306816, 5802888705324613632, 11533718717099671552ULL, 4620693356194824192,
    288234782788157440, 576469569871282176, 1224997833292120064, 2449995666584240128, 4899991333168480256, 9799982666336960512ULL, 1152939783987658752, 2305878468463689728,
    1128098930098176, 2257297371824128, 4796069720358912, 9592139440717824, 19184278881435648, 38368557762871296, 4679521487814656, 9077567998918656

};

//This one is the same as the Knight_Lookup_Table except that this one is for kings
const Bitboard King_Lookup_Table[64] =
{
    770, 1797, 3594, 7188, 14376, 28752, 57504, 49216,
    197123, 460039, 920078, 1840156, 3680312, 7360624, 14721248, 12599488,
    50463488, 117769984, 235539968, 471079936, 942159872, 1884319744, 3768639488LL, 3225468928LL,
    12918652928, 30149115904, 60298231808, 120596463616, 241192927232, 482385854464, 964771708928, 825720045568,
    3307175149568, 7718173671424, 15436347342848, 30872694685696, 61745389371392, 123490778742784, 246981557485568, 211384331665408,
    846636838289408, 1975852459884544, 3951704919769088, 7903409839538176, 15806819679076352, 31613639358152704, 63227278716305408, 54114388906344448,
    216739030602088448, 505818229730443264, 1011636459460886528, 2023272918921773056, 4046545837843546112, 8093091675687092224, 16186183351374184448ULL, 13853283560024178688ULL,
    144959613005987840, 362258295026614272, 724516590053228544, 1449033180106457088, 2898066360212914176, 5796132720425828352, 11592265440851656704ULL, 4665729213955833856
};

Bitboard H_Pawn_Mask = 9259542123273814144ULL;//For masking out A and H pawns so that they cannot capture off of the end of the board
Bitboard A_Pawn_Mask = 72340172838076673;
Bitboard G_Pawn_Mask = 4629771061636907072;
Bitboard B_Pawn_Mask = 144680345676153346;
Bitboard F_Pawn_Mask = 2314885530818453536;
Bitboard C_Pawn_Mask = 289360691352306692;
Bitboard E_Pawn_Mask = 1157442765409226768;
Bitboard D_Pawn_Mask = 578721382704613384;

//Contains a string representation of the squares of the chess board; for example, the 0th element in the array is "a1"
string PlayerMoves[64] =
{

    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",

    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",

    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",

    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",

    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",

    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",

    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",

    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"

};

void Print_Board()
{
    for( int h = 0; h < 64; h++)
    {
        if(GeneralBoard[h] & pos.White_King)
        {
            cout << "White king is on " << PlayerMoves[h] << endl;
        }

        if(GeneralBoard[h] & pos.Black_King)
        {
            cout << "Black king is on " << PlayerMoves[h] << endl;
        }

        if(GeneralBoard[h] & pos.White_Queens)
        {
            cout << "White queen is on " << PlayerMoves[h] << endl;
        }

        if(GeneralBoard[h] & pos.Black_Queens)
        {
            cout << "Black queen is on " << PlayerMoves[h] << endl;
        }

        if(GeneralBoard[h] & pos.White_Rooks)
        {
            cout << "White rook is on " << PlayerMoves[h] << endl;
        }

        if(GeneralBoard[h] & pos.Black_Rooks)
        {
            cout << "Black rook is on " << PlayerMoves[h] << endl;
        }

        if(GeneralBoard[h] & pos.White_Bishops)
        {
            cout << "White Bishop is on " << PlayerMoves[h] << endl;
        }

        if(GeneralBoard[h] & pos.Black_Bishops)
        {
            cout << "Black Bishop is on " << PlayerMoves[h] << endl;
        }

        if(GeneralBoard[h] & pos.White_Knights)
        {
            cout << "White Knight is on " << PlayerMoves[h] << endl;
        }

        if(GeneralBoard[h] & pos.Black_Knights)
        {
            cout << "Black Knight is on " << PlayerMoves[h] << endl;
        }

        if(GeneralBoard[h] & pos.White_Pawns)
        {
            cout << "White Pawn is on " << PlayerMoves[h] << endl;
        }

        if(GeneralBoard[h] & pos.Black_Pawns)
        {
            cout << "Black Pawn is on " << PlayerMoves[h] << endl;
        }
        //cout << "White king: " << White_King << endl;
    }

    if(pos.Current_Turn)
    {
        cout << "It is White's turn" << endl;
    }
    else
    {
        cout << "It is Black's turn" << endl;
    }
}
