#include <iostream>
#include <cstdlib>
#include <ctime>

//Program variables:
int board[9] = {1, 0, -1, 0, 1, 0, -1, 0, 0}; //Represents board state (0 = empty, 1 = Player, -1 = ANN) (Read from left to right, top to down (English style))
int gameNumber=0; //Keeps track of game number

//Weights
double inputWeights[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //Input layer weights
double layer1Weights[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //Hidden layer #1 weights
double layer2Weights[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //Hidden layer #2 weights
double layer3Weights[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //Hidden layer #3 weights
double outputWeights[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //Output layer weights

//Biases
//Input layer has no biases.
double layer1Biases[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //Hidden layer #1 biases
double layer2Biases[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //Hidden layer #2 biases
double layer3Biases[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //Hidden layer #3 biases
double outputBiases[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //Output layer biases

//Function that displays ASCII render of board. Takes in chars annToken and playerToken:
int displayBoard(char annToken, char playerToken) {

    for (int i = 0; i < 9; i++) { //loop through array
        if ((i == 2) || (i == 5) || (i == 8)) { //Detect if on edge of board
            if (board[i] == -1) { //ANN piece
                std::cout << annToken << std::endl;
                if (i != 8) { //Ensures last row dosen't have seperator at bottom
                std::cout << "---------" << std::endl; //Row seperator
                }
            }
            else if (board[i] == 1) { //Player piece
                std::cout << playerToken << std::endl;
                if (i != 8) { //Ensures last row dosen't have seperator at bottom
                std::cout << "---------" << std::endl; //Row seperator
                }
            }
            else if (board[i] == 0) { //Empty spot
                std::cout << "." << std::endl;
                if (i != 8) { //Ensures last row dosen't have seperator at bottom
                std::cout << "---------" << std::endl; //Row seperator
                }
            }
        }
        else { //Middle or non-column piece
            if (board[i] == -1) { //ANN piece
                std::cout << annToken << " | ";
            }
            else if (board[i] == 1) { //Player piece
                std::cout << playerToken << " | ";
            }
            else if (board[i] == 0) { //Empty spot
                std::cout << "." << " | ";
            }
        }
    }
    std::cout << std::endl;
    /*
    std::cout << "Board (Debug print): " << std::endl << std::endl;
    std::cout << board[0] << " | " << board[1] << " | " << board[2] << std::endl; //Row 1
    std::cout << "---------" << std::endl; //Row seperator
    std::cout << board[3] << " | " << board[4] << " | " << board[5] << std::endl; //Row 2
    std::cout << "---------" << std::endl; //Row seperator
    std::cout << board[6] << " | " << board[7] << " | " << board[8] << std::endl << std::endl; //Row 3
    */
    return 0;
}

//Function that returns random long double weight.
long double randomWeight() {
    return (static_cast<long double>(rand()) / RAND_MAX) - 0.5;
}

//Randomizes neuron weights between -0.5 and 0.5
int randomizeWeights() {
    std::cout << "Init model weights randomization:" << std::endl << "Debug prints is true: " << std::endl;
// Randomize input layer weights
    for (int i = 0; i < 9; i++) {
        inputWeights[i] = randomWeight();
        std::cout << "Input index " << i << ": " << inputWeights[i] << std::endl;
    }
// Randomize hidden layer 1 weights
    for (int i = 0; i < 9; i++)  {
        layer1Weights[i] = randomWeight();
        std::cout << "Hidden 1 index " << i << ": " <<layer1Weights[i] << std::endl;
    }
    // Randomize hidden layer 2 weights
    for (int i = 0; i < 9; i++)  {
        layer2Weights[i] = randomWeight();
        std::cout << "Hidden 2 index " << i << ": " << layer2Weights[i] << std::endl;
    }
    // Randomize hidden layer 3 weights
    for (int i = 0; i < 9; i++)  {
        layer3Weights[i] = randomWeight();
        std::cout << "Hidden 3 index " << i << ": " << layer3Weights[i] << std::endl;
    }
// Randomize output layer weights
    for (int i = 0; i < 9; i++) {
        outputWeights[i] = randomWeight();
        std::cout << "Output index " << i << ": " << outputWeights[i] << std::endl;
    }
    return 0;
}


int main() {
    srand(time(0)); //Initial seed set for random num generation
    std::cout << "Welcome to Max\'s tic-tac-toe ANN!" << std::endl;
    displayBoard('O', 'X');
    randomizeWeights();
    return 0;
}
