//Credit: Saul Merino and John Kim
#pragma once
#include <iomanip>
#include <cmath>	//for absolute value calculations
#include <cctype>	//for the toupper validation


void baseConverterMenu();			 //Part 2 Main menu
char baseConverterMenuOption();		 //Introduction UI
int newIntInput();					 //Option A in UI
void baseConversionSingle(int num1); //Option B in UI
void baseConversionAll(int num1);	 //Option C in UI

void menu();
void chooseOption();

//This is the Main menu for Part 2. It will return back to the Assignment 1 once it is done.
// Precondition: None
// Postcondition: returns the called function, depending on what case input was selected.
void baseConverterMenu()
{
	int userNum1; //This is number that is used in all the calculations. 
	bool numInput = false; // this will prevent the program from runnning without an intergr placed in 
	do
	{
		switch (baseConverterMenuOption()) //this will call the main menu, the char output then triggers the switch
		{
		case '0': system("pause");
			system("cls");
			menu();
			chooseOption();
			break;										//This is to exit this program, and return to the main menu
		case 'A':  userNum1 = newIntInput(); numInput = true; break;	//This is A. Enter an Integer Number (Base 10) once this is triggered once, then it will allow user to access other two options
		case 'B': if (!numInput) { cout << "ERROR - No integer has been entered."; break; } baseConversionSingle(userNum1); break;  //this is Option B. Specify the converting Base. It cannot run without running option A at least once.
		case 'C': if (!numInput) { cout << "ERROR - No integer has been entered."; break; } baseConversionAll(userNum1); break;		//this is Option C. Display All Converted Base. It cannot run without running option A at least once.
		default: cout << "ERROR - Invalid option. Please Enter A, B, C, or 0."; break;												//if anything else, then it will look again
		}
		cout << endl;
		system("pause");
	} while (true);
}

//This is the intro text for the Main Menu for Part 2
// Precondition: None
// Postcondition: Returns a (char), or an uppercase of the option (char)
char baseConverterMenuOption()
{
	system("cls");
	cout << "CMPR131 Part 2. Base Converter" << endl;
	cout << "2: Base Converter" << endl;
	cout << string(100, char(205)) << endl;

	cout << "A. Enter an Integer Number (Base 10)" << endl;
	cout << "B. Specify the converting Base" << endl;
	cout << "C. Display All Converted Bases" << endl;
	cout << string(100, char(196)) << endl;

	cout << "0. Return" << endl;
	cout << string(100, char(205)) << endl;
	char option = toupper(inputChar("Option: "));
	return option;
}

//This is where to get the Number for the calculations 
// Precondition: User picks Option "1"
// Postcondition: Returns a validated Integer 
int newIntInput()
{
	return inputInteger("Enter An Integer in Base 10: ");
}

//This is where the user can choose what base to calculate their number. It is limited in range from binary [2] all the way to hexatrigesimal [36]
// Precondition: Valid Integer
// Postcondition: Returns the Integer and its converted Base
void baseConversionSingle(int num1)
{

	int base = inputInteger("Enter the base to convert your number to (2..36): ", 2, 36);	//this is the intro and asks for what base to calculate in
	string binaryNumber = "";
	char hex;					//this is to hold an integer-turned to char for string input.
	int tempNum = num1;

	do
	{
		int remainder = abs(num1) % base;

		num1 /= base;

		if (remainder > 9)																	//this is where numeric values that exteed our decimal system get translated to the appropiate base.
		{
			hex = remainder + 55;															//the 'exteeded' value is converted to the ascii binary code. For example 
			string hexNum(1, hex);															// the array is advanced
			binaryNumber.insert(0, hexNum);													// the now converted value is then added to the string
		}
		else //if the numeric value was between 0-9, it directly puts it in.
		{
			binaryNumber.insert(0, to_string(remainder));
		}

	} while (abs(num1) >= base);
	if (abs(num1) > 9)
	{
		hex = abs(num1) + 55;
		string hexNum(1, hex);
		binaryNumber.insert(0, hexNum);
		if (tempNum < 0)//if the integer inputed was negative, then the negative sign would be added at the end
		{
			binaryNumber.insert(0, "-");
		}
	}
	else if (num1 != 0) // this is if the number is too small and can fit in the base.
	{
		binaryNumber.insert(0, to_string(num1));
	}
	else if (tempNum < 0 && num1 == 0)//if the integer inputed was negative, then the negative sign would be added at the end
	{
		binaryNumber.insert(0, "-");
	}

	cout << tempNum << " (Base of 10) = " << binaryNumber << " (Base of " << base << ")" << endl;
}

//This is where the program calculates their number in all the bases. It lists out all the base conversion from binary [2], to all the way to hexatrigesimal [36] in one list.
// Precondition: Integer (Positve or Negative)
// Postcondition: Outputs the Integer and the list of all converted Bases
void baseConversionAll(int num1)
{

	int tempNum = num1; //this is just to hold the  for a moment.
	char hex;
	cout << "Your number is " << num1 << "." << endl;
	string binaryNumber = "";
	for (int base = 2; base <= 36; base++)
	{
		num1 = tempNum;
		do
		{
			int remainder = abs(num1) % base;
			num1 /= base;
			if (remainder > 9)
			{
				hex = remainder + 55;
				string hexNum(1, hex);
				binaryNumber.insert(0, hexNum);
			}
			else
			{
				binaryNumber.insert(0, to_string(remainder));
			}
		} while (abs(num1) >= base);
		if (abs(num1) > 9)
		{
			hex = abs(num1) + 55;
			string hexNum(1, hex);
			binaryNumber.insert(0, hexNum);
			if (tempNum < 0)
			{
				binaryNumber.insert(0, "-");
			}
		}
		else if (num1 != 0)
		{
			binaryNumber.insert(0, to_string(num1));
		}
		else if (tempNum < 0 && num1 == 0)//if the integer inputed was negative, then the negative sign would be added at the end
		{
			binaryNumber.insert(0, "-");
		}

		cout << binaryNumber << " (Base of " << base << ")" << endl;
		binaryNumber.clear();
	}
}
