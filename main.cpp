#include <iostream>
#include <string>
#include <sstream>


using namespace std;


struct nodeMove
{
    int number;         //the number of this node in same depth
    int infoBoard[9];   //9 positions on the board
    nodeMove* nodeChild[9]; //maximum number of children is 9
};

struct result
{
    int value;
    string path;
};



int depthMax = 4; //the maximum depth for this algorithm
int widthMax = 9; //the maximum possible moves in each move

int sumTest = 0;
int alpha = -9999;
int beta = 9999;

int chooseEvaluationP1 = 0;
int chooseEvaluationP2 = 0;

int totalCheckEveryTurn = 0;


void test()
{
    sumTest++;
    cout <<"this #"<<sumTest<<endl;
}




int char_to_int(char a)
{
    int b = (int)a - 48;
    return b;
}

string int_to_string(int a)
{
    stringstream buffer;
    buffer << a;
    string b = buffer.str();
    return b;
}


//display the board
void display_board(int* listBoard)
{
    for (int i = 0; i < widthMax; i++)
    {
        if (listBoard[i] == 3)
        {
            cout << "x\t";
        }
        else if (listBoard[i] == 5)
        {
            cout << "o\t";
        }
        else if (listBoard[i] == 2)
        {
            cout << "[]\t";
        }
        if (i % 3 == 2)
        {
            cout << endl << endl;
        }
    }
}


//build the tree. create and link children to parents "recursively"
//it gets the reference of pointer to the parent node and the current depth,
//and returns the total number of nodes of it and its sub-tree
int create_tree(nodeMove*& parent, int* currentBoard, int depth)
{
    int sum = 0;    //the total number of all parent's children

    if (depth <= 0) { return 1; }   //reach the depth limit

    if (parent == NULL) //create root
    {
        nodeMove* nodeNew = new nodeMove;
        parent = nodeNew;
        parent->number = 0;
        for (int i = 0; i < widthMax; i++)
        {
            parent->infoBoard[i] = 0;
            parent->nodeChild[i] = NULL;
        }
    }

    //append children to parents
    //(widthMax - depthMax + depth) will be 9, 8, 7, 6 ... etc
    for (int i = 0; i < (widthMax - depthMax + depth); i++)
    {
        nodeMove* nodeNew = new nodeMove;
        nodeNew->number = i;
        parent->nodeChild[i] = nodeNew;
        sum += create_tree(nodeNew, currentBoard, depth - 1);
    }
    if (depth == 4) {cout <<"sum = "<<sum<<endl;}   //test message

    //return current node + all its children
    return 1 + sum;
}


void delete_tree(){}


string move_gen(nodeMove* parent, bool player)
{
    string stringSucc = "";
    int countNode = 0;  //which child to work with

    //read parent board
    for (int i = 0; i < widthMax; i++)
    {
        //if any position out of 9 can be put next move
        if (parent->infoBoard[i] == 2)
        {
            //put generated board info into children (generate children)
            for (int j = 0; j < widthMax; j++)
            {
                //empty position
                if (j == i)
                {
                    //put next move depends on player
                    //we don't have 9 children in each level so it's not 9 times
                    if (player == true)
                    {
                        parent->nodeChild[countNode]->infoBoard[j] = 3;
                    }
                    else    //opponent's move
                    {
                        parent->nodeChild[countNode]->infoBoard[j] = 5;
                    }
                }
                else    //not empty position
                {
                    //copy rest of 8 positions
                    parent->nodeChild[countNode]->infoBoard[j] = parent->infoBoard[j];
                }
            }

            //record which nodes are generated
            stringSucc += int_to_string(countNode);
            countNode++;
        }
    }

    //return a string describing which nodes are generated.
    return stringSucc;
}


