# AI played Tic Tac Toe game
This program uses Alpha-Beta-Pruning and MinMax-A-B algorithms to implement a tic-tac-toe game platform.

The user can choose from three different evaluation functions to be computer's "strategy". 

The computers will use those strategies to play against each other.


## Approach
The AI players each have one stratedgy. The stratedgy is a function to generate the score of a board condition. The AI player will use its stratedgy to calculate scores for all possible conditions based on the current board, and then proceed to do the best move. The possible future conditions are generated as a tree structure.

MinMax-A-B algorithm is used to find the most highest score out of all possible conditions in the future.

Alpha-Beta-Pruning is used to significantly eliminated the useless calculations which don't lead to win.

## Strategies
Currently, the program supports three different strategies.

#### Textbook's
Evaluation function form textbook

Calculate score based on board occupation and check condition.
- Each occupied row, column and diagnal earns 1 point.
- Each two connected marks (check condition) earns 20 points.

#### Po-Teng's
Evaluation function created by Po-Teng

Calculate score based on winning condition, check condition and middle position bonus.
- Each win condition earns high score (40)
- Each lose condition loses high score (-20)
- Each check condition has 1 score.
- The middle position has additional 3 points.

#### Tommy's
Evaluation function created by Tommy

Calculate score based on positions on the board. 
- Middle = 3
- Diagnal = 2
- Other = 1

## Depth of algorithm
Currently, the supported depths are 2 and 4 only.


## Installation

Build and run the [cpp file](main.cpp).

When the program starts:

- Input the max depth when it asks. (can only be 2 or 4)

- Choose evaluation functions for player1 and player2.

Player 1 will be the first player and use X mark.

The rest of process is automatic. 


## Detailed Report
More information of this program can be found by checking [Report](Report.pdf)
