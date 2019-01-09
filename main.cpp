#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include <time.h>
#include <cstdlib>

#include "position.h"

using namespace std;

vector <vector<char>> create_2d_vector()
{
    vector <vector<char>> board;

    vector <char> column;

    for (int i = 0; i < 3; i++)
    {
        column.push_back(' ');
    }

    for (int i = 0; i < 3; i++)
    {
        board.push_back(column);
    }

    return board;
}

void fill_board(vector <vector<char>>& board, string pieces)
{
    int index = 0;

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            board[row][col] = pieces[index];
            index ++;
        }
    }
}

void test_embedded_ranged_for_loop()
{
    position p1; // to get the static coordinates vector initialized.

    for (const coordinate& i: position::coordinates) // only purpose is to run 9 times.
    {
        for (const coordinate& temp: position::coordinates)
        {
            cout << "(" << temp.row << "," << temp.col << "), ";
        }

        cout << "\n";
    }

    // Expectation: 9 lines are printed out, all looking the same. The outside for loop should have NO EFFECT on the inside loop.

    // TEST PASSED.


    // Now let's make CHANGES to the outside for loop, and it SHOULD affect the inner loop (since it is all by reference):

    cout << "\n\n\n\n";

    for (coordinate& i: position::coordinates)
    {
        i.row = -1;
        i.col = -1;

        for (coordinate& temp: position::coordinates)
        {
            cout << "(" << temp.row << "," << temp.col << "), ";
        }

        cout << "\n";
    }

    // Expectation: There should be 9 lines, where each (row, col) block is slowly petering out from left to right.

    // TEST PASSED
}

void test_static_methods()
{
    // create_vector and shuffle methods:

    for (int i = 0; i < 5; i++)
    {
        position p1;

        // On iteration 1, the create_vector function intialized the coordinates vector and shuffled it.

        // And on each GENERAL iteration, the coordinates vector is shuffled.

        // This can be seen from observing the printout for each iteration.

        for (const coordinate& temp: position::coordinates)
        {
            cout << "(" << temp.row << "," << temp.col << "), ";
        }

        cout << "\n";
    }
}

void test_positions()
{
    // Function tests how my program handles various positions, mainly at depths 8-9 and 0-1:

    vector <vector<char>> board = create_2d_vector();

    // depth 8, test 1:

    string pieces = "CUCCUU CU";

    fill_board(board, pieces);

    for (int alpha = -1; alpha <= 100000; alpha++)
    {
        if (alpha > 1)
        {
            alpha = 100000;
        }

        for (int beta = -1; beta <= 100000; beta++)
        {
            if (beta > 1)
            {
                beta = 100000;
            }

            position p1(board, true, 8, alpha, beta);

            if (p1.get_evaluation() != 1)
            {
                cout << "BAD!!!!";
            }
        }
    }

    // depth 8, test 2:

    cout << "\n\n\n";

    pieces = "UCCUUCCU ";

    fill_board(board, pieces);

    for (int alpha = -1; alpha <= 100000; alpha++)
    {
        if (alpha > 1)
        {
            alpha = 100000;
        }

        for (int beta = -1; beta <= 100000; beta++)
        {
            if (beta > 1)
            {
                beta = 100000;
            }

            position p1(board, false, 8, alpha, beta);

            if (p1.get_evaluation() != -1)
            {
                cout << "BAD!!!!";
            }
        }
    }

    // depth 9, test 1:

    cout << "\n\n\n";

    pieces = "UCCUUCCUU";

    fill_board(board, pieces);

    for (int alpha = -1; alpha <= 100000; alpha++)
    {
        if (alpha > 1)
        {
            alpha = 100000;
        }

        for (int beta = -1; beta <= 100000; beta++)
        {
            if (beta > 1)
            {
                beta = 100000;
            }

            position p1(board, true, 9, alpha, beta);

            if (p1.get_evaluation() != -1)
            {
                cout << "BAD!!!!";
            }
        }
    }

    // depth 9, test 2:

    cout << "\n\n\n";

    pieces = "UCCUUCCUC";

    fill_board(board, pieces);

    for (int alpha = -1; alpha <= 100000; alpha++)
    {
        if (alpha > 1)
        {
            alpha = 100000;
        }

        for (int beta = -1; beta <= 100000; beta++)
        {
            if (beta > 1)
            {
                beta = 100000;
            }

            position p1(board, false, 9, alpha, beta);

            if (p1.get_evaluation() != 1)
            {
                cout << "BAD!!!!";
            }
        }
    }
}

