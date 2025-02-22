#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

// Constants
const int BOARD_SIZE = 9;
const long double INITIAL_LEARNING_RATE = 4.0L;

// Program variables
struct ANN {
    long double inputWeights[BOARD_SIZE] = {0};
    long double layer1Weights[BOARD_SIZE] = {0};
    long double layer2Weights[BOARD_SIZE] = {0};
    long double layer3Weights[BOARD_SIZE] = {0};
    long double outputWeights[BOARD_SIZE] = {0};
    
    long double layer1Biases[BOARD_SIZE] = {0};
    long double layer2Biases[BOARD_SIZE] = {0};
    long double layer3Biases[BOARD_SIZE] = {0};
    long double outputBiases[BOARD_SIZE] = {0};
    
    long double inputValues[BOARD_SIZE] = {0};
    long double layer1Values[BOARD_SIZE] = {0};
    long double layer2Values[BOARD_SIZE] = {0};
    long double layer3Values[BOARD_SIZE] = {0};
    long double outputValues[BOARD_SIZE] = {0};
};

struct GameState {
    int board[BOARD_SIZE] = {0};
    int gameNumber = 0;
    bool saveMetadata = false;
    std::string savefile;
};

// Function prototypes
void displayBoard(const GameState& state, char annToken, char playerToken);
long double randomWeight();
void randomizeWeights(ANN& ann);
void randomizeBiases(ANN& ann);
char checkBoard(const GameState& state);
void annClear(ANN& ann);
void clear(GameState& state, ANN& ann);
int runANN(const GameState& state, ANN& ann);
void trainModelFromGame(char res, GameState& state, ANN& ann);
bool boardIsEmpty(const GameState& state);
bool boardIndexIsEmpty(const GameState& state, int index);
char checkWinFromManualBoard(const int newBoard[BOARD_SIZE]);
int bot(const GameState& state);
void trainOnce(GameState& state, ANN& ann);

// Optimized display board
void displayBoard(const GameState& state, char annToken, char playerToken) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        char cell = '.';
        if (state.board[i] == -1) cell = annToken;
        else if (state.board[i] == 1) cell = playerToken;

        std::cout << cell;
        if (i % 3 == 2) {
            std::cout << "\n";
            if (i < 6) std::cout << "---------\n";
        } else {
            std::cout << " | ";
        }
    }
    std::cout << "\n";
}

// Random weight generation
long double randomWeight() {
    return (static_cast<long double>(rand()) / RAND_MAX - 0.5L);
}

// Weight initialization
void randomizeWeights(ANN& ann) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        ann.inputWeights[i] = randomWeight();
        ann.layer1Weights[i] = randomWeight();
        ann.layer2Weights[i] = randomWeight();
        ann.layer3Weights[i] = randomWeight();
        ann.outputWeights[i] = randomWeight();
    }
}

// Bias initialization
void randomizeBiases(ANN& ann) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        ann.layer1Biases[i] = randomWeight();
        ann.layer2Biases[i] = randomWeight();
        ann.layer3Biases[i] = randomWeight();
        ann.outputBiases[i] = randomWeight();
    }
}

// Optimized board checking
char checkBoard(const GameState& state) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        // Rows
        if (state.board[i*3] != 0 && 
            state.board[i*3] == state.board[i*3+1] && 
            state.board[i*3] == state.board[i*3+2]) {
            return (state.board[i*3] == -1) ? 'a' : 'h';
        }
        // Columns
        if (state.board[i] != 0 && 
            state.board[i] == state.board[i+3] && 
            state.board[i] == state.board[i+6]) {
            return (state.board[i] == -1) ? 'a' : 'h';
        }
    }

    // Check diagonals
    if (state.board[0] != 0 && state.board[0] == state.board[4] && state.board[0] == state.board[8])
        return (state.board[0] == -1) ? 'a' : 'h';
    if (state.board[2] != 0 && state.board[2] == state.board[4] && state.board[2] == state.board[6])
        return (state.board[2] == -1) ? 'a' : 'h';

    // Check draw
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (state.board[i] == 0) return 'n';
    }
    return 'd';
}

// ANN clearing optimized
void annClear(ANN& ann) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        ann.inputValues[i] = 0;
        ann.layer1Values[i] = 0;
        ann.layer2Values[i] = 0;
        ann.layer3Values[i] = 0;
        ann.outputValues[i] = 0;
    }
}

// Optimized ANN execution
int runANN(const GameState& state, ANN& ann) {
    annClear(ann);
    const long double scaleFactor = 10.0L;

    // Input layer
    for (int i = 0; i < BOARD_SIZE; ++i) {
        ann.inputValues[i] = state.board[i] * scaleFactor * ann.inputWeights[i];
    }

    // Hidden layers with optimized sum calculation
    auto processLayer = [](const long double* inputs, const long double* weights, 
                          const long double* biases, long double* outputs) {
        long double sum = 0.0L;
        for (int i = 0; i < BOARD_SIZE; ++i) sum += inputs[i];
        sum /= BOARD_SIZE;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            outputs[i] = sum * weights[i] + biases[i];
            if (outputs[i] <= 0) outputs[i] = 0;
        }
    };

    processLayer(ann.inputValues, ann.layer1Weights, ann.layer1Biases, ann.layer1Values);
    processLayer(ann.layer1Values, ann.layer2Weights, ann.layer2Biases, ann.layer2Values);
    processLayer(ann.layer2Values, ann.layer3Weights, ann.layer3Biases, ann.layer3Values);

    // Output layer
    long double sum = 0.0L;
    for (int i = 0; i < BOARD_SIZE; ++i) sum += ann.layer3Values[i];
    sum /= BOARD_SIZE;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        ann.outputValues[i] = sum * ann.outputWeights[i] + ann.outputBiases[i];
    }

    // Find best valid move
    int bestMove = -1;
    long double maxVal = -std::numeric_limits<long double>::max();
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (state.board[i] == 0 && ann.outputValues[i] > maxVal) {
            maxVal = ann.outputValues[i];
            bestMove = i;
        }
    }

    return bestMove;
}

// Training function optimized
void trainModelFromGame(char res, GameState& state, ANN& ann) {
    const long double adup = std::max(4.0L / (1.0L + state.gameNumber/200.0L), 0.5L);
    const long double addo = std::max(4.0L / (1.0L + state.gameNumber/101.0L), 0.5L);
    const long double addr = 2.0L / (2.0L + state.gameNumber/400.0L);

    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (ann.layer1Values[i] > 0) {
            if (res == 'a') {
                ann.layer1Biases[i] += adup/4;
                ann.layer1Weights[i] += addo;
                ann.inputWeights[i] += addo;
            } else if (res == 'h') {
                ann.layer1Biases[i] -= addo/4;
                ann.layer1Weights[i] -= addo;
                ann.inputWeights[i] -= addo;
            } else {
                ann.layer1Biases[i] -= addr/4;
                ann.layer1Weights[i] -= addr;
                ann.inputWeights[i] -= addr;
            }
        }
    }
}

int main() {
    srand(time(0));
    GameState state;
    ANN ann;

    std::cout << "Welcome to Optimized Tic-Tac-Toe ANN!\n";
    randomizeWeights(ann);
    randomizeBiases(ann);

    bool running = true;
    while (running) {
        std::cout << "\nGame #" << state.gameNumber << "\n";
        trainOnce(state, ann);
    }

    return 0;
}