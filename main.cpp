#include <iostream>
#include <cstdlib>
#include <ctime>

//Function that returns random long double weight.
long double randomWeight() {
    return (static_cast<long double>(rand()) / RAND_MAX) - 0.5;
}

//Add descriptor comment here
int randomizeWeights() {
//Finish here
}

//Program variables:
int board[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //Represents board state (0 = empty, 1 = Player, -1 = ANN) (Read from left to right, top to down (English style))
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


int main() {
    srand(time(0)); //Initial seed set for random num generation
    std::cout << "Welcome to Max\'s tic-tac-toe ANN!";

    //Function declarations
    randomizeWeights();
    return 0;
}