void test_loadtime()
{
    double start_time = time(NULL);

    for (int i = 0; i < 50; i++)
    {
        position p1;
    }

    double end_time = time(NULL);

    double difference = end_time - start_time;

    cout << "Time was " << (difference / 50.0) << " seconds.\n";
}

void examine_data_type_sizes()
{

    vector <int> temp;

    for (int i = 1; i <= 100000; i++)
    {
        temp.push_back(i);
    }

    cout << "temp: " << sizeof(temp) << "\n";


    cout << "bool: " << sizeof(bool) << "\n";
    cout << "char: " << sizeof(char) << "\n";
    cout << "int: " << sizeof(int) << "\n";
    cout << "double: " << sizeof(double) << "\n";
    cout << "vector<vector<char>>: " << sizeof(vector<vector<char>>) << "\n";
    cout << "vector<unique_ptr<position>>: " << sizeof(vector<unique_ptr<position>>) << "\n";
    cout << "vector<coordinate>: " << sizeof(vector<coordinate>) << "\n";
    cout << "raw int pointer: " << sizeof(int*) << "\n";
    cout << "raw double pointer: " << sizeof(double*) << "\n";
    cout << "raw position pointer: " << sizeof(position*) << "\n";
    cout << "unique_ptr: " << sizeof(unique_ptr<int>) << "\n";
    cout << "shared_ptr: " << sizeof(shared_ptr<int>) << "\n";
    cout << "weak_ptr: " << sizeof(weak_ptr<int>) << "\n";
    cout << "int&: " << sizeof(int&) << "\n";
    cout << "double&: " << sizeof(double&) << "\n";
    cout << "coordinate: " << sizeof(coordinate) << "\n";
    cout << "position: " << sizeof(position) << "\n";

    position p1;

    cout << "p1: " << sizeof(p1) << "\n";
}

void set_pregame_data(bool& user_goes_first, bool& x_represents_user)
{
    cout << "Type y to go first, and n for the computer to go first: ";

    char user_input = ' ';

    cin >> user_input;

    if (user_input == 'y')
    {
        user_goes_first = true;
    }

    cout << "Type x or o for what piece you want: ";

    cin >> user_input;

    if (user_input == 'x')
    {
        x_represents_user = true;
    }
}

void display_board(vector <vector<char>> board, bool x_represents_user, int evaluation)
{
    // First, change the 'C' and 'U' in board to 'X' and 'O', depending on if 'X' or 'O' represents the user...

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board[row][col] == 'U')
            {
                if (x_represents_user)
                {
                    board[row][col] = 'X';
                }

                else
                {
                    board[row][col] = 'O';
                }
            }

            else if (board[row][col] == 'C')
            {
                if (x_represents_user) // so 'O' represents the computer:
                {
                    board[row][col] = 'O';
                }

                else
                {
                    board[row][col] = 'X';
                }
            }
        }
    }

    // Before I start printing the board to the screen, I want to figure out what I'm going to say to the user about
    // the position's evaluation.

    string evaluation_message = "";

    if (evaluation == -1)
    {
        evaluation_message = "EVALUATION: You are winning!"; // since the computer is losing.
    }

    else if (evaluation == 1)
    {
        evaluation_message = "EVALUATION: The computer is winning!";
    }

    else // evaluation = 0
    {
        evaluation_message = "EVALUATION: The game is equal!";
    }

    cout << "\n    A   B   C\n\n";

    for (int row = 0; row < 3; row++)
    {
        cout << (row + 1) << "   ";

        for (int col = 0; col < 3; col++)
        {
            cout << board[row][col];

            if (col < 2)
            {
                cout << " | ";
            }
        }

        if (row == 1) // I want to print the evaluation message:
        {
            cout << "\t" << evaluation_message;
        }

        cout << "\n";

        if (row < 2)
        {
            cout << "   ---|---|---\n";
        }
    }
}

