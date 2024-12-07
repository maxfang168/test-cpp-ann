**This is the readme for the second version of the program. This will not repeat the mentioned details found in the original readme (Storage/Archives/version0/README.md)**


# Training:


Will completely scrap training process.
Will instead do this:
For the first 100 games, the ANN will play against the player. When it loses, it will lose a certain amount, *p*, in the weights and 1/4th of that in the biases that were activated when it lost. And vice-versa for the wins. However, if it draws, it will get a small award, *p*/8.

For the next 900 games, it will play against the manually coded bot. The same penalties apply.

After the 1000 game, it will be tested against a benchmark:
The benchmark will contain the following tests:

- Move discovery: The ANN will be fed 50 board states with easily discoverable wining moves. Each will be worth 20 points.  Example:

```cpp
{-1, -1, 0, 0, 1, 1, 0, 0, -1, -1}
```

-Defense Rate: The ANN will be fed 50 board states with places where their opponent could win in one turn. Each will be worth 20 points. Example:

```cpp
{1, 1, 0, 0, 1, -1, 0, 0, 0, -1}
```

- Full game win rate: The ANN will play 100 games against the player, but whether they win or lose will be recorded. Each game is worth 10 points.

Final score calculation:
Sum of all the points gained, then divided by 3000 (Total number of points possible).

The penalties, *p* mentioned:

Before first benchmark:

Initial values of *p* = 0.5:
After each benchmark, if the score is more than 80%, then *p* is multiplied by 0.95. If the score is more than 90%, then *p* is multiplied by 0.9. If the score is more than 95%, then *p* is multiplied by 0.8. If the score is more than 97%, then *p* is multiplyed by 0.7. If the score is more than 99%, then *p* is multiplyed by 0.1. If the score is 100%, then *p* is multiplyed by 0.01.

There will be options to train for a specific number of games, or to train until a certain benchmark score is reached.