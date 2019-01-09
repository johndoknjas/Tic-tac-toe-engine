// TO DO:

    // Check that all static variables and methods are initialized/implemented correctly.   DONE

    // Instead of using the embedded for loop in the minimax() function, run through the static coordinates vector instead. DONE

    // Re-shuffle the static coordinates vector for each game (i.e., in constructor when depth = 0). DONE

/* A "position" encompasses:

    - The board
    - The evaluation of position
    - Whose turn it is
    - The depth of the position in the computer's calculations.
 */

#pragma once

#include <vector>
#include <stdexcept>
#include <memory>
#include <cstdlib>
#include <time.h>

using namespace std;

struct coordinate
{
    int row;
    int col;
};

class position
{
public:
    // Constructors:
    position();
    position(const vector <vector<char>>& boardP, bool turnP, int depthP, int alphaP, int betaP);
    // No param for evaluation is sent to constructor, as this is figured out by the computer via minimax.
    // No param for future_positions is sent to constructor, as this is figured out by the computer via minimax.

    // Getters:
    vector <vector<char>> get_board() const;
//    vector <unique_ptr<position>> get_future_positions() const;
    int get_evaluation() const;
    bool get_is_comp_turn() const;
    int get_depth() const;
    unique_ptr<position> get_a_future_position(int i); // MOVES the position object at index i of future_positions and returns!
    vector <unique_ptr<position>> get_future_positions(); // MOVES the future_positions vector and returns it!
    int get_future_positions_size() const;

    // Setters:
    void set_board(const vector <vector<char>>& boardP);
//    void set_future_positions(const vector<unique_ptr<position>>& future_positionsP);
    void set_evaluation (int evalP);
    void set_is_comp_turn (bool turnP);
    void set_depth(int depthP);
    void set_future_positions_size(int i);

    // Helpers:
    bool did_computer_win() const; // returns true if the computer has won the game with 3-in-a-row in the current position.
    bool did_opponent_win() const; // returns true if the user has won the game with 3-in-a-row in the current position.
    bool is_game_drawn() const; // returns true if the game is drawn in the current position.
    bool evaluation_in_future_positions(int eval) const; // returns true if at least 1 future position has the evaluation value
                                                         // of the eval param.
    bool is_valid_move(string coordinates) const; // checks if the coordinates are empty on the board. For example,
                                                  // coordinates could be "a1" and this function would check if the spot
                                                  // [0][0] is empty on the board.

    // Public static methods:

    static vector<coordinate> create_vector_of_coordinate_objects(); // creates a vector of coordinate objects,
                                                                     // and then calls the shuffle function below to randomize
                                                                     // the objects' order. Finally, the vector is returned.

    static void shuffle_objects_in_vector(vector<coordinate>& vec);  // randomizes the order in a vector storing
                                                                     // coordinate objects.

    // Public static variable(s):

    static vector<coordinate> coordinates; // stores coordinate objects, which each have a row and col value. These
                                           // represent coordinates on vector <vector<char>> board.

    static int number_of_instances;

private:
    vector <vector<char>> board; // stores C's and U's and ' ', representing the computer and user's pieces and empty squares.
    vector <unique_ptr<position>> future_positions; // stores pointers to all future positions one move ahead.
    // stored as pointers in order to be efficient with memory, as position objects are huge.
    int evaluation; // stores -1 if the computer is losing, 0 if the game is drawn, and +1 if the computer is winning.
    bool is_comp_turn; // stores true if it's the computer's turn, and false if it's the user's turn.
    int depth; // stores how deep this position is in the computer's calculations.
    int future_positions_size; // stores how many positions are in the future_positions vector.

    int alpha; // stores the best alternative found so far FOR THE COMPUTER at this time in the entire search. (i.e., highest val).
    int beta; // stores the best alternative found so far FOR THE USER at this time in the entire search (i.e., lowest val).

    // Private methods:
    void minimax(); // Employs the minimax algorithm...
                    // fills the future_positions vector with all positions one move ahead.
                    // eventually gives the evaluation attribute a value of -1, 0, or +1.
    bool three_in_a_row(char c) const; // returns true if there is a 3-in-a-row of the char param in board.
    bool is_acceptable_letter(char c) const; // returns true if char c is a letter from a-c (uppercase OR lowercase).
    bool is_acceptable_digit(char c) const; // returns true if char c is between '0' and '9'.
};

// Initializing the static variable: coordinates

vector<coordinate> position::coordinates = create_vector_of_coordinate_objects();
// It will be equal to a vector of coordinate objects, with a random order.

int position::number_of_instances = 0;

// CONSTRUCTORS:

