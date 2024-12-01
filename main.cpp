#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm> //Sorting
#include <fstream>	 //File input/output

// Program variables:

// bool flags:
bool stillRunningTraining = true;
int board[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Represents board state (0 = empty, 1 = Player, -1 = ANN) (Read from left to right, top to down (English style))
int gameNumber = 0;							// Keeps track of game number
bool saveMetadata;

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
	char valid = ' '; // Check if win is detected
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
	else if (board[0] == board[3] && board[3] == board[6] && board[3] != 0)
	{ // Check collumn 1
		if (board[3] == -1)
		{ // ann win
			valid = 'a';
		}
		if (board[3] == 1)
		{ // human win
			valid = 'h';
		}
	}
	else if (board[1] == board[4] && board[4] == board[7] && board[4] != 0)
	{ // Check collumn 2
		if (board[4] == -1)
		{ // ann win
			valid = 'a';
		}
		if (board[4] == 1)
		{ // human win
			valid = 'h';
		}
	}
	else if (board[2] == board[5] && board[5] == board[8] && board[5] != 0)
	{ // Check collumn 3
		if (board[5] == -1)
		{ // ann win
			valid = 'a';
		}
		if (board[5] == 1)
		{ // human win
			valid = 'h';
		}
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
	long double minValue = 0.2;
	int outputIndex; // Index of output in array of board
	// Input neurons:
	for (int i = 0; i < 9; i++)
	{
		inputValues[i] = board[i] * inputWeights[i];
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
		if (layer2Values[i] <= minValue)
		{ // Activation function
			layer2Values[i] = 0;
		}
	}
	// Layer 3 w/act funct
	for (int i = 0; i < 9; i++)
	{
		layer3Values[i] = ((layer2Values[0] + layer2Values[1] + layer2Values[2] + layer2Values[3] + layer2Values[4] + layer2Values[5] + layer2Values[6] + layer2Values[7] + layer2Values[8]) / 9) * layer3Weights[i] + layer3Biases[i];
		if (layer3Values[i] <= minValue)
		{ // Activation function
			layer3Values[i] = 0;
		}
	}
	// Output layer (no actfunct)
	for (int i = 0; i < 9; i++)
	{
		outputValues[i] = ((layer3Values[0] + layer3Values[1] + layer3Values[2] + layer3Values[3] + layer3Values[4] + layer3Values[5] + layer3Values[6] + layer3Values[7] + layer3Values[8]) / 9) * outputWeights[i] + outputBiases[i];
	}
	long double orgOutputValues[9];
	// Copy each element from outputValues to orgOutputValues
	for (int i = 0; i < 9; ++i)
	{
		orgOutputValues[i] = outputValues[i];
	}
	std::sort(outputValues, outputValues + 9, std::greater<long double>()); // Sorts output values from highest to lowest
	for (int i = 0; i < 9; i++)
	{
		long double target = outputValues[i];
		for (int j = 0; j < 9; j++)
		{
			if (target == orgOutputValues[j] && board[j] == 0)
			{ // If empty spot
				outputIndex = j;
				break;
			}
		}
	}
	std::cout << std::endl
			  << std::endl
			  << "Debug print. Output index: " << outputIndex << std::endl
			  << std::endl;
	return outputIndex; // Returns index of output in array of board
}

// Clears data after game
int clear()
{
	if (saveMetadata == true) {
//Save copy of game and ANN metadata.
	std::ofstream outfile;
	outfile.open("metaData.txt", std::ios_base::app);
	if (!outfile.is_open()) {
    std::cerr << "Error opening file." << std::endl;
    return 1;
}

	outfile << "Game " << gameNumber << " Data: " << std::endl;
	outfile << "Board: " << std::endl;
	for (int i = 0; i < 9; i++)
	{ // loop through array
		if ((i == 2) || (i == 5) || (i == 8))
		{ // Detect if on edge of board
			if (board[i] == -1)
			{ // ANN piece
				outfile << "A"; // A for ANN
				if (i != 8)
				{										   // Ensures last row dosen't have seperator at bottom
					outfile << "---------" << std::endl; // Row seperator
				}
			}
			else if (board[i] == 1)
			{ // Player piece
				outfile << "P" << std::endl;
				if (i != 8)
				{										   // Ensures last row dosen't have seperator at bottom
					outfile << "---------" << std::endl; // Row seperator
				}
			}
			else if (board[i] == 0)
			{ // Empty spot
				outfile << "." << std::endl;
				if (i != 8)
				{										   // Ensures last row dosen't have seperator at bottom
					outfile << "---------" << std::endl; // Row seperator
				}
			}
		}
		else
		{ // Middle or non-column piece
			if (board[i] == -1)
			{ // ANN piece
				outfile << "A" << " | ";
			}
			else if (board[i] == 1)
			{ // Player piece
				outfile << "P" << " | ";
			}
			else if (board[i] == 0)
			{ // Empty spot
				outfile << "." << " | ";
			}
		}
	}
	outfile << "Input layer weights: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << inputWeights[j] << std::endl;
	}
	outfile << "Input layer values: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << inputValues[j] << std::endl;
	}
	outfile << "Layer 1 weights: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << layer1Weights[j] << std::endl;
	}
	outfile << "Layer 1 biases: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << layer1Biases[j] << std::endl;
	}
	outfile << "Layer 1 values: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << layer1Values[j] << std::endl;
	}
	outfile << "Layer 2 weights: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << layer2Weights[j] << std::endl;
	}
	outfile << "Layer 2 biases: " << std::endl;
	for (int j = 0; j < 9; j++) {
	    outfile << layer2Biases[j] << std::endl;
	}
	outfile << "Layer 2 values: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << layer2Values[j] << std::endl;
	}
	outfile << "Layer 3 weights: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << layer3Weights[j] << std::endl;
	}
	outfile << "Layer 3 biases: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << layer3Biases[j] << std::endl;
	}
	outfile << "Layer 3 values: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << layer3Values[j] << std::endl;
	}
	outfile << "Output layer values: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << outputValues[j] << std::endl;
	}
	outfile << "Input layer activations: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << inputWeightActivations[j] << std::endl;
	}
	outfile << "Layer 1 activations: " << std::endl;
	for (int j = 0; j < 9; j++) {
		outfile << layer1WeightActivations[j] << std::endl;
	}
	outfile << std::endl;
}
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
	layer1WeightActivations[6] = false;
	layer1WeightActivations[7] = false;
	layer1WeightActivations[8] = false;
	layer2WeightActivations[0] = false;
	layer2WeightActivations[1] = false;
	layer2WeightActivations[2] = false;
	layer2WeightActivations[3] = false;
	layer2WeightActivations[4] = false;
	layer2WeightActivations[5] = false;
	layer2WeightActivations[6] = false;
	layer2WeightActivations[7] = false;
	layer2WeightActivations[8] = false;
	layer3WeightActivations[0] = false;
	layer3WeightActivations[1] = false;
	layer3WeightActivations[2] = false;
	layer3WeightActivations[3] = false;
	layer3WeightActivations[4] = false;
	layer3WeightActivations[5] = false;
	layer3WeightActivations[6] = false;
	layer3WeightActivations[7] = false;
	layer3WeightActivations[8] = false;
	outputWeightActivations[0] = false;
	outputWeightActivations[1] = false;
	outputWeightActivations[2] = false;
	outputWeightActivations[3] = false;
	outputWeightActivations[4] = false;
	outputWeightActivations[5] = false;
	outputWeightActivations[6] = false;
	outputWeightActivations[7] = false;
	outputWeightActivations[8] = false;

	layer1BiasActivations[0] = false;
	layer1BiasActivations[1] = false;
	layer1BiasActivations[2] = false;
	layer1BiasActivations[3] = false;
	layer1BiasActivations[4] = false;
	layer1BiasActivations[5] = false;
	layer1BiasActivations[6] = false;
	layer1BiasActivations[7] = false;
	layer1BiasActivations[8] = false;
	layer2BiasActivations[0] = false;
	layer2BiasActivations[1] = false;
	layer2BiasActivations[2] = false;
	layer2BiasActivations[3] = false;
	layer2BiasActivations[4] = false;
	layer2BiasActivations[5] = false;
	layer2BiasActivations[6] = false;
	layer2BiasActivations[7] = false;
	layer2BiasActivations[8] = false;
	layer3BiasActivations[0] = false;
	layer3BiasActivations[1] = false;
	layer3BiasActivations[2] = false;
	layer3BiasActivations[3] = false;
	layer3BiasActivations[4] = false;
	layer3BiasActivations[5] = false;
	layer3BiasActivations[6] = false;
	layer3BiasActivations[7] = false;
	layer3BiasActivations[8] = false;
	outputBiasActivations[0] = false;
	outputBiasActivations[1] = false;
	outputBiasActivations[2] = false;
	outputBiasActivations[3] = false;
	outputBiasActivations[4] = false;
	outputBiasActivations[5] = false;
	outputBiasActivations[6] = false;
	outputBiasActivations[7] = false;
	outputBiasActivations[8] = false;

	return 0;
}

