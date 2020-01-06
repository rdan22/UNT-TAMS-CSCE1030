/* 
============================================================================
Name        : homework4.cpp
Author      : Riya Danait
Date        : 10/29/17
Description : The program encrypts and decrypts a text file that the user 
creates and incorporates topics including file I/O and Caesar Ciphers. 
============================================================================
*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <locale>
using namespace std;
//function declarations
void encrypt(ifstream& inputFileStream, ofstream& outputFileStream, ofstream& keyFileStream);
void decrypt(ifstream& inputFileStream, ofstream& outputFileStream, ifstream& keyFileStream);

int main()
{
	cout << 
	"+-----------------------------------------------------------+\n"
    "|		Computer Science and Engineering            |\n"
    "|		 CSCE 1030 - Computer Science I             |\n"
    "|	 Riya Danait    rd0305   rd0305@my.unt.edu          |\n"
    "+-----------------------------------------------------------+\n";
	//defining the variables
	char input;
	char plaintextFile[33];
	char encryptedFile[33];
	char keyFile[33];
	bool validInput = false;
	//defining the streams
	ifstream inputFileStream;
	ofstream outputFileStream;
	while(!validInput)
	{
		//prompts the user for either encrypting or decrypting a file
		cout << "Would you like to ENCRYPT or DECRYPT a file (E or D)?: ";
		//saves it in a char input
		cin >> input;
		//if input is e or E, it encrypts
		if(input == 'e' || input == 'E')
		{	
			validInput = true;
			//defines the stream for the key file
			ofstream keyFileStream;
			//prompts the user for the name of the file to encrypt
			cout << "Enter the name of your input file that you'd like to encrypt: ";
			cin >> plaintextFile;
			//opens that file
			inputFileStream.open(plaintextFile);
			//checks to see if the opening failed (if it does, it quits)
			if(inputFileStream.fail())
			{
				cout << "ERROR: Unable to open file: " << plaintextFile << ". Terminating... \n";
				exit(EXIT_FAILURE);
			}
			//otherwise it proceeds as normal and asks for the name of the output file
			cout << "Enter the name of the output file to write the ciphered text to : ";
			cin >> encryptedFile;
			//opens the output file
			outputFileStream.open(encryptedFile);
			//checks to see if the opening failed
			if(outputFileStream.fail())
			{
				cout << "ERROR: Unable to open file: " << encryptedFile << ". Terminating...\n";
				exit(EXIT_FAILURE);
			}
			//asks for the name of the key file
			cout << "Enter the file name that will contain your encryption keys: ";
			cin >> keyFile;
			//opens the key file
			keyFileStream.open(keyFile);
			//checks the see if the opening of the key file fails
			if(keyFileStream.fail())
			{
				cout << "ERROR: Unable to open file: " << keyFile << ". Terminating...\n";
				exit(EXIT_FAILURE);
			}
			//calls the encryption function
			encrypt(inputFileStream, outputFileStream, keyFileStream);
			//closes the three streams
			inputFileStream.close();
			outputFileStream.close();
			keyFileStream.close();
		}
		//else if the input if d or D, it decrypts
		else if(input == 'd' || input == 'D')
		{
			validInput = true;
			//defines the stream for the key file
			ifstream keyFileStream;
			//prompts user for the name of the input file to be decrypted
			cout << "Enter the name of your input file that you'd like to decrypt: ";
			cin >> encryptedFile;
			//opens the input file
			inputFileStream.open(encryptedFile);
			//checks to see if the opening of the input file failed
			if(inputFileStream.fail())
			{
				cout << "ERROR: Unable to open file: " << encryptedFile << ". Terminating...\n";
				exit(EXIT_FAILURE);
			}
			//prompts user for name of the output file
			cout << "Enter the name of the output file to write plaintext: ";
			cin >> plaintextFile;
			//opens the output file
			outputFileStream.open(plaintextFile);
			//checks to see if opening the output file failed
			if(outputFileStream.fail())
			{
				cout << "ERROR: Unable to open file: " << plaintextFile << ". Terminating...\n";
				exit(EXIT_FAILURE);
			}
			//prompts user for the key file name
			cout << "Enter the file name that will contain your encryption keys: ";
			cin >> keyFile;
			//opens the key file
			keyFileStream.open(keyFile);
			//checks to see if key file stream opening failed
			if(keyFileStream.fail())
			{
				cout << "ERROR: Unable to open file: " << keyFile << ". Terminating...\n";
				exit(EXIT_FAILURE);
			}
			//calls the decrypt function
			decrypt(inputFileStream, outputFileStream, keyFileStream);
			//closes all three streams
			inputFileStream.close();
			outputFileStream.close();
			keyFileStream.close();
		}
		/*
		if the value inputted for the encryption or decryption was not valid 
		(i.e was not e, E, d, or D), then it will give an error message.
		*/
		else
		{
			validInput = false;
		}
		}
		return 0;
	}