//evaluation function form textbook
int evaluationText(nodeMove* position, bool player)
{

    int playblock,
        oppblock;

    int playcount = 0,
        oppcount = 0;

    int score;

    int* grid;

    playblock = 5;
    oppblock = 3;

    grid = position->infoBoard;

    if (grid[0] != playblock && grid[1] != playblock && grid[2] != playblock)
        playcount++;

    if (grid[3] != playblock && grid[4] != playblock && grid[5] != playblock)
        playcount++;

    if (grid[6] != playblock && grid[7] != playblock && grid[8] != playblock)
        playcount++;

    if (grid[0] != playblock && grid[3] != playblock && grid[6] != playblock)
        playcount++;

    if (grid[1] != playblock && grid[4] != playblock && grid[7] != playblock)
        playcount++;

    if (grid[2] != playblock && grid[5] != playblock && grid[8] != playblock)
        playcount++;

    if (grid[0] != playblock && grid[4] != playblock && grid[8] != playblock)
        playcount++;

    if (grid[2] != playblock && grid[4] != playblock && grid[6] != playblock)
        playcount++;


    if (grid[0] != oppblock && grid[1] != oppblock && grid[2] != oppblock)
        oppcount++;

    if (grid[3] != oppblock && grid[4] != oppblock && grid[5] != oppblock)
        oppcount++;

    if (grid[6] != oppblock && grid[7] != oppblock && grid[8] != oppblock)
        oppcount++;

    if (grid[0] != oppblock && grid[3] != oppblock && grid[6] != oppblock)
        oppcount++;

    if (grid[1] != oppblock && grid[4] != oppblock && grid[7] != oppblock)
        oppcount++;

    if (grid[2] != oppblock && grid[5] != oppblock && grid[8] != oppblock)
        oppcount++;

    if (grid[0] != oppblock && grid[4] != oppblock && grid[8] != oppblock)
        oppcount++;

    if (grid[2] != oppblock && grid[4] != oppblock && grid[6] != oppblock)
        oppcount++;


    score = playcount - oppcount;

    if (grid[0] * grid[1] * grid[2] == 18)
        score = 20;
    else if (grid[3] * grid[4] * grid[5] == 18)
        score = 20;
    else if (grid[6] * grid[7] * grid[8] == 18)
        score = 20;
    else if (grid[0] * grid[3] * grid[6] == 18)
        score = 20;
    else if (grid[1] * grid[4] * grid[7] == 18)
        score = 20;
    else if (grid[2] * grid[5] * grid[8] == 18)
        score = 20;
    else if (grid[0] * grid[4] * grid[8] == 18)
        score = 20;
    else if (grid[2] * grid[4] * grid[6] == 18)
        score = 20;

    if (grid[0] * grid[1] * grid[2] == 50)
        score = -20;
    else if (grid[3] * grid[4] * grid[5] == 50)
        score = -20;
    else if (grid[6] * grid[7] * grid[8] == 50)
        score = -20;
    else if (grid[0] * grid[3] * grid[6] == 50)
        score = -20;
    else if (grid[1] * grid[4] * grid[7] == 50)
        score = -20;
    else if (grid[2] * grid[5] * grid[8] == 50)
        score = -20;
    else if (grid[0] * grid[4] * grid[8] == 50)
        score = -20;
    else if (grid[2] * grid[4] * grid[6] == 50)
        score = -20;

    if (player == false)
        score = -1 * score;

    return score;


}