position::position()
{
    // Make an empty board:

    vector <char> column;

    for (int i = 0; i < 3; i++)
    {
        column.push_back(' ');
    }

    for (int i = 0; i < 3; i++)
    {
        board.push_back(column);
    }

    is_comp_turn = true;

    depth = 0;

    future_positions_size = 0;

    evaluation = 100000; // just some random value to signify that there is no evaluation value yet.

    alpha = 100000; // just some random value to signify that there is no alpha value yet.

    beta = 100000; // just some random value to signify that there is no beta value yet.

    // The above two assignments assume this position is the current, starting position.

    shuffle_objects_in_vector(coordinates); // if this constructor is called, depth = 0. Therefore, a new game is being
                                            // played, since minimax never creates multiple depth 0 positions (only one exists!).
                                            // So, I want to shuffle the coordinates vector in order to get the computer
                                            // to play something different from last game.

    number_of_instances ++;

    minimax();
}

position::position(const vector <vector<char>>& boardP, bool turnP, int depthP, int alphaP, int betaP)
{
    board = boardP;
    is_comp_turn = turnP;
    depth = depthP;
    future_positions_size = 0;
    evaluation = 100000; // just some random value to signify there is no evaluation value yet.
    alpha = alphaP;
    beta = betaP;

    if (depth == 0)
    {
        shuffle_objects_in_vector(coordinates); // If depth = 0, a new game is being played, since minimax never creates
                                                // multiple depth 0 positions (only one exists!).
                                                // So, I want to shuffle the coordinates vector in order to get the computer
                                                // to play something different from last game.
    }

    number_of_instances++;

    minimax();
}

// GETTERS:

vector <vector<char>> position::get_board() const
{
    return board;
}

int position::get_evaluation() const
{
    return evaluation;
}

bool position::get_is_comp_turn() const
{
    return is_comp_turn;
}

int position::get_depth() const
{
    return depth;
}

unique_ptr<position> position::get_a_future_position(int i)
{
    return move(future_positions[i]);
}

vector <unique_ptr<position>> position::get_future_positions()
{
    return move(future_positions);
}

int position::get_future_positions_size() const
{
    return future_positions_size;
}

// SETTERS:

void position::set_board(const vector <vector<char>>& boardP)
{
    board = boardP;
}

void position::set_evaluation (int evalP)
{
    evaluation = evalP;
}

void position::set_is_comp_turn (bool turnP)
{
    is_comp_turn = turnP;
}

void position::set_depth(int depthP)
{
    depth = depthP;
}

void position::set_future_positions_size(int i)
{
    future_positions_size = i;
}

// HELPERS:

bool position::did_computer_win() const
{
    return (!is_comp_turn && depth >= 5 && three_in_a_row('C'));
}

bool position::did_opponent_win() const
{
    return (is_comp_turn && depth >= 5 && three_in_a_row('U'));
}

// Pre-condition: It has already been checked that no one has won the game.
// Post-condition: The function will return true if the board is full... it is not guaranteed no one has three-in-a-row.
bool position::is_game_drawn() const
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board[row][col] == ' ')
            {
                return false;
            }
        }
    }

    return true;
}

bool position::evaluation_in_future_positions(int eval) const
{
    for (int i = 0; i < future_positions.size(); i++)
    {
        if (future_positions[i]->evaluation == eval)
        {
            return true;
        }
    }

    return false;
}

bool position::is_valid_move(string coordinates) const
{
    // First, check if coordinates is only 2 in size:

    if (coordinates.size() != 2)
    {
        return false;
    }

    char first = coordinates[0];
    char second = coordinates[1];

    // Now check if the first char is a letter between 'A' and 'C', and the second char is a digit between '1' and '3':

    if (!is_acceptable_letter(first) || !is_acceptable_digit(second))
    {
        return false;
    }

    // Now convert char first and char second into board coordinates. The goal is to see if the coordinates are
    // empty on the board:

    int row = (second - '0') - 1;
    int col = 0;

    if (first == 'A' || first == 'a')
    {
        col = 0;
    }

    else if (first == 'B' || first == 'b')
    {
        col = 1;
    }

    else
    {
        col = 2;
    }

    if (board[row][col] != ' ') // coordinate is NOT empty... bad!
    {
        return false;
    }

    return true;
}

// PUBLIC STATIC METHODS:

vector<coordinate> position::create_vector_of_coordinate_objects()
{
    vector<coordinate> vec;

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            coordinate temp;
            temp.row = row;
            temp.col = col;
            vec.push_back(temp);
        }
    }

    shuffle_objects_in_vector(vec);

    return vec;
}

void position::shuffle_objects_in_vector(vector<coordinate>& vec)
{
    // I'll create another vector, and move each element of vec into it (in random order):

    vector<coordinate> replacement;

    while (vec.size() > 0) // while vec still has elements
    {
        int index = rand() % vec.size();

        replacement.push_back(vec[index]);

        vec.erase(vec.begin() + index);
    }

    vec = replacement;
}

// PRIVATE METHODS:

