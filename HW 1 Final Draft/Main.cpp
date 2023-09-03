//Joe Bryant
//8/22/23
//CPMR 131 - Professor Q

//Credit/Contribution
/*
"ASCII Text To ASCII Numbers" : Joe Bryant and Erik Santana

"Base Converter" : John Kim and Saul Merino

"Descriptive Statistics" : Otoniel Torres Bernal and Oscar Gallardo
*/

/*Description:
This is a program that displays a menu that lets you choose from 3 options.
These options are "ASCII Text To ASCII Numbers", "Base Converter", and "Descriptive Statistics".
"ASCII Text To ASCII Numbers" converts ASCII text to ASCII numbers and stores it in a file, "Base Converter" converts a chosen base 10 number to a different bases from 2-36,
and "Descriptive Statistics" reads numbers from a file and gives statistics about this numbers.
*/



#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <fstream>
#include <cmath>
#include "input.h"
#include "baseConverter.h"
#include "descriptiveStatistics.h"
#include "asciiConversion.h"

void menu();
void chooseOption();

int main()
{
	menu();
	chooseOption();
}

//precondition: None
//postcondition: displays main menu
void menu() //main menu for program
{
	cout << "CMPR131 - Chapter 1 Software Development by Joe B\n";
	cout <<
		"==========================================================\n";
	cout << "\t1> ASCII Text To ASCII Numbers\n";
	cout << "\t2> Base Converter\n";
	cout << "\t3> Descriptive Statistics\n";
	cout << "----------------------------------------------------------\n";
	cout << "\t0> exit\n";
	cout <<
		"==========================================================\n";
}
//precondition: None
//postcondition: chooses a menu option based on user input.
void chooseOption() //chooses option for main menu
{
	do
	{
		int option = inputInteger("\tOption: ");

		switch (option)
		{
		case 0: exit(0);
			break;
		case 1: asciiMenu();
			break;
		case 2: baseConverterMenu();
			break;
		case 3: system("cls");
			descriptiveStatistics();
			break;
		default: cout << "ERROR-3A: Invalid input. Must be from 0..3.\n";
		}
	} while (true);
}