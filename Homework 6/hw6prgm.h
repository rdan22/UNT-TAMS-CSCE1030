/* 
============================================================================
Name        : hw6prgm.h
Author      : Riya Danait
Date        : 12/6/17
Description : This header file contains all the definitions/declarations
			  necessary to run the program.  
============================================================================
*/
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
using namespace std;
//head function calls with name/information and rules
void header();
void rules();
//declaring the global variables
const int BOARD_SIZE = 5;
//game pieces
enum PieceType{ 	
	EMPTY 	= ' ',
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
	SPY 	= 'S',
	HIDDEN = 'X'};

//game colors
enum Color {RED = 'R', 
			BLUE = 'B', 
			NONE = 'N'};
//struct
typedef struct {

	PieceType piece;
	Color color;	
	bool isMoveable;

} gamePiece;

//function declarations
void initBoard(gamePiece** boardPieces, int boardSize);
void assignPieces(gamePiece** boardPieces, int boardSize);
void printBoard(gamePiece** boardPieces, int boardSize, bool reveal);
bool validateCurrentCoordinates(gamePiece** boardPieces, int boardSize, string currentPosition);
bool validateNewCoordinates(gamePiece** boardPieces, int boardSize, string currentPosition, string newPosition);
bool updateBoard(gamePiece** boardPieces, string currentPosition, string newPosition);
void cleanUp(gamePiece** boardPieces, int boardSize);

//Bonus - functions for saving and loading the game progress from a file
bool saveGame(gamePiece** boardPieces, int boardSize);
bool loadGame(gamePiece** boardPieces, int& boardSize);
