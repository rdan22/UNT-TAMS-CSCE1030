/* 
============================================================================
Name        : homework5.cpp
Author      : Riya Danait
Date        : 11/19/17
Description : The program prints out a randomized Stratego game board
			  based on a set of rules.  
============================================================================
*/
#include <iostream>
#include <stdio.h>
#include <cstdlib>
using namespace std;
//head function calls with name/information and rules
void header();
void rules();
//declaring the global variables
const int BOARD_SIZE = 5;
//game pieces
enum Pieces {EMPTY 	= ' ',
			 FLAG 	= 'F', 
			 BOMB 	= 'B', 
			 MARSHAL = '1', 
			 GENERAL = '2', 
			 COLONEL = '3', 
			 MAJOR 	= '4', 
			 CAPTAIN = '5', 
			 LIEUTENANT = '6', 
			 SERGEANT = '7', 
			 MINER 	= '8', 
			 SPY 	= 'S'};
//game colors
enum Color {RED = 'R', 
			BLUE = 'B', 
			NONE = 'N'};
//function declarations
void initBoard(Pieces (&boardPieces)[BOARD_SIZE][BOARD_SIZE], Color (&boardColor)[BOARD_SIZE][BOARD_SIZE], int size);

void assignPieces(Pieces (&boardPieces)[BOARD_SIZE][BOARD_SIZE], Color (&boardColor)[BOARD_SIZE][BOARD_SIZE], int size);