// Uses activation arrays to adjust weights and biases of neurons.
int trainModelFromGame(char res)
{
	long double adup = 2 / (1 + (static_cast<long double>(gameNumber) / 200)); // Number to add up for win.
	long double addo = 2 / (1 + (static_cast<long double>(gameNumber) / 101)); // Number to subtract for loss.
	std::cout << std::endl
			  << std::endl
			  << "Debug print. adup: " << adup << " addo: " << addo << " Game number: " << gameNumber << std::endl
			  << std::endl;
	if (adup < 0.1)
	{ // Checks for potential stagnation. SEE README.MD
		adup == 0.1;
	}
	if (addo < 0.1)
	{ // Check for potential stagnation. README.MD more info
		addo == 0.1;
	}
	for (int i = 0; i < 9; i++)
	{ // Loop throuigh the various activation arrays repeat 9 times
		if (layer1Values[i] > 0)
		{
			if (res == 'a')
			{ // If ann won
				layer1Biases[i] += adup / 4;
				layer1Weights[i] += addo;
				inputWeights[i] += addo;
			}
			if (res == 'h')
			{ // If human won
				layer1Biases[i] -= adup / 4;
				layer1Weights[i] -= addo;
				inputWeights[i] -= addo;
			}
		}
		if (layer2Values[i] > 0)
		{
			if (res == 'a')
			{ // If ann won
				layer1Biases[i] += adup / 4;
				layer1Weights[i] += addo;
				layer2Biases[i] += adup / 4;
				layer2Weights[i] += addo;
			}
			if (res == 'h')
			{ // If human won
				layer1Biases[i] -= adup / 4;
				layer1Weights[i] -= addo;
				layer2Biases[i] -= adup / 4;
				layer2Weights[i] -= addo;
			}
		}
		if (layer3Values[i] > 0)
		{
			if (res == 'a')
			{ // If ann won
				layer2Biases[i] += adup / 4;
				layer2Weights[i] += addo;
				layer3Biases[i] += adup / 4;
				layer3Weights[i] += addo;
			}
			if (res == 'h')
			{ // If human won
				layer2Biases[i] -= adup / 4;
				layer2Weights[i] -= addo;
				layer3Biases[i] -= adup / 4;
				layer3Weights[i] -= addo;
			}
		}
		if (outputValues[i] > 0)
		{
			if (res == 'a')
			{ // If ann won
				layer3Biases[i] += adup / 4;
				layer3Weights[i] += addo;
				outputBiases[i] += adup / 4;
				outputWeights[i] += addo;
			}
			if (res == 'h')
			{ // If human won
				layer3Biases[i] -= adup / 4;
				layer3Weights[i] -= addo;
				outputBiases[i] -= adup / 4;
				outputWeights[i] -= addo;
			}
		}
	}
	return 0;
}

