#include <iostream>
#include <algorithm>
using namespace std;

class Board
{
public:
	Board() // Creates an empty board.
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board[i][j] = ' ';
			}
		}
	}
	void reset() // clears the board. 
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board[i][j] = ' ';
			}
		}
	}
	void addChecker(char who, int row, int col); // puts who at position (r, c)
	int numJumps(int row, int col); // Returns the maximum number of jumps a checker can make starting at (row, col)
	void print(); // Print the board for debugging only.
private:
	char board[8][8];
};


int main()
{
	Board board;

	char myCheckers = 'X', yourCheckers = 'O';
	int myCheckerPiece, yourCheckerPiece;
	int row, col, row1, col1;
	int row2 = 0, col2 = 0;
	int testCases;
	int nJumps[1000];


	cin >> testCases;

	for (int i = 0; i < testCases; i++)
	{
		cin >> myCheckerPiece >> yourCheckerPiece;


		for (int j = 0; j < myCheckerPiece; j++) {

			if (j == 0)
			{
				cin >> row >> col;
				board.addChecker(myCheckers, row, col);
			}
			else
			{
				cin >> row1 >> col1;
				board.addChecker(myCheckers, row1, col1);

			}
			//board.print();
		}

		for (int k = 0; k < yourCheckerPiece; k++) {
			cin >> row2 >> col2;
			board.addChecker(yourCheckers, row2, col2);
			//board.print();
		}
		nJumps[i] = board.numJumps(row, col);
		board.reset();
	}

	for (int i = 0; i < testCases; i++)
	{
		cout << "the number of jumps is " << nJumps[i] << endl;
	}

	return 0;
}

void Board::addChecker(char who, int row, int col) // Puts who at position (row, col) 
												   //Pre-Condition: None
												   //Post-Condition: the int row and int column are assigned to char who 
{
	board[row][col] = who;
}


void Board::print() // Print the board for debugging only.
{
	//Pre-Conditon: 2 lines will be printed out on a 8 by 8 grid 
	//Post-Condition: board[i][j] will be printed out

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << "|_";
			cout << board[i][j];
		}
		cout << endl;
	}
}

int Board::numJumps(int row, int col)  // Returns the maximum number of jumps a checker can make starting at (row, col)
{
	//Pre-Conditon: row < 8 and col < 8 and row =- n, col +- != 'X' or ' ' to jump
	//Post-Condition: board[][] is either ' ', 'X' or 'O'

	int totalJumps = 0;


	if (row < 8 && col < 8)
	{
		if ((board[row - 1][col + 1] != ' ') && (board[row - 1][col + 1] != 'X'))
		{
			if ((board[row - 2][col + 2] == ' ') && (board[row - 2][col + 2] != 'X')) // Up Right
			{
				addChecker('X', row - 2, col + 2); //jump piece  
												   //print();
				addChecker(' ', row - 1, col + 1); //remove opponents piece.
												   //print();
				totalJumps = max(totalJumps, 1 + numJumps(row - 2, col + 2));
				addChecker(' ', row - 2, col + 2); //undo jump for king
												   //print();
				addChecker('O', row - 1, col + 1); //undo jump for opponent
												   //print();
			}
		}
	}


	if (row < 8 && col < 8)
	{
		if ((board[row - 1][col - 1] != ' ') && (board[row - 1][col - 1] != 'X'))
		{
			if ((board[row - 2][col - 2] == ' ') && (board[row - 2][col - 2] != 'X')) // Up Left
			{
				addChecker('X', row - 2, col - 2); //jump piece
												   //print();
				addChecker(' ', row - 1, col - 1); //remove opponents piece.
												   //print();
				totalJumps = max(totalJumps, 1 + numJumps(row - 2, col - 2));
				addChecker(' ', row - 2, col - 2); //undo jump for king
												   //print();
				addChecker('O', row - 1, col - 1); //undo jump for opponent
												   //print();
			}
		}
	}

	if (row < 8 && col < 8)
	{
		if ((board[row + 1][col + 1] != ' ') && (board[row + 1][col + 1] != 'X'))
		{
			if ((board[row + 2][col + 2] == ' ') && (board[row + 2][col + 2] != 'X'))// Down Right
			{
				addChecker('X', row + 2, col + 2);  //jump piece 
													//print();
				addChecker(' ', row + 1, col + 1); //remove opponents piece.
												   //print();
				totalJumps = max(totalJumps, 1 + numJumps(row + 2, col + 2));
				addChecker(' ', row + 2, col + 2); //undo jump for king
												   //print();
				addChecker('O', row + 1, col + 1); //undo jump for opponent
												   //print();
			}
		}
	}


	if (row < 8 && col < 8)
	{
		if ((board[row + 1][col - 1] != ' ') && (board[row + 1][col - 1] != 'X'))
		{
			if ((board[row + 2][col - 2] = ' ') && (board[row + 2][col - 2] = ' ')) // Down Left
			{
				addChecker('X', row + 2, col - 2); //jump piece
												   //print();
				addChecker(' ', row + 1, col - 1); //remove opponents piece.
												   //print();
				totalJumps = max(totalJumps, 1 + numJumps(row + 2, col - 2));
				addChecker(' ', row + 2, col - 2); //undo jump for king
												   //print();
				addChecker('O', row + 1, col - 1); //undo jump for opponent
												   //print();
			}
		}
	}


	return totalJumps;
}
