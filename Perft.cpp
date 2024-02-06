#include "Perft.h"
#include "Search.h"
#include "UCI.h"

Bitboard Root_Perft(int depth, bool PrintMoveList) {
	if (depth == 0) return 0;

	if (PrintMoveList)
		cout << "\n";

	Bitboard nodes = 0;
	pos.Current_Turn ? Generate_White_Moves(false, pos) : Generate_Black_Moves(false, pos);
	for (int i = 0; i < pos.numlegalmoves; i++) {
		pos.Make_Move(pos.LegalMoves[i]);

		if (PrintMoveList)
			Print_Move_List(i);

		int f = nodes;
		nodes += Perft(pos, depth - 1);

		if (PrintMoveList)
			cout << nodes - f << endl;

		pos.Undo_Move(pos.LegalMoves[i]);
	}
	return nodes;

}
int Perft(Position& posit, int depth) {
	if (depth == 1) {
		Position position(posit);
		position.Current_Turn ? Generate_White_Moves(false, position) : Generate_Black_Moves(false, position);
		return position.numlegalmoves;
	}

	if (depth == 0) return 1;

	Position position(posit);
	Bitboard nodes = 0;
	position.Current_Turn ? Generate_White_Moves(false, position) : Generate_Black_Moves(false, position);
	for (int i = 0; i < position.numlegalmoves; i++) {
		position.Make_Move(position.LegalMoves[i]);
		nodes += Perft(position, depth - 1);
		position.Undo_Move(position.LegalMoves[i]);
	}
	return nodes;
}

void Print_Move_List(int i) {
	for (int h = 0; h < 64; h++) {
		if (GeneralBoard[h] & pos.LegalMoves[i].From) {
			cout << PlayerMoves[h];
		}
	}

	for (int h = 0; h < 64; h++) {
		if (GeneralBoard[h] & pos.LegalMoves[i].To) {
			cout << PlayerMoves[h];
			if (pos.LegalMoves[i].Promotion) {
				switch (pos.LegalMoves[i].PromotionType) {
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
				default:
					break;
				}
			}
			cout << ": ";
		}
	}
}

void PerftSuite() {
	vector<string> TestPositions;
	vector<int> TestPositionDepths;
	vector<Bitboard> TestPositionNodes;

	/////////////////////////////////////////////////////////////////////////////////
	// Test positions
	/////////////////////////////////////////////////////////////////////////////////
	TestPositions.push_back("3k4/3p4/8/K1P4r/8/8/8/8 b - - 0 1");
	TestPositionDepths.push_back(6);
	TestPositionNodes.push_back(1134888);
	TestPositions.push_back("8/8/4k3/8/2p5/8/B2P2K1/8 w - - 0 1");
	TestPositionDepths.push_back(6);
	TestPositionNodes.push_back(1015133);
	TestPositions.push_back("8/8/1k6/2b5/2pP4/8/5K2/8 b - d3 0 1");
	TestPositionDepths.push_back(6);
	TestPositionNodes.push_back(1440467);
	TestPositions.push_back("5k2/8/8/8/8/8/8/4K2R w K - 0 1");
	TestPositionDepths.push_back(6);
	TestPositionNodes.push_back(661072);
	TestPositions.push_back("3k4/8/8/8/8/8/8/R3K3 w Q - 0 1");
	TestPositionDepths.push_back(6);
	TestPositionNodes.push_back(803711);
	TestPositions.push_back("r3k2r/1b4bq/8/8/8/8/7B/R3K2R w KQkq - 0 1");
	TestPositionDepths.push_back(4);
	TestPositionNodes.push_back(1274206);
	TestPositions.push_back("r3k2r/8/3Q4/8/8/5q2/8/R3K2R b KQkq - 0 1");
	TestPositionDepths.push_back(4);
	TestPositionNodes.push_back(1720476);
	TestPositions.push_back("2K2r2/4P3/8/8/8/8/8/3k4 w - - 0 1");
	TestPositionDepths.push_back(6);
	TestPositionNodes.push_back(3821001);
	TestPositions.push_back("8/8/1P2K3/8/2n5/1q6/8/5k2 b - - 0 1");
	TestPositionDepths.push_back(5);
	TestPositionNodes.push_back(1004658);
	TestPositions.push_back("4k3/1P6/8/8/8/8/K7/8 w - - 0 1");
	TestPositionDepths.push_back(6);
	TestPositionNodes.push_back(217342);
	TestPositions.push_back("8/P1k5/K7/8/8/8/8/8 w - - 0 1");
	TestPositionDepths.push_back(6);
	TestPositionNodes.push_back(92683);
	TestPositions.push_back("K1k5/8/P7/8/8/8/8/8 w - - 0 1");
	TestPositionDepths.push_back(6);
	TestPositionNodes.push_back(2217);
	TestPositions.push_back("8/k1P5/8/1K6/8/8/8/8 w - - 0 1");
	TestPositionDepths.push_back(7);
	TestPositionNodes.push_back(567584);
	TestPositions.push_back("8/8/2k5/5q2/5n2/8/5K2/8 b - - 0 1");
	TestPositionDepths.push_back(4);
	TestPositionNodes.push_back(23527);


	/////////////////////////////////////////////////////////////////////////////////
	//
	/////////////////////////////////////////////////////////////////////////////////

	int FailCount = 0;

	cout << "\n\nStarting the perft test suite:\n" << endl;

	for (int i = 0; i < TestPositions.size(); i++) {
		cout << "Position " << i + 1 << "/" << TestPositions.size() << ": " << TestPositions[i] << endl;

		Parse_Fen(TestPositions[i]);

		Bitboard nodes = Root_Perft(TestPositionDepths[i], false);

		cout << "Expected: " << TestPositionNodes[i] << ", got: " << nodes;

		// print the right amount of dashes so the pass/fails all line up
		for (int j = 0; j < 50 - (to_string(nodes).length() * 2); j++) {
			cout << "-";
		}

		cout << ">   ";

		if (TestPositionNodes[i] == nodes)
			cout << "PASS\n\n" << endl;
		else {
			cout << "FAIL\n\n" << endl;
			FailCount++;
		}
	}

	cout << "============================================\n" << endl;
	cout << "Perft suite results: " << TestPositions.size() - FailCount << " passed, " << FailCount << " failed\n" << endl;
}
