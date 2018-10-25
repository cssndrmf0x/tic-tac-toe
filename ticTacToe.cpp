#include <iostream>

using namespace std;

// global constants 
const int NUM_ROWS = 3,
          NUM_COLS = 3;

void instructions();
void dispBoard(char [][NUM_COLS]);

bool isVal(int &, int, int);
void userMove(char [][NUM_COLS], int);

bool rowCheck(char [][NUM_COLS]);
bool colCheck(char [][NUM_COLS]);
bool diagCheck(char [][NUM_COLS]);
bool isWinner(char [][NUM_COLS]);

int main()
{
    int winnerNumber = 0;
    // asterisks indicate empty spaces
    char gameBoard[NUM_ROWS][NUM_COLS] = {{'*','*','*'},
                                          {'*','*','*'},
                                          {'*','*','*'}};
    bool gameOver = false,
    // win1 indicates p1 won, win2 indicates p2 won
         win1 = false,
         win2 = false;

    instructions();
    dispBoard(gameBoard);

    /* continues playing until gameOver is true, as someone will have won game
       however this while loop actually just takes break statements to break out of it because
       the condition can't be tested in the middle of the loop */
    while(gameOver == false)
    {
        // player 1's move, then the game board is displayed, then we check if p1 is a winner
        userMove(gameBoard,1);
        dispBoard(gameBoard);
        win1 = isWinner(gameBoard);

        if (win1)
        {
            cout << "Congrats, Player 1. You win!\n\n";
            break;
        }

        // player 2's move, then the game board is displayed, then we check if p1 is a winner
        userMove(gameBoard,2);
        dispBoard(gameBoard);
        win2 = isWinner(gameBoard);

        if (win2)
        {
            cout << "Congrats, Player 2. You win!\n\n";
            break;
        }
    }

    cout << "Thanks for playing!\n";

    return 0;
}

// explains tic tac toe 
void instructions()
{
    cout << "Welcome to Tic-Tac-Toe! Player 1 will be playing with 'X's and \n"
         << "Player 2 will be playing with 'O's. Please follow your answers to all\n"
         << "prompts with the enter key.\n\n";
}

// displays game board
void dispBoard(char board[][NUM_COLS])
{
    for (int row = 0; row < NUM_ROWS; row++)
    {
        for (int col = 0; col < NUM_COLS; col++)
            cout << board[row][col] << '\t';
        cout << "\n\n";
    }
}

/* checks if an integer input value is between min and max value, prompts for new
   one if if it's not */
bool isVal(int &userEntry, int minVal, int maxVal)
{
    while (userEntry < minVal || userEntry > maxVal)
    {
        cout << "I'm sorry, that's an invalid answer. Try again.\n"
             << "Enter a number between 1 and 3: ";

        cin >> userEntry;
    }
}

/* input validation, checks if row and col are valid nums, then checks if
   there is already a marker there. if entry is valid, the player's marker
   is placed there */
void userMove(char board[][NUM_COLS], int playerNum)
{
    int userRow, userCol;
    bool rowValid, colValid;

    cout << "Player " << playerNum << ", where would you like to place your marker?\n"
         << "Enter the row number: ";
    cin >> userRow;
    rowValid = isVal(userRow, 1, 3);

    cout << "Enter the column number: ";
    cin >> userCol;
    colValid = isVal(userCol, 1, 3);

    /* userRow & Col - 1 because user will not start at 0 when numbering rows and columns
       but the array does */
    while (board[userRow - 1][userCol - 1] != '*')
    {
        cout << "Sorry, there's already a marker there. Try again.\n"
             << "Enter the row number: ";
        cin >> userRow;
        rowValid = isVal(userRow, 1, 3);

        cout << "Enter the column number: ";
        cin >> userCol;
        colValid = isVal(userCol, 1, 3);
    }

    cout << endl;

    // if playerNum is 1, it's player 1's turn and marker is an X, otherwise it's p2 and an O
    if (playerNum == 1)
        board[userRow - 1][userCol - 1] = 'X';
    else
        board[userRow - 1][userCol - 1] = 'O';
}

// checks each row of board for a winner
bool rowCheck(char board[NUM_ROWS][NUM_COLS])
{
    bool win = false;
    char tempVal;

    // outer loop marches thru each row, inner loop goes through elements of row by col
    for (int row = 0; row < NUM_ROWS; row++)
    {
        // tempVal stores first element of row for comparison purposes
        tempVal = board[row][0];
        for (int col = 0; col < NUM_COLS; col++)
        {
            /* if element is asterisk, break out of loop and go to next row b/c
               not all elements of this row are filled in */
            if (board[row][col] == '*')
                break;
            /* if element is not the same as the first element of row (tempVal), this is
               also not a winning row */
            else if (board[row][col] != tempVal)
                break;
            /* win is only true if we have reached last column of row, and the value is
               the same as the first element of row, tempVal */
            else if (board[row][col] == tempVal && col == 2)
                win = true;
        }
    }

    return win;
}

// checks each column of board for a winner
bool colCheck(char board[NUM_ROWS][NUM_COLS])
{
    bool win = false;
    char tempVal;

    for (int col = 0; col < NUM_COLS; col++)
    {
        tempVal = board[0][col];
        for (int row = 0; row < NUM_ROWS; row++)
        {
            if (board[row][col] == '*')
                break;
            else if (board[row][col] != tempVal)
                break;
            else if (board[row][col] == tempVal && row == 2)
                win = true;
        }
    }

    return win;
}

// checks each diagonal for a win
bool diagCheck(char board[NUM_ROWS][NUM_COLS])
{
    bool win = false;
    char tempVal;

    // checks downward diag, top left to bot right
    for (int row = 0, col = 0; row < NUM_ROWS, col < NUM_COLS; row++, col++)
    {
        tempVal = board[0][0];
        if (board[row][col] == '*')
            break;
        else if (board[row][col] != tempVal)
            break;
        else if (board[row][col] == tempVal && col == 2)
            win = true;
    }

    // checks upward diag, bot left to top right
    for (int row = 2, col = 0; row >= 0, col < NUM_COLS; row--, col++)
    {
        tempVal = board[2][0];
        if (board[row][col] == '*')
            break;
        else if (board[row][col] != tempVal)
            break;
        else if (board[row][col] == tempVal && col == 2)
            win = true;
    }

    return win;
}

// this function uses previous three functions, just runs them all to check for winner
bool isWinner(char board[][NUM_COLS])
{
    // row winner, column winner, and diagonal winner all start out false
    bool winnerR = false,
         winnerC = false,
         winnerD = false;

    winnerR = rowCheck(board);
    winnerC = colCheck(board);
    winnerD = diagCheck(board);

    // if there are any winning values, true will be returned
    if(winnerR || winnerC || winnerD)
        return true;

    // otherwise, function returns false
    return false;
}