void position::minimax()
{
    // Here's where all the magic happens.

    // First, see if this position is won for one side or drawn...

    if (did_computer_win())
    {
        evaluation = 1;
        return;
    }

    if (did_opponent_win())
    {
        evaluation = -1;
        return;
    }

    if (depth == 9) // if depth = 9, and no one already won from the above if statements, then the game must be drawn.
    {
        evaluation = 0;
        return;
    }

    // The game is not over, so look at all positions one move ahead.
    // Then, set evaluation accordingly, using the minimax algorithm...

    for (const coordinate& temp: coordinates) // running through the coordinates vector.
    {
        if (board[temp.row][temp.col] == ' ') // empty spot... put a piece here:
        {
            // Now to make a copy of the current board:

            vector <vector<char>> copy_board = board;

            if (is_comp_turn)
            {
                copy_board[temp.row][temp.col] = 'C';
            }

            else // opponent's turn:
            {
                copy_board[temp.row][temp.col] = 'U';
            }

            // Now to make a new position object, with this updated board that's one move ahead.

            unique_ptr<position> pt = make_unique<position>(copy_board, !is_comp_turn, depth + 1, alpha, beta);

            int future_evaluation = pt->evaluation;

            future_positions.push_back(move(pt));

            future_positions_size ++;

            // Test if a winning move was found for the comp or user:

            if (future_evaluation == 1 && is_comp_turn) // so the comp can make a move that wins...
            {
                evaluation = 1;
                return;
            }

            if (future_evaluation == -1 && !is_comp_turn) // so the user can make a move that wins for them...
            {
                evaluation = -1;
                return;
            }

            if (evaluation == 100000) // no evaluation for this position yet, so for now:
            {
                evaluation = future_evaluation;
            }

            else // this position already has an evaluation from a future position previously examined, so I need to see if
            {    // I should replace it with an updated evaluation value from the current future position being examined now.
                if (future_evaluation > evaluation && is_comp_turn)
                {
                    evaluation = future_evaluation;
                }

                else if (future_evaluation < evaluation && !is_comp_turn)
                {
                    evaluation = future_evaluation;
                }
            }

            // ALPHA-BETA PRUNING:

            // Let's check if this position is a MAX block (comp's turn) or MIN block (user's turn):

            if (is_comp_turn) // This is a MAX block... check beta to try to prune, and possibly reset alpha.
            {
                // SEE IF I CAN PRUNE:
                if (beta != 100000 && beta <= evaluation) // there is a real beta value, and it is <= evaluation.
                {
                    // This position's evaluation can only stay the same or get higher, since the comp will find the position
                    // with the highest evaluation (this is a MAX node).

                    // Already, beta is <= evaluation.

                    // Therefore, the user (in the previous MIN node) would not have picked this branch. They
                    // would have picked the branch with the value of beta (i.e., lowest value).

                    // So, this branch will be TRIMMED.

                    evaluation = 1; // To ensure this branch is not favoured over the previous good branch
                                    // with the value of beta. The parent MIN node of this current MAX node will
                                    // definitely NOT like an evaluation of 1 (it's the highest possible evaluation).

                    return;
                }

                // SEE IF ALPHA SHOULD BE RESET (or given a value, if it doesn't have one yet):
                if (alpha == 100000 || evaluation > alpha)
                {
                    alpha = evaluation;
                }
            }

            else // user's turn, so MIN block... check alpha to see if branch should be pruned, and possibly reset beta.
            {
                // SEE IF I CAN PRUNE:
                if (alpha != 100000 && alpha >= evaluation) // there is a real alpha value, and it is >= evaluation.
                {
                    // This position's evaluation can only stay the same or get lower, since the user will find the position
                    // with the lowest evaluation (this is a MIN block).

                    // Already, alpha is >= evaluation.

                    // Therefore, the comp (in the previous MAX node) would not have picked this branch. It would have picked
                    // the branch with the value of alpha (i.e., highest value).

                    // So, this branch will be TRIMMED.

                    evaluation = -1; // To ensure this branch is not favoured over the previous good branch
                                     // with the value of alpha. The parent MAX node of this current MIN node will
                                     // definitely NOT like an evaluation of -1 (it's the lowest possible evaluation).

                    return;
                }

                // SEE IF BETA SHOULD BE RESET (or given a value, if it doesn't have one yet):
                if (beta == 100000 || evaluation < beta)
                {
                    beta = evaluation;
                }
            }
        }
    }
}

bool position::three_in_a_row(char c) const
{
    // Diagonals:
    if (board[0][0] == c && board[1][1] == c && board[2][2] == c)
    {
        return true;
    }
    if (board [2][0] == c && board[1][1] == c && board[0][2] == c)
    {
        return true;
    }

    // Verticals & Horizontals:
    for (int i = 0; i < 3; i++)
    {
        // Vertical:
        if (board[0][i] == c && board[1][i] == c && board[2][i] == c)
        {
            return true;
        }

        // Horizontal:
        if (board[i][0] == c && board[i][1] == c && board[i][2] == c)
        {
            return true;
        }
    }

    return false;
}

bool position::is_acceptable_letter(char c) const
{
    return ((c >= 'A' && c <= 'C') || (c >= 'a' && c <= 'c'));
}

bool position::is_acceptable_digit(char c) const
{
    return (c >= '1' && c <= '3');
}

