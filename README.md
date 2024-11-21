# Purpose


This program is designed for the purpose of furthering my understanding of the C++ programming language. It is not intended to be used as the basis for any actual projects.


**BY VIEWING THIS REPOSITORY, YOU ACKNOWLEDGE THAT YOU HAVE READ THE TERMS OF SERVICE, CONTAINED IN THE LICENSE FILE, AND ARE LEGALLY BOUND TO IT.**

# Outline:


This project will utilize a ANN, and ASCII depictions of the Tic-Tac-Toe board. It will run locally on user's cpu. The ANN will be manually programmed, with no libraries.
Idea:
Input layer consists of 9 neurons, each with an input normalized to either 1, or -1. 1 will indicate a move by the player, and -1 will indicate a move made by the ANN. IE:
Board visualization:
User is X, ANN is O:
```
X | O | X
---------
O | X | O
---------
X | O | X
```
The input layer will be:
```
{1, -1, 1, -1, 1, -1, 1, -1, 1}
```
This will enable the ANN to start playing either player, and be able to continue previous games.
Output will consist of 9 neurons, with a weight between 1 and -1. The highest output will become the spot where the ANN is to place their piece. If the highest output already has a piece in it, the second highest, then the 3rd, and so on will be considered.

# Neurons


Each neuron will have the following properties:
- A weight between 1 and -1
- A bias from between 1 and -1
- A value from between 1 and -1
- A function to calculate the value of the neuron
- A function to update the weight and bias of the neuron
For the input neuron, the input is multiplied by the weight, and the bias is added to the result. The value is then normalized to between 1 and -1 by dividing by the sum of the absolute value of the weight and the bias. It's then fed into a binary function, where if the total is more than 0.5, it activates. Same is similar for hidden layer neurons, but the input from every connected neuron is multiplied by the weight, summed up, averaged, and then normalized to between 1 and -1 by dividing by the sum of the absolute value of the weight and the bias. The value is then fed into a binary function, where if the total is more than 0.5, it activates. For output neurons, there is no activation function.

# Architecture


Will run locally on user's cpu.
Input layer: 9 neurons
Hidden layer #1: 9 neurons
Hidden layer #2: 9 neurons
Hidden layer #3: 9 neurons
Output layer: 9 neurons

# Training


ALL VALUES WILL BE NORMALIZED TO C++ DOUBLES (rounding will be incorporated).
The ANN will be trained using the following method:
- The ANN will start with random weights between -0.5 and 0.5.
- The ANN will play a game of Tic-Tac-Toe against a human player
During the game, a win/loss/draw detection function will be run after every move.
- The ANN will then add 1/(2+(game#/10) (minimum will be 0.01 to prevent stagnation) to the weights of the neurons that were activated when the ANN won, and subtract 1/(2+(game#/5) (minimum will be 0.01 to prevent stagnation) from the weights of the neurons that were activated when the human player won.
- The ANN will then play another game of Tic-Tac-Toe against a human player
There are plans to implement ANN vs ANN training.
#Win/Loss detection
- A program will be written to detect if the game has been won, lost, or is a draw

# Requirements


Minimum (Not recommended):
Note that in this configuration, modern operating systems will leave the program with almost nothing to work with, and the program will either lag, or will be unable to run.
- C++XX
- Clang or G++ (C++ compiler)
- 4 gb RAM
- 1.1 Ghz, dual core CPU (Remember, the program will run locally on your cpu)
Recommended:
- C++17 or newer
- Clang or G++ (C++ compiler)
- 16 gb RAM
- 3 Ghz, 6 core CPU (Remember, the program will run locally on your cpu)
Best:
Optimal performance
- C++20 or newer
- Clang or G++ (C++ compiler)
- 32 gb RAM
- 4 Ghz, 8 core CPU (Remember, the program will run locally on your cpu)