//evaluation function created by Po-Teng
int evaluationPodeng(nodeMove* nodeCurrent, bool player)
{
    int* grip = nodeCurrent->infoBoard;
    int valueCheck;
    int countCheck = 0;
    int center = 0;
    int playerMark;
    int win = 0;
    int valueWin;
    int lose = 0;
    int valueLose;

    if (player)
    {
        playerMark = 3;
        valueCheck = 18;
        valueWin = 27;
        valueLose = 125;
    }
    else
    {
        playerMark = 5;
        valueCheck = 50;
        valueWin = 125;
        valueLose = 27;
    }

    int row[3] = {1, 1, 1};
    int col[3] = {1, 1, 1};
    int dia[3] = {1, 1, 1};

    if (grip[4] == playerMark)
    {
        center += 3;
    }

    for (int i = 0; i < 9; i += 3)
    {
        col[0] *= grip[0 + i];
        col[1] *= grip[1 + i];
        col[2] *= grip[2 + i];
    }
    for (int i = 0; i < 3; i ++)
    {
        row[0] *= grip[0 + i];
        row[1] *= grip[3 + i];
        row[2] *= grip[6 + i];
    }
    dia[0] = grip[0] * grip[4] * grip[8];
    dia[1] = grip[2] * grip[4] * grip[6];

    for (int i = 0; i < 3; i++)
    {
        if (row[i] == valueCheck) { countCheck++; }
        if (col[i] == valueCheck) { countCheck++; }
        if (dia[i] == valueCheck) { countCheck++; }

        if (row[i] == valueWin) { win += 40; }
        if (col[i] == valueWin) { win += 40; }
        if (dia[i] == valueWin) { win += 40; }

        if (row[i] == valueLose) { lose -= 20; }
        if (col[i] == valueLose) { lose -= 20; }
        if (dia[i] == valueLose) { lose -= 20; }
    }

    if (depthMax%2 == 1)
    {
        return 5 + win + lose + center + countCheck;
    }
    else
    {
        return (5 + win + lose + center + countCheck);
    }
}


//Evaluation function created by Tommy
int evaluationTommy(nodeMove* position, bool player)
{
    int mark = 0;

    int score = 0;

    int* grid;

    if (player == true)
       mark = 3;
    else
       mark = 5;

    grid = position->infoBoard;

    if (grid[4] == mark)
        score = score + 3;

    if (grid[0] == mark)
        score = score + 2;

    if (grid[2] == mark)
        score = score + 2;

    if (grid[6] == mark)
        score = score + 2;

    if (grid[8] == mark)
        score = score + 2;

    if (grid[1] == mark)
        score = score + 1;

    if (grid[3] == mark)
        score = score + 1;

    if (grid[5] == mark)
        score = score + 1;

    if (grid[7] == mark)
        score = score + 1;

    if (player == false)
        score = -1 * score;

    return score;
}



int evaluation(nodeMove* nodeCurrent, bool player)
{
    totalCheckEveryTurn++;
    if (player == true)    //player1
    {
        if (chooseEvaluationP1 == 1)
        {
            return evaluationText(nodeCurrent, player);
        }
        else if (chooseEvaluationP1 == 2)
        {
            return evaluationPodeng(nodeCurrent, player);
        }
        else if (chooseEvaluationP1 == 3)
        {
            return evaluationTommy(nodeCurrent, player);
        }
    }
    else if (player == false)    //player2
    {
        if (chooseEvaluationP2 == 1)
        {
            return evaluationText(nodeCurrent, player);
        }
        else if (chooseEvaluationP2 == 2)
        {
            return evaluationPodeng(nodeCurrent, player);
        }
        else if (chooseEvaluationP2 == 3)
        {
            return evaluationTommy(nodeCurrent, player);
        }
    }
}


result alpha_beta_search(nodeMove* , int , bool );
result max_value(nodeMove* , int , bool );
result min_value(nodeMove* , int , bool );
bool CheckWin(nodeMove*, bool);


result alpha_beta_search(nodeMove* nodeCurrent, int depth, bool player)
{
    result resultFinal;

    resultFinal = max_value(nodeCurrent, depth, player);

    //return action and value
    return resultFinal;
}