// Manually coded bot. Doesn't use ANN. Used to train.
int bot()
{
	return 0;
}

// Trains the model exactly for one game
int trainOnce()
{

	bool trainFunctRun = true; // For game loop
	char annToken;			   // ANN piece
	char playerToken;		   // Player piece
	int decision = -1;		   // Board index of decision of ANN (place piece) (-1 for now)
	bool botVAnn = true;	   // ANN v ANN
	std::string botVAnnInput;
	int annCounter = 0;
	std::string hFirst; // If human go first
	int hMove;			// Human move index
	std::cout << "Would you like to train in ANN (or bot) vs ANN mode?: (Y/n): ";
	std::cin >> botVAnnInput;
	std::cout << std::endl
			  << "Debug print. botVAnnInput: " << botVAnnInput << std::endl;
	if (botVAnnInput == "Y" || botVAnnInput == "y" || botVAnnInput == "yes" || botVAnnInput == "1" || botVAnnInput == "Yes" || botVAnnInput == "YES")
	{
		botVAnn = true;
		std::cout << "Debug print: If statement triggered.";
	}
	else
	{
		botVAnn = false;
		std::cout << "Debug print: Else statement triggered.";
	}
	if (botVAnn == false)
	{
		std::cout << "Enter ANN token (piece): ";
		std::cin >> annToken;
		std::cout << "Enter player token (piece): ";
		std::cin >> playerToken;
		std::cout << std::endl
				  << std::endl
				  << std::endl; // Spacers for visual accuity
		std::cout << std::endl
				  << std::endl
				  << "Will you go first?: (Y/n): ";
		std::cin >> hFirst;
		if (hFirst == "Y" || hFirst == "y" || hFirst == "Yes" || hFirst == "yes")
		{ // Check if human goes first.
			std::cout << std::endl
					  << std::endl
					  << "Board:" << std::endl
					  << std::endl;
			displayBoard(annToken, playerToken);
			std::cout << std::endl
					  << std::endl;
			std::cout << "What move index will you make?: ";
			std::cin >> hMove;
			board[hMove] = 1;

			while (trainFunctRun == true)
			{							 // One game
				char res = checkBoard(); // Save memory by only calling once per run
				std::cout << std::endl
						  << "Debug res token: " << res << std::endl;
				if (res == 'a' || res == 'h' || res == 'd')
				{
					std::cout << "If condition has been triggered.";
					gameNumber += 1; // Add game num before dependent fnct call
					trainModelFromGame(res);
					trainFunctRun = false;
					clear();
					break;
				}
				displayBoard(annToken, playerToken);
				decision = runANN();  // Run the model
				board[decision] = -1; // Make move.
				res = checkBoard();	  // Save memory by only calling once per run
				std::cout << std::endl
						  << "Debug res token: " << res << std::endl;
				if (res == 'a' || res == 'h' || res == 'd')
				{
					std::cout << "If condition has been triggered.";
					gameNumber += 1; // Add game num before dependent fnct call
					trainModelFromGame(res);
					trainFunctRun = false;
					clear();
					break;
				}
				std::cout << std::endl
						  << std::endl
						  << "Board:" << std::endl
						  << std::endl;
				displayBoard(annToken, playerToken);
				std::cout << std::endl
						  << std::endl
						  << "What index will you make your move?: ";
				std::cin >> hMove;
				board[hMove] = 1; // Make move.

				std::cout << std::endl
						  << std::endl;
			}
		}
	}
	if (botVAnn == true)
	{
		std::cout << std::endl
				  << "NOTE: Training in ANN vs ANN or bot vs ANN mode. How many games will you have it play against itself for?: ";
		std::cin >> annCounter;
		std::cout << std::endl
				  << "Will you train in bot vs ANN mode? (Y/n:)";
		std::string mode; // Set mode based on user input
		std::cin >> mode;
		annToken = 'X';
		playerToken = 'O';

		for (int x = 0; x < annCounter; x++)
		{
			while (trainFunctRun == true)
			{							 // One game
				char res = checkBoard(); // Save memory by only calling once per run
				if (res == 'a' || res == 'h' || res == 'd')
				{
					gameNumber += 1; // Add game num before dependent fnct call
					trainModelFromGame(res);
					trainFunctRun = false;
					clear();
					break;
				}
				decision = runANN();  // Run the model
				board[decision] = -1; // Make move.
				res = checkBoard();	  // Save memory by only calling once per run
				if (res == 'a' || res == 'h' || res == 'd')
				{
					gameNumber += 1; // Add game num before dependent fnct call
					trainModelFromGame(res);
					trainFunctRun = false;
					clear();
					break;
				}
				if (mode == "y" || mode == "Y" || mode == "yes" || mode == "Yes")

				{

					// Train against manually coded bot
					board[bot()] = 1;
				}
				else
				{ // ANN vs ANN
					board[runANN()] = 1;
				}

				res = checkBoard(); // Save memory by only calling once per run
				if (res == 'a' || res == 'h' || res == 'd')
				{
					gameNumber += 1; // Add game num before dependent fnct call
					trainModelFromGame(res);
					trainFunctRun = false;
					clear();
					break;
				}
			}
			trainFunctRun = true; // Reset so game can play again.
		}
	}
	return 0;
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
	std::string mode;
		std::cout << std::endl
				  << "Main loop iteration." << std::endl
				  << std::endl << "Is metadata collection allowed for the next game? (y/n): ";
		std::cin >> mode;
		if (mode == "n" || mode == "N" || mode == "no" || mode == "No")
		{
			saveMetadata = false;
			std::cout << std::endl
					  << "Metadata collection disabled." << std::endl;
		}
		else
		{
			saveMetadata = true;
			std::cout << std::endl
					  << "Metadata collection enabled." << std::endl;
		}
		trainOnce();
	}
	return 0;
}