void play_game()
{
    bool user_goes_first = false;
    bool x_represents_user = false;

    set_pregame_data(user_goes_first, x_represents_user);

    unique_ptr<position> pos = make_unique<position>(create_2d_vector(), !user_goes_first, 0, 100000, 100000);
    // pos represents the current position of the game.
    // sending !user_goes_first as argument because class attribute stores true if COMP goes first.

    cout << "\nSTARTING POSITION:\n";

    display_board(pos->get_board(), x_represents_user, pos->get_evaluation());

    cout << "\n\n\n";

    while (!pos->did_computer_win() && !pos->did_opponent_win() && !pos->is_game_drawn()) // while the game is still going on...
    {
        if (pos->get_is_comp_turn() == true) // computer's turn:
        {
            int start_time = time(NULL); // Will be used to make sure the computer takes 2 seconds to stall:

            // First, I want to directly access the future_positions vector. I'll be moving it out of the position
            // object, but that's okay (the position object doesn't need it anymore):

            vector <unique_ptr<position>> candidate_moves = pos->get_future_positions(); // function MOVES future_positions.

            pos->set_future_positions_size(0); // since the position object's future_positions vector is dead now.

            // Next step: look through the candidate moves vector to find the best move.

            // To do this, only keep positions with the same evaluation as the current position, since in minimax
            // the current position has the same evaluation as the best positions after it (since the computer picks the
            // best option).

            vector <unique_ptr<position>> best_moves;

            for (int i = 0; i < candidate_moves.size(); i++)
            {
                if (candidate_moves[i]->get_evaluation() == pos->get_evaluation())
                {
                    best_moves.push_back(move(candidate_moves[i]));
                }
            }

            // Now to randomly pick one of the moves in best_moves, since they are all equally the best:

            if (best_moves.size() == 0)
            {
                throw runtime_error("No best moves...\n");
            }

            int index = rand() % best_moves.size();

            // Now to set pos to this new position's board, which the computer will play:

            vector <vector<char>> new_board = best_moves[index]->get_board();

            pos = make_unique<position>(new_board, !pos->get_is_comp_turn(), pos->get_depth() + 1, 100000, 100000);
            // creates FROM SCRATCH.

            // Now before displaying the computer's move, I want to make sure it has stalled for 2 seconds, in order to
            // not make things too confusing & fast for the user:

            while (time(NULL) - start_time < 1)
            {
                // deliberately left empty, just using this loop to stall if 2 seconds haven't passed yet.
            }

            cout << "COMPUTER'S MOVE:\n";

            display_board(pos->get_board(), x_represents_user, pos->get_evaluation());
        }

        else // user's turn:
        {
            string coordinates = "";

            cout << "Enter coordinates to move: ";

            cin >> coordinates;

            while (!pos->is_valid_move(coordinates))
            {
                cout << "You entered an invalid move. Please try again: ";

                cin >> coordinates;
            }

            // Now that I know the user inputted valid coordinates, convert them to row and col:

            char letter = coordinates[0];
            char digit = coordinates[1];

            int row = (digit - '0') - 1;
            int col = 0;

            if (letter == 'A' || letter == 'a')
            {
                col = 0;
            }

            else if (letter == 'B' || letter == 'b')
            {
                col = 1;
            }

            else // letter = 'C' or 'c'
            {
                col = 2;
            }

            // Now to make the user's move on a temporary board:

            vector <vector<char>> temp_board = pos->get_board();

            temp_board[row][col] = 'U';

            // Now to set pos to a new position object with temp_board:

            pos = make_unique<position>(temp_board, !pos->get_is_comp_turn(), pos->get_depth() + 1, 100000, 100000);
            // created FROM SCRATCH.

            cout << "YOUR MOVE:\n";

            display_board(pos->get_board(), x_represents_user, pos->get_evaluation());
        }

        cout << "\n\n\n";
    }

    // At this point, the game has ended. I should display the winner:

    if (pos->did_computer_win())
    {
        cout << "The computer won!\n\n";
    }

    else if (pos->did_opponent_win())
    {
        cout << "You won!\n\n";
    }

    else
    {
        cout << "The game is a draw!\n\n";
    }
}

int main()
{
    srand(time(NULL));

   // position p1;

   // cout << "Number of instances: " << p1.number_of_instances << "\n";

    // test_loadtime();

    // test_positions();

    // test_static_methods();

   // test_embedded_ranged_for_loop();

   // examine_data_type_sizes();



    char user_input = ' ';

    cout << "To play, press 1 and enter: ";

    cin >> user_input;

    while (user_input == '1')
    {
        play_game();

        cout << "To play again, press 1 and enter: ";

        cin >> user_input;
    }


}

