#include <iostream>
#include <cstdlib>
#include <ctime>

// Program variables:

// training flags:
bool stillRunningTraining = true;
int board[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Represents board state (0 = empty, 1 = Player, -1 = ANN) (Read from left to right, top to down (English style))
int gameNumber = 0;							// Keeps track of game number

// Weights
long double inputWeights[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};	// Input layer weights
long double layer1Weights[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Hidden layer #1 weights
long double layer2Weights[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Hidden layer #2 weights
long double layer3Weights[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Hidden layer #3 weights
long double outputWeights[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Output layer weights

// Biases
// Input layer has no biases.
long double layer1Biases[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Hidden layer #1 biases
long double layer2Biases[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Hidden layer #2 biases
long double layer3Biases[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Hidden layer #3 biases
long double outputBiases[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Output layer biases

// Values:
long double inputValues[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};  // Input layer values
long double layer1Values[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Hidden layer #1 values
long double layer2Values[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Hidden layer #2 values
long double layer3Values[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Hidden layer #3 values
long double outputValues[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Output layer values

// Bias activations:
bool layer1BiasActivations[9] = {false, false, false, false, false, false, false, false, false}; // Hidden layer #1 bias activations
bool layer2BiasActivations[9] = {false, false, false, false, false, false, false, false, false}; // Hidden layer #2 bias activations
bool layer3BiasActivations[9] = {false, false, false, false, false, false, false, false, false}; // Hidden layer #3 bias activations
bool outputBiasActivations[9] = {false, false, false, false, false, false, false, false, false}; // Output layer bias activations

// Weight activations:
bool inputWeightActivations[9] = {false, false, false, false, false, false, false, false, false};  // Input layer weight activations
bool layer1WeightActivations[9] = {false, false, false, false, false, false, false, false, false}; // Hidden layer #1 weight activations
bool layer2WeightActivations[9] = {false, false, false, false, false, false, false, false, false}; // Hidden layer #2 weight activations
bool layer3WeightActivations[9] = {false, false, false, false, false, false, false, false, false}; // Hidden layer #3 weight activations
bool outputWeightActivations[9] = {false, false, false, false, false, false, false, false, false}; // Output layer weight activations

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
				{										   // Ensures last row dosen't have seperator at bottom
					std::cout << "---------" << std::endl; // Row seperator
				}
			}
			else if (board[i] == 0)
			{ // Empty spot
				std::cout << "." << std::endl;
				if (i != 8)
				{										   // Ensures last row dosen't have seperator at bottom
					std::cout << "---------" << std::endl; // Row seperator
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

// Function that returns random long double weight or bias.
long double randomWeight()
{
	return (static_cast<long double>(rand()) / RAND_MAX) - 0.5;
}

// Randomizes neuron weights between -0.5 and 0.5
int randomizeWeights()
{
	std::cout << "Init model weights randomization:" << std::endl
			  << "Debug prints is true: " << std::endl;
	// Randomize input layer weights
	for (int i = 0; i < 9; i++)
	{
		inputWeights[i] = randomWeight();
		std::cout << "Input index " << i << ": " << inputWeights[i] << std::endl;
	}
	// Randomize hidden layer 1 weights
	for (int i = 0; i < 9; i++)
	{
		layer1Weights[i] = randomWeight();
		std::cout << "Hidden 1 index " << i << ": " << layer1Weights[i] << std::endl;
	}
	// Randomize hidden layer 2 weights
	for (int i = 0; i < 9; i++)
	{
		layer2Weights[i] = randomWeight();
		std::cout << "Hidden 2 index " << i << ": " << layer2Weights[i] << std::endl;
	}
	// Randomize hidden layer 3 weights
	for (int i = 0; i < 9; i++)
	{
		layer3Weights[i] = randomWeight();
		std::cout << "Hidden 3 index " << i << ": " << layer3Weights[i] << std::endl;
	}
	// Randomize output layer weights
	for (int i = 0; i < 9; i++)
	{
		outputWeights[i] = randomWeight();
		std::cout << "Output index " << i << ": " << outputWeights[i] << std::endl;
	}
	return 0;
}

// Randomizes neuron biases between -0.5 and 0.5
int randomizeBiases()
{
	std::cout << "Init model biases randomization:" << std::endl
			  << "Debug prints is true: " << std::endl;
	// Randomize hidden layer 1 biases
	for (int i = 0; i < 9; i++)
	{
		layer1Biases[i] = randomWeight();
		std::cout << "Hidden 1 index " << i << ": " << layer1Biases[i] << std::endl;
	}
	// Randomize hidden layer 2 biases
	for (int i = 0; i < 9; i++)
	{
		layer2Biases[i] = randomWeight();
		std::cout << "Hidden 2 index " << i << ": " << layer2Biases[i] << std::endl;
	}
	// Randomize hidden layer 3 biases
	for (int i = 0; i < 9; i++)
	{
		layer3Biases[i] = randomWeight();
		std::cout << "Hidden 3 index " << i << ": " << layer3Biases[i] << std::endl;
	}
	// Randomize output layer biases
	for (int i = 0; i < 9; i++)
	{
		outputBiases[i] = randomWeight();
		std::cout << "Output index " << i << ": " << outputBiases[i] << std::endl;
	}
	return 0;
}
// Checks for wins. Return Key: n = no win yet, a = ANN win, h = human win, d = draw
char checkBoard()
{
	char valid = NULL; // Check if win is detected
	if (board[0] == board[1] && board[1] == board[2] && board[1] != 0)
	{ // Check row 1
		if (board[1] == -1)
		{ // ANN win
			valid = 'a';
		}
		if (board[1] == 1)
		{ // Human win
		}
	}
	else if (board[3] == board[4] && board[4] == board[5] && board[4] != 0)
	{ // Check row 2
		if (board[4] == -1)
		{ // ANN win
			valid = 'a';
		}
		if (board[4] == 1)
		{ // Human win
			valid = 'h';
		}
	}
	else if (board[6] == board[7] && board[7] == board[8] && board[7] != 0)
	{ // Check row 3
		if (board[7] == -1)
		{ // ANN win
			valid = 'a';
		}
	}
	else if (board[0] == board[4] && board[8] == board[4] && board[4] != 0)
	{ // Check diagonal 1 from left
		if (board[4] == -1)
		{ // ANN win
			valid = 'a';
		}
		if (board[4] == 1)
		{ // Human win
			valid = 'h';
		}
	}
	else if (board[2] == board[4] && board[6] == board[4] && board[4] != 0)
	{ // Check diagonal 2 from right
		if (board[4] == -1)
		{ // ANN win
			valid = 'a';
		}
		if (board[4] == 1)
		{ // Human win
			valid = 'h';
		}
	}
	else if (board[0] != 0 && board[1] != 0 && board[2] != 0 && board[3] != 0 && board[4] != 0 && board[5] != 0 && board[6] != 0 && board[7] != 0 && board[8] != 0)
	{				 // Checks for draw IE: board full and no winner
		valid = 'd'; // Draw
	}
	else
	{
		std::cout << "Else triggered.";
		valid = 'n';
	}
	return valid;
}

// Runs ANN
int runANN()
{
	int outputIndex; // Index of output in array of board
	// Input neurons:
	for (int i = 0; i < 9; i++)
	{
		inputValues[i] = board[i] * inputWeights[i];
		in
	}
	// Layer 1
	for (int i = 0; i < 9; i++)
	{
		layer1Values[i] = inputValues[i] * layer1Weights[i] + layer1Biases[i];
	}
	// Layer 2 w/act funct
	for (int i = 0; i < 9; i++)
	{
		layer2Values[i] = ((layer1Values[0] + layer1Values[1] + layer1Values[2] + layer1Values[3] + layer1Values[4] + layer1Values[5] + layer1Values[6] + layer1Values[7] + layer1Values[8]) / 9) * layer2Weights[i] + layer2Biases[i];
		if (layer2Values[i] <= 0.5)
		{ // Activation function
			layer2Values[i] = 0;
		}
	}
	// Layer 3 w/act funct
	for (int i = 0; i < 9; i++)
	{
		layer3Values[i] = ((layer2Values[0] + layer2Values[1] + layer2Values[2] + layer2Values[3] + layer2Values[4] + layer2Values[5] + layer2Values[6] + layer2Values[7] + layer2Values[8]) / 9) * layer3Weights[i] + layer3Biases[i];
		if (layer3Values[i] <= 0.5)
		{ // Activation function
			layer3Values[i] = 0;
		}
	}
	// Output layer (no actfunct)
	for (int i = 0; i < 9; i++)
	{
		outputValues[i] = ((layer3Values[0] + layer3Values[1] + layer3Values[2] + layer3Values[3] + layer3Values[4] + layer3Values[5] + layer3Values[6] + layer3Values[7] + layer3Values[8]) / 9) * outputWeights[i] + outputBiases[i];
	}

	std::cout << std::endl
			  << std::endl
			  << "What is the index of the largest value? (Index starts at 0)" << std::endl
			  << std::endl
			  << outputValues[0] << std::endl
			  << outputValues[1] << std::endl
			  << outputValues[2] << std::endl
			  << outputValues[3] << std::endl
			  << outputValues[4] << std::endl
			  << outputValues[5] << std::endl
			  << outputValues[6] << std::endl
			  << outputValues[7] << std::endl
			  << outputValues[8] << std::endl;
	std::cin >> outputIndex;
	// Check if piece is already there
	if (board[outputIndex] != 0)
	{
		std::cout << std::endl
				  << std::endl
				  << "Piece already present. Sort it again." << std::endl;
		std::cout << std::endl
				  << std::endl
				  << "What is the index of the second largest value? (Index starts at 0)" << std::endl
				  << std::endl
				  << outputValues[0] << std::endl
				  << outputValues[1] << std::endl
				  << outputValues[2] << std::endl
				  << outputValues[3] << std::endl
				  << outputValues[4] << std::endl
				  << outputValues[5] << std::endl
				  << outputValues[6] << std::endl
				  << outputValues[7] << std::endl
				  << outputValues[8] << std::endl;
		std::cin >> outputIndex;
		// Check if piece is already there
		if (board[outputIndex] != 0)
		{
			std::cout << std::endl
					  << std::endl
					  << "Piece already present. Sort it again." << std::endl;
			std::cout << std::endl
					  << std::endl
					  << "What is the index of the third largest value? (Index starts at 0)" << std::endl
					  << std::endl
					  << outputValues[0] << std::endl
					  << outputValues[1] << std::endl
					  << outputValues[2] << std::endl
					  << outputValues[3] << std::endl
					  << outputValues[4] << std::endl
					  << outputValues[5] << std::endl
					  << outputValues[6] << std::endl
					  << outputValues[7] << std::endl
					  << outputValues[8] << std::endl;
			std::cin >> outputIndex;
			// Check if piece is already there
			if (board[outputIndex] != 0)
			{
				std::cout << std::endl
						  << std::endl
						  << "Piece already present. Sort it again." << std::endl;
				std::cout << std::endl
						  << std::endl
						  << "What is the index of the fourth largest value? (Index starts at 0)" << std::endl
						  << std::endl
						  << outputValues[0] << std::endl
						  << outputValues[1] << std::endl
						  << outputValues[2] << std::endl
						  << outputValues[3] << std::endl
						  << outputValues[4] << std::endl
						  << outputValues[5] << std::endl
						  << outputValues[6] << std::endl
						  << outputValues[7] << std::endl
						  << outputValues[8] << std::endl;
				std::cin >> outputIndex;
				// Check if piece is already there
				if (board[outputIndex] != 0)
				{
					std::cout << std::endl
							  << std::endl
							  << "Piece already present. Sort it again." << std::endl;
					std::cout << std::endl
							  << std::endl
							  << "What is the index of the fifth largest value? (Index starts at 0)" << std::endl
							  << std::endl
							  << outputValues[0] << std::endl
							  << outputValues[1] << std::endl
							  << outputValues[2] << std::endl
							  << outputValues[3] << std::endl
							  << outputValues[4] << std::endl
							  << outputValues[5] << std::endl
							  << outputValues[6] << std::endl
							  << outputValues[7] << std::endl
							  << outputValues[8] << std::endl;
					std::cin >> outputIndex;
					// Check if piece is already there
					if (board[outputIndex] != 0)
					{
						std::cout << std::endl
								  << std::endl
								  << "Piece already present. Sort it again." << std::endl;
						std::cout << std::endl
								  << std::endl
								  << "What is the index of the sixth largest value? (Index starts at 0)" << std::endl
								  << std::endl
								  << outputValues[0] << std::endl
								  << outputValues[1] << std::endl
								  << outputValues[2] << std::endl
								  << outputValues[3] << std::endl
								  << outputValues[4] << std::endl
								  << outputValues[5] << std::endl
								  << outputValues[6] << std::endl
								  << outputValues[7] << std::endl
								  << outputValues[8] << std::endl;
						std::cin >> outputIndex;
						// Check if piece is already there
						if (board[outputIndex] != 0)
						{
							std::cout << std::endl
									  << std::endl
									  << "Piece already present. Sort it again." << std::endl;
							std::cout << std::endl
									  << std::endl
									  << "What is the index of the seventh largest value? (Index starts at 0)" << std::endl
									  << std::endl
									  << outputValues[0] << std::endl
									  << outputValues[1] << std::endl
									  << outputValues[2] << std::endl
									  << outputValues[3] << std::endl
									  << outputValues[4] << std::endl
									  << outputValues[5] << std::endl
									  << outputValues[6] << std::endl
									  << outputValues[7] << std::endl
									  << outputValues[8] << std::endl;
							std::cin >> outputIndex;
							// Check if piece is already there
							if (board[outputIndex] != 0)
							{
								std::cout << std::endl
										  << std::endl
										  << "Piece already present. Sort it again." << std::endl;
								std::cout << std::endl
										  << std::endl
										  << "What is the index of the eigth largest value? (Index starts at 0)" << std::endl
										  << std::endl
										  << outputValues[0] << std::endl
										  << outputValues[1] << std::endl
										  << outputValues[2] << std::endl
										  << outputValues[3] << std::endl
										  << outputValues[4] << std::endl
										  << outputValues[5] << std::endl
										  << outputValues[6] << std::endl
										  << outputValues[7] << std::endl
										  << outputValues[8] << std::endl;
								std::cin >> outputIndex;
								// Check if piece is already there
								if (board[outputIndex] != 0)
								{
									std::cout << std::endl
											  << std::endl
											  << "Piece already present. Sort it again." << std::endl;
									std::cout << std::endl
											  << std::endl
											  << "What is the index of the least value? (Index starts at 0)" << std::endl
											  << std::endl
											  << outputValues[0] << std::endl
											  << outputValues[1] << std::endl
											  << outputValues[2] << std::endl
											  << outputValues[3] << std::endl
											  << outputValues[4] << std::endl
											  << outputValues[5] << std::endl
											  << outputValues[6] << std::endl
											  << outputValues[7] << std::endl
											  << outputValues[8] << std::endl;
									std::cin >> outputIndex;
								}
							}
						}
					}
				}
			}
		}
	}
	return outputIndex;
}

// Clears data after game
int clear()
{
	// Board
	board[0] = 0;
	board[1] = 0;
	board[2] = 0;
	board[3] = 0;
	board[4] = 0;
	board[5] = 0;
	board[6] = 0;
	board[7] = 0;
	board[8] = 0;
	inputValues[0] = 0;
	inputValues[1] = 0;
	inputValues[2] = 0;
	inputValues[3] = 0;
	inputValues[4] = 0;
	inputValues[5] = 0;
	inputValues[6] = 0;
	inputValues[7] = 0;
	inputValues[8] = 0;
	layer1Values[0] = 0;
	layer1Values[1] = 0;
	layer1Values[2] = 0;
	layer1Values[3] = 0;
	layer1Values[4] = 0;
	layer1Values[5] = 0;
	layer1Values[6] = 0;
	layer1Values[7] = 0;
	layer1Values[8] = 0;
	layer2Values[0] = 0;
	layer2Values[1] = 0;
	layer2Values[2] = 0;
	layer2Values[3] = 0;
	layer2Values[4] = 0;
	layer2Values[5] = 0;
	layer2Values[6] = 0;
	layer2Values[7] = 0;
	layer2Values[8] = 0;
	layer3Values[0] = 0;
	layer3Values[1] = 0;
	layer3Values[2] = 0;
	layer3Values[3] = 0;
	layer3Values[4] = 0;
	layer3Values[5] = 0;
	layer3Values[6] = 0;
	layer3Values[7] = 0;
	layer3Values[8] = 0;
	outputValues[0] = 0;
	outputValues[1] = 0;
	outputValues[2] = 0;
	outputValues[3] = 0;
	outputValues[4] = 0;
	outputValues[5] = 0;
	outputValues[6] = 0;
	outputValues[7] = 0;
	outputValues[8] = 0;
	inputWeightActivations[0] = false;
	inputWeightActivations[1] = false;
	inputWeightActivations[2] = false;
	inputWeightActivations[3] = false;
	inputWeightActivations[4] = false;
	inputWeightActivations[5] = false;
	inputWeightActivations[6] = false;
	inputWeightActivations[7] = false;
	inputWeightActivations[8] = false;
	layer1WeightActivations[0] = false;
	layer1WeightActivations[1] = false;
	layer1WeightActivations[2] = false;
	layer1WeightActivations[3] = false;
	layer1WeightActivations[4] = false;
	layer1WeightActivations[5] = false;

	return 0;
}

int main()
{
	// Game loop
	while (true)
	{
		// Clears data
		clear();
		// Prints board
		return 0;
	}
	// Uses activation arrays to adjust weights and biases of neurons.
	int trainModelFromGame(char res)
	{
		int adup = 1 / (2 + (gameNumber / 10)); // Number to add up for win.
		int addo = 1 / (2 + (gameNumber / 5));	// Number to subtract for loss.
		if (adup < 0.0001)
		{ // Checks for potential stagnation. SEE README.MD
			adup == 0.0001;
		}
		if (addo < 0.0001)
		{ // Check for potential stagnation. README.MD more info
			addo == 0.0001;
		}
		for (int i = 0; i < 9; i++)
		{ // Loop throuigh the various activation arrays repeat 9 times
			if (i == 0)
			{
				if (inputWeightActivations[i] == true)
				{
					if (res == 'a')
					{ // ANN win
						inputWeights[i] = inputWeights[i] + adup;
					}
					if (res == 'h')
					{ // Human win
						inputWeights[i] = inputWeights[i] - addo;
					}
				}
				if (layer1WeightActivations[i] == true)
				{
					if (res == 'a')
					{ // ANN win
						layer1Weights[i] = layer1Weights[i] + adup;
					}
					if (res == 'h')
					{ // Human win
						layer1Weights[i] = layer1Weights[i] - addo;
					}
				}
				if (layer2WeightActivations[i] == true)
				{
					if (res == 'a')
					{ // ANN win
						layer2Weights[i] = layer2Weights[i] + adup;
					}
					if (res == 'h')
					{ // Human win
						layer2Weights[i] = layer2Weights[i] - addo;
					}
				}
				if (layer3WeightActivations[i] == true)
				{
					if (res == 'a')
					{ // ANN win
						layer3Weights[i] = layer3Weights[i] + adup;
					}
					if (res == 'h')
					{ // Human win
						layer3Weights[i] = layer3Weights[i] - addo;
					}
				}
				if (outputWeightActivations[i] == true)
				{
					if (res == 'a')
					{ // ANN win
						outputWeights[i] = outputWeights[i] + adup;
					}
					if (res == 'h')
					{ // Human win
						outputWeights[i] = outputWeights[i] - addo;
					}
				}
				if (layer1Biases[i] == true)
				{
					if (res == 'a')
					{												  // ANN win
						layer1Biases[i] = layer1Biases[i] + adup / 4; // see README.MD
					}
					if (res == 'h')
					{												  // human wiun
						layer1Biases[i] = layer1Biases[i] - addo / 4; // see README.MD
					}
				}
				if (layer2Biases[i] == true)
				{
					if (res == 'a')
					{												  // ANN win
						layer2Biases[i] = layer2Biases[i] + adup / 4; // see README.MD
					}
					if (res == 'h')
					{												  // hunman win
						layer2Biases[i] = layer2Biases[i] - addo / 4; // see README.MD
					}
				}
				if (layer3Biases[i] == true)
				{
					if (res == 'a')
					{												  // ANN win
						layer3Biases[i] = layer3Biases[i] + adup / 4; // see README.MD
					}
					if (res == 'h')
					{												  // Human win
						layer3Biases[i] = layer3Biases[i] - addo / 4; // see README.MD
					}
				}
				if (outputBiases[i] == true)
				{
					if (res == 'a')
					{												  // ANN win
						outputBiases[i] = outputBiases[i] + adup / 4; // see README.MD
					}
					if (res == 'h')
					{												  // Human win
						outputBiases[i] = outputBiases[i] - addo / 4; // see README.MD
					}
				}
			}
		}
		return 0;
	}
	// Trains the model exactly for one game
	int trainOnce()
	{
		bool trainFunctRun = true; // For game loop
		char annToken;			   // ANN piece
		char playerToken;		   // Player piece
		int decision = -1;		   // Board index of decision of ANN (place piece) (-1 for now)
		std::cout << "Enter ANN token (piece): ";
		std::cin >> annToken;
		std::cout << "Enter player token (piece): ";
		std::cin >> playerToken;
		std::cout << std::endl
				  << std::endl
				  << std::endl; // Spacers for visual accuity
		while (trainFunctRun == true)
		{							 // One game
			char res = checkBoard(); // Save memory by only calling once per run
			std::cout << std::endl
					  << "Debug res token: " << res << std::endl;
			if (res == 'a' || res == 'h' || res == 'd')
			{
				std::cout << "If condition has been triggered.";
				trainModelFromGame(res);
				trainFunctRun = false;
				break;
			}
			displayBoard(annToken, playerToken);
			decision = runANN(); // Run the model
		}
		gameNumber++;
		clear() return 0;
	}

	int main()
	{
		srand(time(0)); // Initial seed set for random num generation
		std::cout << "Welcome to Max\'s tic-tac-toe ANN!" << std::endl;
		std::cout << "Debug board print:" << std::endl;
		displayBoard('O', 'X');
		randomizeWeights();
		std::cout << std::endl
				  << "Weight randomization complete." << std::endl
				  << std::endl
				  << "Beginning bias randomization:" << std::endl;
		randomizeBiases();
		std::cout << std::endl
				  << "Training initiating.";
		std::cout << std::endl
				  << "Init main loop." << std::endl;
		while (stillRunningTraining == true)
		{ // Main loop
			std::cout << std::endl
					  << "Main loop iteration." << std::endl
					  << std::endl;
			trainOnce();
		}
		return 0;
	}
