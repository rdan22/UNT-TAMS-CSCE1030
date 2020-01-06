/* 
============================================================================
Name        : hw6func.cpp
Author      : Riya Danait
Date        : 12/6/17
Description : This is the .cpp file that contains all of the functions for 
              the program. 
============================================================================
*/
#include "hw6prgm.h"
#include <fstream>

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
	"   or the GENERAL (2). When pieces have equal rank, then both pieces are\n"
    "   removed.\n"
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
Parameters  : The pointer to the pointer for the two dimension dynamic array
              , the board size, the string for the position of the piece. 
Return      : nothing as it is a void function.
Description : This function simply initializes the board to NONE color and
EMPTY pieces.
============================================================================
*/
void initBoard(gamePiece** boardPieces, int size)
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
            boardPieces[row][col].piece = EMPTY;
            boardPieces[row][col].color  = NONE;
            boardPieces[row][col].isMoveable = false;
        }
    }
}
/* 
============================================================================
Function    : assignPieces
Parameters  : The pointer to the pointer for the two dimension dynamic array
              , the board size, the string for the position of the piece. 
Return      : nothing as it is a void function.
Description : This function uses a random number generator to randomly 
assign some of the game pieces to the board (for both BLUE and RED). 
============================================================================
*/
void assignPieces(gamePiece** boardPieces, int size)
{
	//declaring the variables
    int i;
    //declaring and initializing the row and column variables 
    int col = 0;
    int row = 0;
    char choice;
    
    
    // BONUS: Prompt player if they would like to resume last saved game.
    // If so, load the game file saved previously, rather than generating random piece assignments.
    cout << "Resume previously saved game ? (R to resume, N to start new game): ";
    
    cin >> choice;
    
    if (toupper(choice) == 'R')
    {
        // Load saved game from file
        if (loadGame(boardPieces, size))
        {
            cout << "Resuming previously saved game ... \n";
            return;
        }
        else
        {
            cout << "Could not load previously saved game. Startng new game...\n";
        }
    }
    
    // User chose not to resume a previously saved game
    // Start a new game board by generating random assignments for BLUE and RED pieces
    
    cout << "Assigning BLUE pieces to the board ... \n";
    cout << "Assigning RED pieces to the board ... \n";

    srand(time(NULL)); // Seed Random function
    
    // Randomly assign 1 FLAG to the back row (row 0) of BLUE player
    // in any one column (i.e., 0 through size - 1).
    do
    {
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[0][col].piece != EMPTY);
    
    boardPieces[0][col].piece = FLAG;
    boardPieces[0][col].color  = BLUE;
    boardPieces[0][col].isMoveable = false;
    
    // Randomly assign 1 FLAG to the back row (row 4) of RED player
    // in any one column (i.e., 0 through size - 1).
    do
    {
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[size - 1][col].piece != EMPTY);
    
    boardPieces[size - 1][col].piece = FLAG;
    boardPieces[size - 1][col].color = RED;
    boardPieces[size - 1][col].isMoveable = false;
    
    
    //  Randomly assign 3 BOMBs to one of the two back two rows (i.e. rows 0 and 1) of BLUE player
    //  in any column (i.e., 0 through size-1).
    
    for (i = 0; i < 3; i++)
    {
        do
        {
            row = rand() % 2;    // pick a random row between 0 and 1
            col = rand() % size; // pick a random column between 0 and size-1
        } 
        while(boardPieces[row][col].piece != EMPTY);
        
        boardPieces[row][col].piece = BOMB;
        boardPieces[row][col].color = BLUE;
        boardPieces[row][col].isMoveable = false;
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
        while(boardPieces[row][col].piece != EMPTY);
        
        boardPieces[row][col].piece = BOMB;
        boardPieces[row][col].color = RED;
        boardPieces[row][col].isMoveable = false;
    }
    
    // 1 of either the MARSHAL or GENERAL, randomly selected, to be randomly assigned to one of the two back
    // two rows for each player (i.e., rows 0 and 1 for BLUE and rows 3 and 4 for RED) and any column (i.e., 0 through 4).
    PieceType randomPiece = (rand() % 2 + 1) == 1 ? MARSHAL : GENERAL;    //pick either MARSHAL or GENERAL randomly for the BLUE player
    do
    {
        row = rand() % 2;    // pick a random row between 0 and 1
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[row][col].piece != EMPTY);
    
    boardPieces[row][col].piece = randomPiece;
    boardPieces[row][col].color  = BLUE;
    boardPieces[row][col].isMoveable = true;

    
    randomPiece =  (rand() % 2 + 1) == 1 ? MARSHAL: GENERAL;    //pick either MARSHAL or GENERAL randomly for the RED player
    do
    {
        row = rand() % 2 + size - 2;    // pick a random row between size-2 and size-1 (e.g. rows 3 and 4 if size is 5)
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[row][col].piece != EMPTY);
    
    boardPieces[row][col].piece = randomPiece;
    boardPieces[row][col].color = RED;
    boardPieces[row][col].isMoveable = true;

    
    //  Randomly assign 1 MINER to one of the two back two rows for each player
    //  (e.g. rows 0 and 1 for BLUE and rows 3 and 4 for RED) and any column (i.e., 0 through size-1).
    do
    {
        row = rand() % 2;    // pick a random row between 0 and 1
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[row][col].piece != EMPTY);
   
    boardPieces[row][col].piece  = MINER;
    boardPieces[row][col].color  = BLUE;
    boardPieces[row][col].isMoveable = true;
    
    do
    {
        row = rand() % 2 + size - 2; // pick a random row between size-2 and size-1 (e.g. rows 3 and 4 if size is 5)
        col = rand() % size;       // pick a random column between 0 and size-1
    } 
    while(boardPieces[row][col].piece != EMPTY);
    
    boardPieces[row][col].piece  = MINER;
    boardPieces[row][col].color  = RED;
    boardPieces[row][col].isMoveable = true;
    
    //  Randomly assign 1 SPY to one of the two back two rows for each player
    //  (e.g. rows 0 and 1 for BLUE and rows 3 and 4 for RED) and any column (i.e., 0 through size-1).
    do
    {
        row = rand() % 2;    // pick a random row between 0 and 1
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[row][col].piece != EMPTY);
    
    boardPieces[row][col].piece = SPY;
    boardPieces[row][col].color = BLUE;
    boardPieces[row][col].isMoveable = true;
    
    do
    {
        row = rand() % 2 + size - 2;    // pick a random row between size-2 and size-1 (e.g. rows 3 and 4 if size is 5)
        col = rand() % size; // pick a random column between 0 and size-1
    } 
    while(boardPieces[row][col].piece != EMPTY);
    
    boardPieces[row][col].piece  = SPY;
    boardPieces[row][col].color  = RED;
    boardPieces[row][col].isMoveable = true;
    
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
        while(boardPieces[row][col].piece != EMPTY);
        
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
        boardPieces[row][col].piece  = randomPiece;
        boardPieces[row][col].color  = BLUE;
        boardPieces[row][col].isMoveable = true;

    }
    
    for (i = 0; i < 3; i++)
    {
        int val =  (rand() % 5 + 3); // generate a random number between 3 and 7 inclusive, to randomly select a piece to be assigned
        
        do
        {
            row = rand() % 2 + size - 2;   // pick a random row between size-2 and size-1 (e.g. rows 3 and 4 if size is 5)
            col = rand() % size; // pick a random column between 0 and size-1
        } 
        while(boardPieces[row][col].piece != EMPTY);
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
        boardPieces[row][col].piece  = randomPiece;
        boardPieces[row][col].color  = RED;
        boardPieces[row][col].isMoveable = true;
    }
}
/* 
============================================================================
Function    : validateCurrentCoordinates
Parameters  : The pointer to the pointer for the two dimension dynamic array
              , the board size, the string for the position of the piece. 
Return      : Returns true.
Description : This function validates the coordinates the user picks to move.
============================================================================
*/
bool validateCurrentCoordinates(gamePiece** boardPieces, int boardSize, string currentPosition)
{
    int row;
    int col;
    
    if (currentPosition.length() > 2)
    {
        cout << "Error: invalid coordinates " << currentPosition << ". Try again..." << endl;
        return false;
    }
    
    row = currentPosition[0] - 'A';  // convert first coordinate to row number
    col = currentPosition[1] - '1';  // convert second cooordinate to colum number
    
    if ((row < 0) || (row > (boardSize-1)))
    {
        cout << "Error: Invalid row location " << currentPosition[0] << ". Try again..." << endl;
        return false;
    }
    
    if ((col < 0) || (col > (boardSize - 1)))
    {
        cout << "Error: Invalid column location " << currentPosition[1] << ". Try again..." << endl;
        return false;
    }
    
    if ((!boardPieces[row][col].isMoveable)
        || (boardPieces[row][col].piece == EMPTY)
        || (boardPieces[row][col].color == BLUE))
    {
        cout << "Error: Invalid piece or not moveable at " << currentPosition << ". Try again..."<< endl;
        return false;
    }
    
    return true;
}
/* 
============================================================================
Function    : validateNewCoordinates
Parameters  : The pointer to the pointer for the two dimension dynamic array
              , the board size, the string for the current position of the 
              piece, and the string for the position of the new location. 
Return      : Returns true.
Description : This function validates the new coordinates the user picks to 
              move to.
============================================================================
*/
bool validateNewCoordinates(gamePiece** boardPieces, int boardSize, string currentPosition, string newPosition)
{
    int currentRow, currentCol;
    int newRow, newCol;

    currentRow = currentPosition[0] - 'A';
    currentCol = currentPosition[1] - '1';
    
    newRow = newPosition[0] - 'A';  // convert first coordinate to row number
    newCol = newPosition[1] - '1';  // convert second cooordinate to colum number
   
    
    // if coordinates are longer than 2 characters, they are invald
    if (newPosition.length() > 2)
    {
        cout << "Error: invalid coordinates " << newPosition << ". Try again..." << endl;
        return false;
    }
    
    // check if row is out of range
    if ((newRow < 0) || (newRow > (boardSize-1)))
    {
        cout << "Error: Invalid row location " << newPosition[0] << ". Try again..." << endl;
        return false;
    }
    
    // check if column is out of range
    if ((newCol < 0) || (newCol > (boardSize - 1)))
    {
        cout << "Error: Invalid column location " << newPosition[1] << ". Try again..." << endl;
        return false;
    }

    // check if the new position is already occupied by a RED piece
    if (boardPieces[newRow][newCol].color == RED)
    {
        cout << "Error: Invalid piece or not moveable at " << newPosition << ". Try again..."<< endl;
        return false;
    }

    // check if the move is illegal - can only move up/down or left/right by one position
    if ((newRow != currentRow) && (newCol != currentCol))
    {
        cout << "Error: Invalid piece move " << currentPosition << " to " << newPosition << ". Try again..."<< endl;
        return false;
    }
    
    if ((abs(newRow-currentRow) > 1) || (abs(newCol-currentCol) > 1))
    {
        cout << "Error: Invalid piece move " << currentPosition << " to " << newPosition << ". Try again..."<< endl;
        return false;
    }
    
    return true;
}
/* 
============================================================================
Function    : updateBoard
Parameters  : The pointer to the pointer for the two dimension dynamic array
              , the string for the position of the piece. 
Return      : Returns false.
Description : This function updates the board.
============================================================================
*/
bool updateBoard(gamePiece** boardPieces, string currentPosition, string newPosition)
{
    int currentRow, currentCol;
    int newRow, newCol;
    
    currentRow = currentPosition[0] - 'A';
    currentCol = currentPosition[1] - '1';
    
    newRow = newPosition[0] - 'A';  // convert first coordinate to row number
    newCol = newPosition[1] - '1';  // convert second cooordinate to colum number
 
    
    // Handle the case where new position is empty
    if (boardPieces[newRow][newCol].piece == EMPTY)
    {
        
        cout << "RED " << (char) boardPieces[currentRow][currentCol].piece << " move from "
             << currentPosition << " to " << newPosition << endl;
        
        // Move piece to new position on the board
        boardPieces[newRow][newCol].piece = boardPieces[currentRow][currentCol].piece;
        boardPieces[newRow][newCol].color = boardPieces[currentRow][currentCol].color;
        boardPieces[newRow][newCol].isMoveable = boardPieces[currentRow][currentCol].isMoveable;
        
        
        // Clear current position on the board
        boardPieces[currentRow][currentCol].piece = EMPTY;
        boardPieces[currentRow][currentCol].color = NONE;
        boardPieces[currentRow][currentCol].isMoveable = false;
        
        return false;
    }
    else{
        
        // Check if destination positon is a FLAG. If so, RED wins the game.
        if (boardPieces[newRow][newCol].piece == FLAG)
        {
            // Game Won!
            cout << "RED " << (char) boardPieces[currentRow][currentCol].piece << " at " << currentPosition
                 << " captures BLUE " << (char) boardPieces[newRow][newCol].piece << " at " << newPosition
                 << ". Congratulations!" << endl;
            boardPieces[newRow][newCol].color = NONE;
            return true;
        }
        
        // Check if destination positon is a BOMB
        if (boardPieces[newRow][newCol].piece == BOMB)
        {
            if (boardPieces[currentRow][currentCol].piece == MINER)
            {
                cout << "RED " << (char) boardPieces[currentRow][currentCol].piece << " at " << currentPosition
                << " defuses BLUE " << (char) boardPieces[newRow][newCol].piece << " at " << newPosition << "." << endl;
                
                // Move MINER to new position on the board
                boardPieces[newRow][newCol].piece = boardPieces[currentRow][currentCol].piece;
                boardPieces[newRow][newCol].color = boardPieces[currentRow][currentCol].color;
                boardPieces[newRow][newCol].isMoveable = boardPieces[currentRow][currentCol].isMoveable;
                
                // Clear current position on the board
                boardPieces[currentRow][currentCol].piece = EMPTY;
                boardPieces[currentRow][currentCol].color = NONE;
                boardPieces[currentRow][currentCol].isMoveable = false;
            }
            else
            {
                cout << "RED " << (char) boardPieces[currentRow][currentCol].piece << " at " << currentPosition
                     << " blown up by BLUE " << (char) boardPieces[newRow][newCol].piece << " at " << newPosition << "." << endl;
                
                // Clear current position on the board
                boardPieces[currentRow][currentCol].piece = EMPTY;
                boardPieces[currentRow][currentCol].color = NONE;
                boardPieces[currentRow][currentCol].isMoveable = false;
               
                
            };
            return false;
        }
        
        // Check if the RED piece is a SPY and destination position is a MARSHAL (1) or a GENERAL (2)
        
        if ((boardPieces[currentRow][currentCol].piece == SPY) &&
            ((boardPieces[newRow][newCol].piece == MARSHAL) || (boardPieces[newRow][newCol].piece == GENERAL)))
        {
            // A SPY can capture a Marshal or General
            
            cout << "RED " << (char) boardPieces[currentRow][currentCol].piece << " at " << currentPosition << " captures "
            << "BLUE " << (char) boardPieces[newRow][newCol].piece << " at " << newPosition << "." << endl;
            
            // Move piece to new position on the board
            boardPieces[newRow][newCol].piece = boardPieces[currentRow][currentCol].piece;
            boardPieces[newRow][newCol].color = boardPieces[currentRow][currentCol].color;
            boardPieces[newRow][newCol].isMoveable = boardPieces[currentRow][currentCol].isMoveable;
            
            // Clear current position on the board
            boardPieces[currentRow][currentCol].piece = EMPTY;
            boardPieces[currentRow][currentCol].color = NONE;
            boardPieces[currentRow][currentCol].isMoveable = false;
            
            return false;
        }
        
        
        // Check if destination position is occupied by a BLUE piece thats superior
        if (boardPieces[newRow][newCol].piece < boardPieces[currentRow][currentCol].piece)
        {
            cout << "RED " << (char) boardPieces[currentRow][currentCol].piece << " at " << currentPosition << " captured by "
            << "BLUE " << (char) boardPieces[newRow][newCol].piece << " at " << newPosition << "." << endl;
            
            // Clear current position on the board
            boardPieces[currentRow][currentCol].piece = EMPTY;
            boardPieces[currentRow][currentCol].color = NONE;
            boardPieces[currentRow][currentCol].isMoveable = false;
            
            return false;
        }
        
        // Check if destination position is occupied by a BLUE piece thats inferior
        if (boardPieces[newRow][newCol].piece > boardPieces[currentRow][currentCol].piece)
        {
            cout << "RED " << (char) boardPieces[currentRow][currentCol].piece << " at " << currentPosition << " captures "
            << "BLUE " << (char) boardPieces[newRow][newCol].piece << " at " << newPosition << "." << endl;
            
            // Move piece to new position on the board
            boardPieces[newRow][newCol].piece = boardPieces[currentRow][currentCol].piece;
            boardPieces[newRow][newCol].color = boardPieces[currentRow][currentCol].color;
            boardPieces[newRow][newCol].isMoveable = boardPieces[currentRow][currentCol].isMoveable;
            
            // Clear current position on the board
            boardPieces[currentRow][currentCol].piece = EMPTY;
            boardPieces[currentRow][currentCol].color = NONE;
            boardPieces[currentRow][currentCol].isMoveable = false;
        
            return false;
        }
        
        
        // Check if destination position is occupied by a BLUE piece thats of equal rank as the RED piece
        if (boardPieces[newRow][newCol].piece == boardPieces[currentRow][currentCol].piece)
        {
            cout << "RED " << (char) boardPieces[currentRow][currentCol].piece << " at " << currentPosition << " and "
            << "BLUE " << (char) boardPieces[newRow][newCol].piece << " at " << newPosition << " eliminate each other." << endl;
            
            // Move piece to new position on the board
            boardPieces[newRow][newCol].piece = EMPTY;
            boardPieces[newRow][newCol].color = NONE;
            boardPieces[newRow][newCol].isMoveable = false;
            
            // Clear current position on the board
            boardPieces[currentRow][currentCol].piece = EMPTY;
            boardPieces[currentRow][currentCol].color = NONE;
            boardPieces[currentRow][currentCol].isMoveable = false;
            
            return false;
        }
        
        
    }
    
    return false;

}
/* 
============================================================================
Function    : cleanUp
Parameters  : The pointer to the pointer for the two dimension dynamic array
              and the int board size.
Return      : nothing as it is void.
Description : This function returns the memory to the free store.
============================================================================
*/
void cleanUp(gamePiece** boardPieces, int size)
{
    for(int i = 0; i < size; i++)
        {
            delete boardPieces[i]; 
        }
    delete [] boardPieces;
}
/* 
============================================================================
Function    : printBoard
Parameters  : The pointer to the pointer for the two dimension dynamic array
              , the board size, and the boolean reveal. 
Return      : nothing as it is void.
Description : This function prints out the game board.
============================================================================
*/
void printBoard(gamePiece** boardPieces, int size, bool reveal)
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
			if (boardPieces[row][col].color == BLUE)
			{
                if(reveal)
                {
                    // print BLUE colors pieces
				    printf(" \033[1;34m%c\033[0m", boardPieces[row][col].piece);
                }
                else
                {
                    printf(" \033[1;34m%c\033[0m", HIDDEN);
                }
			}
			else if (boardPieces[row][col].color == RED)
			{
                // print RED colored pieces
				printf(" \033[1;31m%c\033[0m", boardPieces[row][col].piece);
			}
            else
            {
                // print EMPTY spots, with no color
                printf(" %c", boardPieces[row][col].piece);
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
//Bonus - functions for saving and loading the game progress from a file
/* 
============================================================================
Function    : saveGame
Parameters  : The pointer to the pointer for the two dimension dynamic array
              and the int board size.
Return      : Returns true.
Description : This function saves the game to an output file. 
============================================================================
*/
bool saveGame(gamePiece** boardPieces, int boardSize)
{
    ofstream gameFileStream;
    int row;
    int col;
    
    gameFileStream.open("game.dat");
    
    //checks to see if the opening failed
    if(gameFileStream.fail())
    {
        cout << "Could not open the file game.dat to save the game\n";
        return false;
    }
    
    gameFileStream << boardSize << endl;
    
    for (row = 0; row < boardSize; row++)
    {
        for (col = 0; col < boardSize; col++)
        {
            gameFileStream << boardPieces[row][col].piece << ' ' << boardPieces[row][col].color << ' ' <<   boardPieces[row][col].isMoveable << ' ';
        }
    }
    gameFileStream.close(ff);
    
    return true;
    
}
/* 
============================================================================
Function    : loadGame
Parameters  : The pointer to the pointer for the two dimension dynamic array
              and the int board size.
Return      : Returns true.
Description : This function loads a game from an input file. 
============================================================================
*/
bool loadGame(gamePiece** boardPieces, int& boardSize)
{
    ifstream gameFileStream;
    int row;
    int col;
    int piece;
    int  color;
    bool isMoveable;
    
    
    gameFileStream.open("game.dat");
    //checks to see if the opening failed
    if(gameFileStream.fail())
    {
        cout << "Could not open the file game.dat to load the game\n";
        return false;
    }
    
    gameFileStream >> boardSize;
    
    for (row = 0; row < boardSize; row++)
    {
        for (col = 0; col < boardSize; col++)
        {
            gameFileStream >> piece;
            gameFileStream >> color;
            gameFileStream >> isMoveable;
            
            boardPieces[row][col].piece = (PieceType) piece;
            boardPieces[row][col].color = (Color) color;
            boardPieces[row][col].isMoveable = isMoveable;
            
        }
    }
    
    gameFileStream.close();
    
    return true;
    
}
