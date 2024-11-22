#include <iostream>
#include <cstdlib>
#include <ctime>

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

//Function that returns random long double weight.
long double randomWeight() {
    return (static_cast<long double>(rand()) / RAND_MAX) - 0.5;
}

//Randomizes neuron weights between -0.5 and 0.5
int randomizeWeights() {
    std::cout << "Init model weights randomization:" << endl;
// Randomize input layer weights
    for (int i = 0; i < 9; i++) {
        inputWeights[i] = randomWeight();
        std::cout << inputWeights[i] << std::endl;
    }
// Randomize hidden layer 1 weights
    for (int i = 0; i < 9; i++)  {
        layer1Weights[i] = randomWeight();
        std::cout << layer1Weights[i] << std::endl;
    }
    // Randomize hidden layer 2 weights
    for (int i = 0; i < 9; i++)  {
        layer2Weights[i] = randomWeight();
        std::cout << layer2Weights[i] << std::endl;
    }
    // Randomize hidden layer 3 weights
    for (int i = 0; i < 9; i++)  {
        layer3Weights[i] = randomWeight();
        std::cout << layer3Weights[i] << std::endl;
    }
// Randomize output layer weights
    for (int i = 0; i < 9; i++) {
        outputWeights[i] = randomWeight();
        std::cout << outputWeights[i] << std::endl;
    }
    
}


int main() {
    srand(time(0)); //Initial seed set for random num generation
    std::cout << "Welcome to Max\'s tic-tac-toe ANN!";

    //Function declarations
    randomizeWeights();
    return 0;
}
