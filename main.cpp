#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm> //Sorting
#include <fstream>	 //File input/output
#include <sstream>
#include <string>

int board[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Represents board state (0 = empty, 1 = Player, -1 = ANN) (Read from left to right, top to down (English style))
// Function that returns random long double weight or bias.
long double randomWeight()
{
	return (static_cast<long double>(rand()) / RAND_MAX) - 0.5;
}

// Function that displays ASCII render of board. Takes in chars annToken and playerToken:
int displayBoard(char annToken, char playerToken)
{

	for (int i = 0; i < 9; i++)
	{ // loop through array
		if ((i == 2) || (i == 5) || (i == 8))
		{ // Detect if on edge of board
			if (board[i] == -1)
			{ // ANN piece
				std::cout << annToken << std::endl;
				if (i != 8)
				{										   // Ensures last row dosen't have seperator at bottom
					std::cout << "---------" << std::endl; // Row seperator
				}
			}
			else if (board[i] == 1)
			{ // Player piece
				std::cout << playerToken << std::endl;
				if (i != 8)
				{ // Ensures last row dosen't have seperator at bottom
					std::cout
						<< "---------" << std::endl; // Row seperator
				}
			}
			else if (board[i] == 0)
			{ // Empty spot
				std::cout << "." << std::endl;
				if (i != 8)
				{ // Ensures last row dosen't have seperator at bottom
					std::cout
						<< "---------" << std::endl; // Row seperator
				}
			}
		}
		else
		{ // Middle or non-column piece
			if (board[i] == -1)
			{ // ANN piece
				std::cout << annToken << " | ";
			}
			else if (board[i] == 1)
			{ // Player piece
				std::cout << playerToken << " | ";
			}
			else if (board[i] == 0)
			{ // Empty spot
				std::cout << "." << " | ";
			}
		}
	}
	std::cout << std::endl;
	return 0;
}

