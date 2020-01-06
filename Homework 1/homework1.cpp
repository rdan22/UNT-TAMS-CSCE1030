/*
Homework 1 submitted by Riya Danait, CSCE 1030 Section 002, 9/9/17
The following code determines the increase in temperature of the hot reservoir required to yield a higher Carnot efficiency, where the temperature of the cold reservoir stays the same.
*/

#include <iostream>   
#include <iomanip> 
// #include <math.h> 
using namespace std;

int main (){
	
	cout << "Homework submitted by : Riya Danait\n";
	cout << "EUID: rd0305\n";
	cout << "Email: riyadanait@my.unt.edu\n";
	cout << "CSCE 1030 Section 002" << endl;

	//I am assigning a variable, n1, for the original Carnot Efficiency.
	double n1;
	//I am assigning a variable, n2, for the increased Carnot Efficiency.
	double n2; 
	//I am assigning a variable for the temperature of the cold reservoir in degrees Celsius.
	int coldReservoirTemperature;
	

	//cout statements for the initial inputs
	cout << "Enter the original Carnot efficiency (0 < n1 < 1):\n";
	//This cin statement will read the line and get the user's input 
	cin >> n1;
	cout << "Enter the improved Carnot efficiency (0 < n2 < 1 and n1 < n2):\n";
	//This cin statement will read the line and get the user's input 
	cin >> n2;
	cout << "Enter the temperature for the cold reservoir in Celsius:\n";
	//This cin statement will read the line and get the user's input 
	cin >> coldReservoirTemperature;
	

	/*
	Now, I am assigning a variable to store the value of the increase in temperature for the hot reservoir. I am also converting cold reservoir temperature from Celsius to Kelvin using T(Kelvin)= T(Celsius) + 273.15
	*/
	double hotReservoir = ((coldReservoirTemperature + 273.15)/(1-n2)) - ((coldReservoirTemperature + 273.15)/(1-n1));
	
	//This sets the precision to 2 decimal places. 
	cout.setf(ios::fixed);
	cout.precision(2);

	//Prints the increase in temperature for the hot reservoir in Kelvin
    cout << "The temperature of the hot reservoir must increase by: " << hotReservoir << " K." << endl;


    return 0;

}