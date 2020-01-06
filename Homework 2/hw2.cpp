/* Author: Riya Danait (RiyaDanait@my.unt.edu)
EUID: rd0305
Date: 9/22/2017
Intstructor: Joseph Helsing
Department and Course Number: CSCE 1030 Section 002 */
#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{

    //declaring the variables
    int total = 0;
    int infectious = 0;
    int iPrevious = 0;
    int susceptible = 0;
    int sPrevious = 0;
    int recovered = 0;
    int rPrevious = 0;
    double contactRate = 0.0;
    double recoveryRate = 0.0;
    int day = 0;
	
    cout << "**********************************************\n"
    "Computer Science and Engineering\n"
    "CSCE 1030 - Computer Science I\n"
    "Riya Danait    rd0305   rd0305@my.unt.edu\n"
    "**********************************************\n";
    
    cout << "Welcome to the outbreak simulator.";

     //do-while loop which runs at least once to make sure the user inputs the correct data type for the total population
    do
    {
        cout << "\nPlease enter a positive, whole number for the total of the population you wish to simulate: ";
        cin >> total;
	   
            //to allow for an invalid (decimal or negative) input - clears input buffer and sets total to 0
            if (cin.fail())
             {
                total = 0;
             }
            cin.clear(); 

            //error message if-else statement
            if (total > 0) 
            {
		      break;
            }
            else
            {
                //actual error message
                cerr << "\n" << total << " is not a positive whole number. Please enter a positive whole number for the total population: ";
    
            }
    }
    while (total <= 0);
 
    //do-while loop which runs at least once to make sure the user inputs the correct data type for the number of infectious people
    do
    {
        cout << "\nPlease enter a positive, whole number that is less than the total population for the number of infectious individuals: ";
        cin >> infectious;
	       
            //to allow for an invalid (decimal or negative) input - clears input buffer and sets total to 0
            if (cin.fail())
            {
                infectious = 0;
            }
            cin.clear(); 

            //erro message if-else statement
            if ((infectious > 0) && (infectious < total))
		    {
                break;
            }
            else
            {
                //actual error message
                cerr << "\n" << infectious << " is not a positive whole number or is greater than the total population.";
            }
    }
     while ((infectious <= 0) || (infectious >= total));


     //do-while loop which runs at least once to make sure the user inputs the correct data type for the contact rate
     do
     {
     	cout << "\nPlease enter a positive number greater than 0 and less than 1 for the contact rate: ";
        cin >> contactRate;
            //error message if-else statement
            if ((contactRate > 0.0) && (contactRate < 1.0))
        	{
                break;
            }
            else
            {   
                //actual error message
                cerr << "\n" << contactRate << " is not greater than 0 and less than 1.";
            }
    }
    while ((contactRate <= 0.0) || (contactRate >= 1.0));
    
    //do-while loop which runs at least once to make sure the user inputs the correct data type for the recovery rate
    do
    {
    	cout << "\nPlease enter a positive number greater than 0 and less than 1 for the recovery rate: ";
        cin >> recoveryRate;
            //error message if-else statement
            if ((recoveryRate > 0) && (recoveryRate < 1))
            {
        	   break;
            }
            else
            {
                //actual error message
               cerr << "\n" << recoveryRate << " is not greater than 0 and less than 1.";
            }

    }
    while ((recoveryRate<=0) || (recoveryRate>=1.0));

    //calculates the number of susceptible individuals
    susceptible = total - infectious; 
    //setting previous to initial values of susceptible, infectious, and recovered
    sPrevious = susceptible;
    iPrevious = infectious;
    rPrevious = recovered;

    do 
    {
        //equations for S.I.R.
        susceptible = sPrevious - (contactRate)*(iPrevious)*(sPrevious); 
        infectious = iPrevious + (contactRate)*(iPrevious)*(sPrevious) - (recoveryRate)*(iPrevious);
        recovered = rPrevious + (recoveryRate)*(iPrevious);
        //prints out number of days and susceptible, infectious, recovered people each time
        printf("Day: %4d S: %7d I: %7d R: %7d\n", day, susceptible, infectious, recovered);
        //increments day counter by 1
        day++;
        //updates total number of susceptible, infectious, and recovered individuals
        sPrevious = susceptible;
        iPrevious = infectious;
        rPrevious = recovered;
    }
    //based upon when infectious is greater than 0: when it isn't, we end the do-while loop and cout the number of days it took to end. 
    while (infectious > 0);
    cout << "The outbreak took " << day << " days to end." << endl;

    return 0;
}
