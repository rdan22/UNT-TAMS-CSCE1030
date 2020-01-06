/*
 =====================================================================
 Name 			: homework3.cpp
 Author			: Riya Danait (RiyaDanait@my.unt.edu)
 Description	: The program performs simple arithmetic calculations 
 				  based on input from the user. 
 =====================================================================
*/ 
#include <iostream>
#include <iomanip>
using namespace std;
/*
 ===================================================================================
 Function 		: drawTriangle
 Parameters		: Passes through row, i and evenInt 
 Description	: This void function prints out a triangle with evenInt rows,
 				  where each row has that many numbers, Each row in the triangle 
 				  will be composed of a certain integer number 
 				  (and space where needed)-- the top row contains one 1, the second 
 				  row contains two 2's, the third contains three 3's and so on.
 ===================================================================================
*/ 
void drawTriangle(int evenInt)
{
    //for loop to generate the number of rows
    for(int row = 1; row <= evenInt; row++)
    { 
        //for loop to generate the spaces
        for(int space = 2*(evenInt - row)-1; space >= 0; space--)
        {
            cout << " ";
        }
        /*This for loop serves as a counter for the number of rows
        and it contains a nested if-else statement that determines how 
        many spaces need to be between each number, since it is clear that the 
        numbers 1 - 9 in the triangle contain 2 spaces, while the numbers 10-12 contain 
        no spaces as they contain more characters.*/
        for(int i = 1; i <= row; i++)
        {
            if(row < 10)
            {
                cout << " " << row;
            }
            else
            {
                cout << row;
            }
        }
        //makes sure to start on a new line for each row
        cout << endl;
    }
}
/*
 =============================================================================
 Function 		: isEven
 Parameters		: a user input of the data type integer (evenInt) that is used
 				  throughout the program and is passed in other functions
 Description	: This bool function determines whether the number that the
 				  user inputs is even. 
 =============================================================================
*/ 
bool isEven (int evenInt)
{
    /*If portion of the if-else statement with parameters such that the user 
    input evenInt is between 2 and 12, and is congruent to 0 (mod 2) meaning
    it is even. It returns true. */
	if (evenInt % 2 == 0 && evenInt >= 2 && evenInt <= 12)
	{
        //the integer is even
    	cout << evenInt << " is even.\n";
 	return true;
	}
    /*Else portion of the if-else statement that returns an error message if the above
    conditions aren't satisfied. It returns false.*/
  	else 
  	{ 
  		// the integer is odd
  		cerr << evenInt << " is an invalid entry." << endl;
    return false;
    }
}
/*
 ==========================================================================
 Function 		: calculateProduct
 Parameters		: Using the evenInt, a counter and a product which updates
 				  each time the for loop runs
 Description	: This function calculates the product of the integers from
 				  2 to evenInt. 
 ==========================================================================
*/ 
int calculateProduct(int evenInt)
{
		//initializes the product to 1 as we will be multiplying the counter to it
		int product = 1;
        //This for loop creates a counter <= the user input evenInt and increments the counter
		for(int i = 1; i <= evenInt; ++i)
    	{
            //the initialized product is multiplied by the counter.
        	product *= i;
    	}
        //couts the product and returns the product as well. 
    	cout << "The product of integers from 2 to " << evenInt << " is " << product << ".\n";
    	return product;
}
/*
 =============================================================================
 Function 		: main
 Parameters		: Passes in evenInt, x, y, and the void function drawTriangle
 Description	: The main function is called at the startup of the program. 
 =============================================================================
*/ 
int main()
{
	//declaring and initializing of variables
    int evenInt = 0;
	bool x = false;
	int y = 0;
	cout << "**********************************************\n"
    "Computer Science and Engineering\n"
    "CSCE 1030 - Computer Science I\n"
    "Riya Danait    rd0305   rd0305@my.unt.edu\n"
    "**********************************************\n";
	//while x is not false, run the following
	while(!x)
    {
    	cout << "Please enter an EVEN integer in range 2 - 12: ";
		cin >> evenInt;
    	x = isEven(evenInt);
    }
    //referencing the calculateProduct function
    y = calculateProduct(evenInt);
    //referencing the drawTriangle function
    drawTriangle(evenInt);

return 0;
}