void printBoard(Pieces (&boardPieces)[BOARD_SIZE][BOARD_SIZE], Color (&boardColor)[BOARD_SIZE][BOARD_SIZE], int size);
//main function
int main()
{
	Pieces boardPieces[BOARD_SIZE][BOARD_SIZE];
	Color boardColor[BOARD_SIZE][BOARD_SIZE];

    //calling all the functions
	header();
    rules();
    initBoard(boardPieces, boardColor, BOARD_SIZE);
    assignPieces(boardPieces, boardColor, BOARD_SIZE);
    printBoard(boardPieces, boardColor, BOARD_SIZE);

	return 0;
}
/* 
============================================================================
Function    : header
Parameters  : none
Return      : nothing as it is a void function.
Description : This function prints out my name and information.
============================================================================
*/
void header()
{
	cout << 
	"  +-------------------------------------------------------------------+\n"
    "  |		      Computer Science and Engineering                |\n"
    "  |		       CSCE 1030 - Computer Science I                 |\n"
    "  |	       Riya Danait    rd0305   rd0305@my.unt.edu              |\n"
    "  +-------------------------------------------------------------------+\n";
}
/* 
============================================================================
Function    : rules
Parameters  : none
Return      : nothing as it is a void function.
Description : This function prints out the rules of the game Stratego.
============================================================================
*/
void rules()
{
	cout <<
	"                   Welcome to CSCE 1030 Stratego                        \n"

	"------------------------------------------------------------------------\n"
	"This program consists of a 5x5 game board for a 1030 version of the game\n"
	"of Stratego. One player will compete against the computer, each assigned\n"
	"10 total pieces consisting of the following:\n"
	"  1 FLAG (F)\n"
	"  3 BOMB (B)\n"
	"  1 MARSHAL (1) or GENERAL (2)\n"
	"  3 COLONEL (3), MAJOR (4), CAPTAIN (5), LIEUTENANT (6), or SERGEANT (7)\n"
	"  1 MINER (8)\n"
	"  1 SPY (S)\n"
	"GENERAL RULES:\n"
	"--------------\n"
	"The game will follow the standard Stratego rules, with some exceptions. \n"
	"1. Both players (BLUE and RED) will have all of their 10 game pieces as-\n"
	"   signed randomly with the only requirement being that the FLAG must be\n"
	"   placed in the back row. RED will start the game first.\n"
	"2. Higher ranked pieces can capture lower ranked pieces in the following\n"
	"   order: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> S, meaning that 1 (the\n" 
	"   MARSHAL) can remove 2 (the GENERAL) and so forth. The MINER (8) piece\n"
	"   may strike a BOMB and remove it to occupy the now unoccupied space. A\n" 
	"   SPY (S), although the lowest ranked piece, may remove the MARSHAL (1)\n"
	"   or the GENERAL (2).\n"
	"3. The FLAG and BOMBs are not moveable while all of the other pieces may\n"
	"   move one square at a time forward, backward, or sideward, but not di-\n"
	"   agonally to an open square.\n"
	"4. A player must either move or strike on his/her turn.\n"
	"5. The game ends when a player strikes his/her opponent's flag.\n"
	"------------------------------------------------------------------------\n";
}
/* 
============================================================================
Function    : initBoard
Parameters  : the two enumerated type arrays and the size
Return      : nothing as it is a void function.
Description : This function simply initializes the board to NONE color and
EMPTY pieces.
============================================================================
*/
void initBoard(Pieces (&boardPieces)[BOARD_SIZE][BOARD_SIZE],
                Color (&boardColor)[BOARD_SIZE][BOARD_SIZE], int size)
{
	//variables for the rows and columns of the game board
    int row;
    int col;

    cout << "\nInitializing game board ... \n";

    // Initialize the board with all pieces set to EMPTY and their colors set to NONE 
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            boardPieces[row][col] = EMPTY;
            boardColor[row][col]  = NONE;
        }
    }
}
/* 
============================================================================
Function    : assignPieces
Parameters  : the two enumerated type arrays and the size
Return      : nothing as it is a void function.
Description : This function uses a random number generator to randomly 
assign some of the game pieces to the board (for both BLUE and RED). 
============================================================================
*/
void assignPieces(Pieces (&boardPieces)[BOARD_SIZE][BOARD_SIZE],
                  Color (&boardColor)[BOARD_SIZE][BOARD_SIZE], int size)
{
	//declaring the variables
    int i;
    //declaring and initializing the row and column variables 
    int col = 0;
    int row = 0;

    cout << "Assigning BLUE pieces to the board ... \n";
    cout << "Assigning RED pieces to the board ... \n";

    srand(time(NULL)); // Seed Random function
    
    // Randomly assign 1 FLAG to the back row (row 0) of BLUE player
    // in any one column (i.e., 0 through size - 1).
    do
    {
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[0][col] != EMPTY);
    
    boardPieces[0][col] = FLAG;
    boardColor[0][col]  = BLUE;
    
    // Randomly assign 1 FLAG to the back row (row 4) of RED player
    // in any one column (i.e., 0 through size - 1).
    do
    {
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[size - 1][col] != EMPTY);
    
    boardPieces[size - 1][col] = FLAG;
    boardColor[size - 1][col]  = RED;
    
    //  Randomly assign 3 BOMBs to one of the two back two rows (i.e. rows 0 and 1) of BLUE player
    //  in any column (i.e., 0 through size-1).
    
    for (i = 0; i < 3; i++)
    {
        do
        {
            row = rand() % 2;    // pick a random row between 0 and 1
            col = rand() % size; // pick a random column between 0 and size-1
        } 
        while(boardPieces[row][col] != EMPTY);
        
        boardPieces[row][col] = BOMB;
        boardColor[row][col]  = BLUE;
    }
    
    //  Randomly assign 3 BOMBs to one of the two back two rows (i.e. rows 3 and 4) of RED player
    //  in any column (i.e., 0 through size-1).
    for (i = 0; i < 3; i++)
    {
        do
        {
            row = rand() % 2 + size - 2; // pick a random row between size-2 and size-1 (e.g. rows 3 and 4 if size is 5)
            col = rand() % size;       // pick a random column between 0 and size-1
        } 
        while(boardPieces[row][col] != EMPTY);
        
        boardPieces[row][col] = BOMB;
        boardColor[row][col]  = RED;
    }
    
    // 1 of either the MARSHAL or GENERAL, randomly selected, to be randomly assigned to one of the two back
    // two rows for each player (i.e., rows 0 and 1 for BLUE and rows 3 and 4 for RED) and any column (i.e., 0 through 4).
    Pieces randomPiece = (rand() % 2 + 1) == 1 ? MARSHAL : GENERAL;    //pick either MARSHAL or GENERAL randomly for the BLUE player
    do
    {
        row = rand() % 2;    // pick a random row between 0 and 1
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[row][col] != EMPTY);
    
    boardPieces[row][col] = randomPiece;
    boardColor[row][col]  = BLUE;
    
    randomPiece =  (rand() % 2 + 1) == 1 ? MARSHAL: GENERAL;    //pick either MARSHAL or GENERAL randomly for the RED player
    do
    {
        row = rand() % 2 + size - 2;    // pick a random row between size-2 and size-1 (e.g. rows 3 and 4 if size is 5)
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[row][col] != EMPTY);
    
    boardPieces[row][col] = randomPiece;
    boardColor[row][col]  = RED;
    
    //  Randomly assign 1 MINER to one of the two back two rows for each player
    //  (e.g. rows 0 and 1 for BLUE and rows 3 and 4 for RED) and any column (i.e., 0 through size-1).
    do
    {
        row = rand() % 2;    // pick a random row between 0 and 1
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[row][col] != EMPTY);
   
    boardPieces[row][col] = MINER;
    boardColor[row][col]  = BLUE;
    
    do
    {
        row = rand() % 2 + size - 2; // pick a random row between size-2 and size-1 (e.g. rows 3 and 4 if size is 5)
        col = rand() % size;       // pick a random column between 0 and size-1
    } 
    while(boardPieces[row][col] != EMPTY);
    
    boardPieces[row][col] = MINER;
    boardColor[row][col]  = RED;
    
    //  Randomly assign 1 SPY to one of the two back two rows for each player
    //  (e.g. rows 0 and 1 for BLUE and rows 3 and 4 for RED) and any column (i.e., 0 through size-1).
    do
    {
        row = rand() % 2;    // pick a random row between 0 and 1
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[row][col] != EMPTY);
    
    boardPieces[row][col] = SPY;
    boardColor[row][col]  = BLUE;
    
    do
    {
        row = rand() % 2 + size - 2;    // pick a random row between size-2 and size-1 (e.g. rows 3 and 4 if size is 5)
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[row][col] != EMPTY);
    
    boardPieces[row][col] = SPY;
    boardColor[row][col]  = RED;
    
    /*
    Randomly assign 3 of any of COLONEL, MAJOR, CAPTAIN, LIEUTENTANT, or SERGEANT,
    randomly selected, to one of the two back two rows for each player
    (i.e., rows 0 and 1 for BLUE and rows 3 and 4 for RED)
    and any column (i.e., 0 through 4). Duplicates are acceptable
    */

    for (i = 0; i < 3; i++)
    {
        int val =  (rand() % 5 + 3); // generate a random number between 3 and 7 inclusive, to randomly select a piece to be assigned
        
        do
        {
            row = rand() % 2;   // pick a random row between 0 and 1
            col = rand() % size; // pick a random column between 0 and size-1
        } 
        while(boardPieces[row][col] != EMPTY);
        
        //switch statement to determine which piece aligns with the random number generated (BLUE)
        switch(val)
        {
            case 3:
                randomPiece = COLONEL;
                break;
            case 4:
                randomPiece = MAJOR;
                break;
            case 5:
                randomPiece = CAPTAIN;
                break;
            case 6:
                randomPiece = LIEUTENANT;
                break;
            case 7:
                randomPiece = SERGEANT;
                break;
            default:
                randomPiece = EMPTY;
        }
        boardPieces[row][col] = randomPiece;
        boardColor[row][col]  = BLUE;
    }
    
    for (i = 0; i < 3; i++)
    {
        int val =  (rand() % 5 + 3); // generate a random number between 3 and 7 inclusive, to randomly select a piece to be assigned
        
        do
        {
            row = rand() % 2 + size - 2;   // pick a random row between size-2 and size-1 (e.g. rows 3 and 4 if size is 5)
            col = rand() % size; // pick a random column between 0 and size-1
        } 
        while(boardPieces[row][col] != EMPTY);
        //switch statement to determine which piece aligns with the random number generated (RED)
        switch(val)
        {
            case 3:
                randomPiece = COLONEL;
                break;
            case 4:
                randomPiece = MAJOR;
                break;
            case 5:
                randomPiece = CAPTAIN;
                break;
            case 6:
                randomPiece = LIEUTENANT;
                break;
            case 7:
                randomPiece = SERGEANT;
                break;
            default:
                randomPiece = EMPTY;
        }
        boardPieces[row][col] = randomPiece;
        boardColor[row][col]  = RED;
    }    
}
/* 
============================================================================
Function    : printBoard
Parameters  : the two enumerated type arrays and the size
Return      : nothing as it is a void function.
Description : This function prints out the actual board to the screen.
============================================================================
*/
void printBoard(Pieces (&boardPieces)[BOARD_SIZE][BOARD_SIZE],
                Color (&boardColor)[BOARD_SIZE][BOARD_SIZE], int size)
{
    //declaring the variables
    int i;
    int row;
    int col;
    
    // Print column header
	printf("   ");
	for(i = 1; i < size + 1; i++)
	{
		printf( " %d", i);
	}
	printf("  \n");

    // Print top border
	printf("  +");
	for (i = 1; i < size + 1; i++)
	{
		printf( "--");
	}
	printf("-+\n");

    // Print each row of the board, 
	// Row name, followed by the beginning border, followed by pieces, and finally the trailing border
    for (int row = 0; row < size; row++)
    {

		// Add ASCII 65 ('A') to the row number to get the row name, and print it as a char by using a static cast.
        printf("%c |", static_cast<char>(row + 65));

		// Print the board pieces for each column of this row.
        for (int col = 0; col < size; col++)
        {
			if (boardColor[row][col] == BLUE)
			{
                // print BLUE colors pieces
				printf(" \033[1;34m%c\033[0m", boardPieces[row][col]);
			}
			else if (boardColor[row][col] == RED)
			{
                // print RED colored pieces
				printf(" \033[1;31m%c\033[0m", boardPieces[row][col]);
			}
            else
            {
                // print EMPTY spots, with no color
                printf(" %c", boardPieces[row][col]);
            }
        }
        printf(" |\n");
    }
    // Print bottom border
    printf("  +");
    for (i = 1; i < size + 1; i++)
    {
        printf( "--");
    }
    printf("-+\n");
}