result max_value(nodeMove* nodeCurrent, int depth, bool player)
{

    result resultCurrent;
    result resultSucc;

    if (depth >= depthMax || CheckWin(nodeCurrent, player || CheckWin(nodeCurrent, !player))) //leaves
    {

        resultCurrent.value = evaluation(nodeCurrent, player);
        resultCurrent.path = int_to_string( nodeCurrent->number );
        return resultCurrent;
    }
    else if (depth < depthMax)
    {
        string successors ="";

        int scoreBest = 0;
        int valueNew = 0;

        //expand the node
        //move_gen gives a list of nodes

        successors = move_gen(nodeCurrent, player);

        //if successors is empty, return current values
        if (successors == "")
        {
            resultCurrent.value = evaluation(nodeCurrent, player);
            resultCurrent.path = int_to_string( nodeCurrent->number );
            return resultCurrent;
        } //no more move
        else //if it's not empty, examine each element in successors
        {
            scoreBest = -999999; //best score for any element in successors

            for (int i = 0; i < successors.length(); i++)
            {
                resultSucc = min_value(nodeCurrent->nodeChild[ char_to_int( successors[i] ) ], depth + 1, player);
                valueNew = resultSucc.value;

                if (valueNew > scoreBest)
                {
                    scoreBest = valueNew;
                    resultCurrent.path =  int_to_string(i);
                }

                if (scoreBest >= beta)	//Pruning in max_value
                {
                    resultCurrent.value = scoreBest;
                    if (depth != 0)
                    {
                        return resultCurrent;
                    }
                }
                if (scoreBest > alpha)
                {
                    alpha = scoreBest;
                }
            }

            resultCurrent.value = scoreBest;
            return resultCurrent;
        }
    }

}

result min_value(nodeMove* nodeCurrent, int depth, bool player)
{

    result resultCurrent;
    result resultSucc;
    if (depth >= depthMax || CheckWin(nodeCurrent, player) || CheckWin(nodeCurrent, !player)) //leaves
    {
        resultCurrent.value = evaluation(nodeCurrent, player);
        resultCurrent.path = int_to_string( nodeCurrent->number );
        return resultCurrent;
    }
    else if (depth < depthMax)
    {
        string successors ="";

        int scoreBest = 0;
        int valueNew = 0;

        //expand the node
        //move_gen gives a list of nodes

        successors = move_gen(nodeCurrent, !player);

        //if successors is empty, return current values
        if (successors == "")
        {
            resultCurrent.value = evaluation(nodeCurrent, player);
            resultCurrent.path = int_to_string( nodeCurrent->number );
            return resultCurrent;
        } //no more move
        else //if it's not empty, examine each element in successors
        {
            scoreBest = 999999; //best score for any element in successors

            for (int i = 0; i < successors.length(); i++)
            {
                resultSucc = max_value(nodeCurrent->nodeChild[ char_to_int( successors[i] ) ], depth + 1, player);
                valueNew = resultSucc.value;
                //
                if (valueNew < scoreBest)
                {
                    scoreBest = valueNew;
                    resultCurrent.path = int_to_string(i);
                }

                if (scoreBest <= alpha)		//Pruning in min_value
                {
                    resultCurrent.value = scoreBest;
                    return resultCurrent;
                }
                if (scoreBest < beta)
                {
                    beta = scoreBest;
                }
            }

            resultCurrent.value = scoreBest;
            return resultCurrent;
        }
    }


}


result alpha_beta_search_old(nodeMove* nodeCurrent, int depth, bool player)
{
    result resultCurrent;
    result resultSucc;

    if (depth < depthMax)
    {
        string successors ="";

        int scoreBest = 0;
        int valueNew = 0;
        string pathBest = "";

        //expand the node
        //move_gen gives a list of nodes

        successors = move_gen(nodeCurrent, player);

        //if successors is empty, return current values
        if (successors == "")
        {
            resultCurrent.value = evaluation(nodeCurrent, player);
            resultCurrent.path = "";
            return resultCurrent;
        } //no more move
        else //if it's not empty, examine each element in successors
        {
            scoreBest = -999999; //best score for any element in successors

            //assume the best succ is the first child
            pathBest = "0";

            for (int i = 0; i < successors.length(); i++)
            {
                //convert the char in successors[i] to int
                resultSucc = alpha_beta_search(nodeCurrent->nodeChild[ char_to_int( successors[i] ) ], depth + 1, !player);
                valueNew = -(resultSucc.value);

                //As the root also gets the reverse value, we choose the smaller one.
                if (valueNew > scoreBest)
                {
                    scoreBest = valueNew;
                    pathBest = int_to_string(nodeCurrent->nodeChild[i]->number);
                }
            }

            //append current node to the best path returned from children
            //convert int to string so it can be appended to another string

            cout << "depth = "<<depth << " pathBest = " <<pathBest<<" + "<<resultSucc.path<<" = "<< pathBest<<endl;
            pathBest = pathBest + resultSucc.path;

            resultCurrent.value = scoreBest;
            resultCurrent.path = pathBest;

            return resultCurrent;
        }
    }
    else if (depth >= depthMax) //leaves
    {
        resultCurrent.value = evaluation(nodeCurrent, player);
        cout << "eval for #"<<nodeCurrent->number<<" node is "<<resultCurrent.value<<endl<<endl;
        resultCurrent.path = "";

        return resultCurrent;
    }
}

