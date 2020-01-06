/* 
============================================================================
Name        : hw6main.cpp
Author      : Riya Danait
Date        : 12/6/17
Description : This is the main function that holds the local include 
              directive for the header file as well as the main function for 
              the program.
============================================================================
*/
#include "hw6prgm.h"
#include <stdio.h>
#include <string>
#include <ctype.h>


int main()
{
	
	bool gameOver = false;  // Flag to determine if the game is over (if FLAG is captured)
    bool reveal = false;    // Flag to control whether to reveal BLUE player positions
    string currentPosition, newPosition;
	gamePiece **boardPieces; // Pointer to pointer to a dynamically allocated 2-D array of board pieces
	bool validInput = false; // Input validation flag
    char saveFile;           // BONUS: Variable to store user input to determine if game is to be saved

	//allocating memory for board pieces
	boardPieces = new gamePiece* [BOARD_SIZE];

	for(int i = 0; i < BOARD_SIZE; i++)
	{
		boardPieces[i] = new gamePiece[BOARD_SIZE];
	}
    
    //calling all the functions
	header();
    rules();

    initBoard(boardPieces, BOARD_SIZE);

    // Assign pieces to game board - Randomly if starting new game. Loading from file if resuming existing game
    assignPieces(boardPieces, BOARD_SIZE);    
    
    printBoard(boardPieces, BOARD_SIZE, reveal);

    //condition for whether FLAG was captured
    while (!gameOver)
    {

		while(!validInput)
		{

    		// user inputs currrent coordinates
    		cout << "RED MOVE: Enter current coordinates of piece (e.g., D2, or QQ to quit): ";
    		cin >> currentPosition;
            
    		if(currentPosition == "QQ")
    		{
                
    			cout << "Would you like to save the game before quitting? (Y/N)";
    			cin >> saveFile;

    			if (toupper(saveFile) == 'Y')
    			{
                    //save the game to a file before exiting
                    cout << "Saving the game and exiting..";
                    saveGame(boardPieces, BOARD_SIZE);   // BONUS: save game to be resumed in a subsequent session.
                    cout << "Please play again soon!" << endl;
                    printBoard(boardPieces, BOARD_SIZE, false);
    			}
                else
                {
                    cout << "RED player forfeits game. Please play again soon!" << endl;
                    printBoard(boardPieces, BOARD_SIZE, true);
                    remove("game.dat"); // remove any previously saved file as this game is over
                }
                
                cleanUp(boardPieces, BOARD_SIZE); // return memory to free store before exiting
 				exit(0);
    		}
    		else
    		{
                validInput = validateCurrentCoordinates(boardPieces, BOARD_SIZE, currentPosition);
            }
    	}
        
    	//user inputs new coordinates
    	validInput = false; // reset flag for new coordinates

    	while (!validInput)
    	{
			cout << "RED MOVE: Enter new coordinates of piece at " << currentPosition << ":";
    		cin >> newPosition;
            
            validInput = validateNewCoordinates(boardPieces, BOARD_SIZE, currentPosition, newPosition);
        }

        validInput = false; // reset input validation flag to get ready for next RED move
    	
        gameOver = updateBoard(boardPieces, currentPosition, newPosition);
        
        if (gameOver)
                reveal = true;
    	
        printBoard(boardPieces, BOARD_SIZE, reveal);
    	
    }
    //returning memory to freestore
    cleanUp(boardPieces, BOARD_SIZE);
}