/* 
============================================================================
Function    : encrypt
Parameters  : the plaintext input file, encrypted output file, and key file 
streams.
Return      : nothing as it is a void function.
Description : This function encrypts a text file from the user and generates 
a key file that was used in the encryption process. The key file is made up 
of randomly generated integers between 3 and 277 that serve as a shift 
cipher for the characters in the text file.
============================================================================
*/
void encrypt(ifstream& plaintextStream, ofstream& encryptedFileStream, ofstream& keyFileStream)
{
	//declaring of the variables
	//k is each number in the key file, c is each character to be encrypted in the output file, m is each original character in the input file
	int k;
	char m;
	int c;
	//seed the random number generator
	srand (time(NULL));
	/* 
	While we get each character from the input file, we also want to generate a random 
	number for k each time to use in the encryption key and save that to the key file.
	*/
	while (plaintextStream.get(m))
	{
		//we want to keep all punctuation the same and put that into the output file as is
		if (ispunct(m))
		{
			encryptedFileStream.put(m);
		}
		//if its not punctuation, we generate random numbers for alphanumeric characters
		else
		{
			//if the character is not a space, we generate the random number
			if (!(isspace(m)))
			{
				k = (rand() % 275) + 3;		// Generate random key between 3 and 277, inclusively.
				//input the random number into the key file
				keyFileStream << k;
				keyFileStream << ' ';
				//for the numeric characters
				if (isdigit(m))
				{
					c = m + (k % 10);	// shift by a maximum of 10 digits

					if (c > 57)		// if encrypted value exceeds ASCII '9', wrap around
					{
						c -= 10;
					}
					else if (c < 48)	// if encryped value is less than ASCII '0' add 10 so that its in range of 0..9 ASCII.
					{
						c += 10;
					}
				}
				else
				{
					//if it is an alphabetical character
					if(isalpha(m))
					{
						//perform the modular calculations now
						c = m + (k % 26);	// shift plaintext character by k % 26	
						//consider if character in the input file is upper or lowercase
						if (isupper(m))
						{
							if (c > 90)	// if encrypted value exceeds ASCII 'Z', wrap around
							{
								c -= 26;
							}
							else if (c < 65) // if encrypted value is less than ASCII 'A', wrap around
							{
								c += 26;
							}
						}
						else
						{
							//if it is lowercase
							if (islower(m))
							{
								if (c > 122)	// if encrypted value exceeds ASCII 'z', wrap around
								{
									c -= 26;
								}
								else if (c < 97)
								{
									c += 26;
								}
							}
						}
					}
				}
				/*
        			at the end, we have to type cast the c to a character so we can use put
        			to put it into the output file
        		*/
				encryptedFileStream.put((char)c);
			}
		}
	}
	return;
}

/* 
============================================================================
Function    : decrypt
Parameters  : the encrypted input file, plaintext output file, and key file
streams.
Return      : nothing as it is a void function.
Description : This function decrypts an encrypted file using the created
key file from the encryption process above.
 ============================================================================
*/
void decrypt(ifstream& encryptedFileStream, ofstream& plaintextStream, ifstream& keyFileStream)
{
	//declaring the variables
	//c is each encrypted character in the input, k is each number from the key file, m is the original character for the output file
	int m;
	int k;
	char c;
	/*
	While we get each character in the input file (which is the encrypted file)
	we do the following
	*/
	while(encryptedFileStream.get(c))
	{
		//keep all original punctuation as is
		if (ispunct(c))
		{
			plaintextStream.put(c);
		}
		else
		{
			//we get the k value from the key file
			keyFileStream >> k;
			//if it is a digit, then do the following mod operation
			if (isdigit(c))
			{
				// shift by a maximum of 10 digits (since it is 0 - 9)
				m = c - (k % 10);
				// if encrypted value exceeds ASCII '9', wrap around
				if (m > 57)
				{
					m -= 10;
				}
				// if encryped value is less than ASCII '0' add 10 so that its in range of 0..9 ASCII.
				else if (m < 48)
				{
					m += 10;
				}
			}
			else
			{	
				//if it is a alphabetical character
				if(isalpha(c))
				{
					//perform the mod operation
					m  = c - (k %26);
					//conisider if the input file has uppercase letters
					//when original exceeds ASCII value for Z, wrap around
        			if (isupper(c))
        			{
                		if (m > 90)
                		{
                    		m -= 26;
                		}
                		//if below ASCII value for A, add 26
                		else if (m < 65)
                		{
                    		m += 26;
                		}
        			}
        			else
        			{
        				//or lowercase
                		if (islower(c))
                		{
                			//when original exceeds ASCII value for z, wrap around
                    		if (m > 122)
                    		{
                        		m -= 26;
                    		}
                    		//if below ASCII value of a, add 26
                    		else if (m < 97)
                    		{
                        		m += 26;
                    		}
                		}
        			}
        		}
			}
			//type cast to a char and put it in the output file each time
			plaintextStream.put((char)m);
		}
	}
	return;
}