bool CheckWin(nodeMove *position, bool player)
{
    int playmark;

    if (player == true)
        playmark = 3;
    else
        playmark = 5;

    bool win = false;

    int *grid;
    grid = position->infoBoard;

    if (grid[0] == playmark && grid[1] == playmark && grid[2] == playmark)
        win = true;
    else if (grid[3] == playmark && grid[4] == playmark && grid[5] == playmark)
        win = true;
    else if (grid[6] == playmark && grid[7] == playmark && grid[8] == playmark)
        win = true;
    else if (grid[0] == playmark && grid[3] == playmark && grid[6] == playmark)
        win = true;
    else if (grid[1] == playmark && grid[4] == playmark && grid[7] == playmark)
        win = true;
    else if (grid[2] == playmark && grid[5] == playmark && grid[8] == playmark)
        win = true;
    else if (grid[2] == playmark && grid[4] == playmark && grid[6] == playmark)
        win = true;
    else if (grid[0] == playmark && grid[4] == playmark && grid[8] == playmark)
        win = true;

    return win;
}




void play(nodeMove *&root)
{
    result resultFinal;
    bool player = true;

    //set board
    for (int i = 0; i < widthMax; i++)
    {
        root->infoBoard[i] = 2;
    }

    //start the game
    display_board(root->infoBoard);
    int countMove = 0;
    while (!CheckWin(root, player) && !CheckWin(root, !player) && countMove <= 8)
    {

        alpha = -99;
        beta = 99;
        //decide which move to make
        resultFinal = alpha_beta_search(root, 0, player);
        cout << "\nThe best move is " << resultFinal.path << ", value = "<< resultFinal.value <<" . Make the move to " << resultFinal.path[0] << endl<<endl;

        //make the move and update the board
        for (int i = 0; i < widthMax; i++)
        {
            root->infoBoard[i] = root->nodeChild[ char_to_int( resultFinal.path[0] ) ]->infoBoard[i];
        }

        display_board(root->infoBoard);
        player = !player;
        countMove++;

        cout << totalCheckEveryTurn << " possibilities were checked.\n";
        totalCheckEveryTurn = 0;
    }

    if (CheckWin(root, true) )
    {
        cout << "\n\nGame Ends. Player1 won.\n\n";
    }
    else if (CheckWin(root, false))
    {
        cout << "\n\nGame Ends. Player2 won.\n\n";
    }
    else
    {
        cout << "\n\nGame Ends. Draw\n\n";
    }
	
    //decide which move to make
    //make the move and update the board

    return;

}



bool Opposite(bool player)
{
    if (player == true)
        return false;
    else
        return true;
}



int main()
{

    int board[9] = {5, 5, 2, 5, 3, 5, 5, 5, 5}; //for testing
    nodeMove* root = NULL;
    int sumNode = 0;

    //display_board(board);

    sumNode = create_tree(root, board, depthMax);
    cout << sumNode << " nodes created." << endl;

    cout << "Enter maximum depth:\n";
    cin >> depthMax;

    cout << "Choose evaluation function for Player1:\n1. Text Book  2.Po-Teng\'s  3.Thomas\'s\n";
    cin >> chooseEvaluationP1;
    cout << "Choose evaluation function for Player2:\n1. Text Book  2.Po-Teng\'s  3.Thomas\'s\n";
    cin >> chooseEvaluationP2;


    play(root);


    delete_tree();
    return 0;
}
