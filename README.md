# Purpose


This program is designed for the purpose of furthering my understanding of the C++ programming language. It is not intended to be used as the basis for any actual projects.


**BY VIEWING THIS REPOSITORY, YOU ACKNOWLEDGE THAT YOU HAVE READ THE TERMS OF SERVICE, CONTAINED IN THE LICENSE FILE, AND ARE LEGALLY BOUND TO IT.**

# Outline


This project will utilize an ANN, and ASCII depictions of the Tic-Tac-Toe board. In the ASCII depiction, the Xs and Os will be displayed, but empty spaces will be replaced with a "." It will run locally on the user's CPU. The ANN will be manually programmed, with no libraries.
Idea:
The input layer consists of 9 neurons, each with an input normalized to either 1, or -1. 1 will indicate a move by the player, 0 will indicate an empty spot, and -1 will indicate a move made by the ANN. IE:
Board visualization:
User is X, ANN is O:
```
X | O | X
---------
O | X | .
---------
X | O | X
```
The input layer will be:
```
{1, -1, 1, -1, 1, 0, 1, -1, 1}
```
This will enable the ANN to start playing either player, and be able to continue previous games.
Output will consist of 9 neurons, with a weight between 1 and -1. The highest output will become the spot where the ANN is to place their piece. If the highest output already has a piece in it, the second highest, then the 3rd, and so on will be considered.

# Neurons


Each neuron will have the following properties:
- A weight between 1 and -1
- A bias from between 1 and -1
- A value between 1 and -1
- A function to calculate the value of the neuron
- A function to update the weight and bias of the neuron
For the input neuron, the input is multiplied by the weight, and the bias is added to the result. The value is then normalized to between 1 and -1 by dividing by the sum of the absolute value of the weight and the bias. It's then fed into a binary function, where if the total is more than 0.5, it activates. Same is similar for hidden layer neurons, but the input from every connected neuron is multiplied by the weight, summed up, averaged, and then normalized to between 1 and -1 by dividing by the sum of the absolute value of the weight and the bias. The value is then fed into a binary function, where if the total is more than 0.5, it activates. For output neurons, there is no activation function.

# Architecture


Will run locally on the user's CPU.
Input layer: 9 neurons
Hidden layer #1: 9 neurons
Hidden layer #2: 9 neurons
Hidden layer #3: 9 neurons
Output layer: 9 neurons

# Training


ALL VALUES WILL BE NORMALIZED TO C++ LONG DOUBLES.
The ANN will be trained using the following method:
- The ANN will start with random weights and biases between -0.5 and 0.5.
- The ANN will play a game of Tic-Tac-Toe against a human player
During the game, a win/loss/draw detection function will be run after every move.
- The ANN will then add 10/(2+(game#/10) (minimum will be 0.0001 to prevent stagnation) to the weights and a quarter of that to the biases of the neurons that were activated when the ANN won, and subtract 10/(2+(game#/5) (minimum will be 0.0001 to prevent stagnation) from the weights and a quarter of that from the biases of the neurons that were activated when the human player won.
 
**NOTE THAT THE BIASES ARE EXEMPT FROM THE 0.0001 RULE, THEY GO TO A MINNIMUM OF 0.000025, WHICH IS 1/4th OF THE MINNIMUM WEIGHT**.
- The ANN will then play another game of Tic-Tac-Toe against a human player
There are plans to implement ANN vs ANN training.
#Win/Loss Detection
- A program will be written to detect if the game has been won, lost, or is a draw

# Requirements (IF RUNNING IN MODERN OS)


**Minimum** *(Not recommended)***:**
*Note that in this configuration, modern operating systems will leave the program with almost nothing to work with, and the program will either lag or will be unable to run.*
- C++XX
- Clang or G++ (C++ compiler)
- 4 GB RAM
- 1.1 GHz, dual-core CPU (Remember, the program will run locally on your CPU)

**Recommended:**
- C++17 or newer
- Clang or G++ (C++ compiler)
- 16 GB RAM
- 3 Ghz, 6 core CPU (Remember, the program will run locally on your CPU)

**Best:**
*Optimal performance*
- C++20 or newer
- Clang or G++ (C++ compiler)
- 32 GB RAM
- 4 Ghz, 8-core CPU (Remember, the program will run locally on your CPU)
