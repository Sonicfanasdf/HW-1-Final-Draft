//Credit: Joe Bryant and Erik Santana

#pragma once
#include <cstdlib>
#include <cctype>
#include <cmath>
#include "baseConverter.h"





void asciiMenu();
void writeFile(string textString, string& fileName);
void readFile(string fileText, string fileName);
void menu();
void chooseOption();

//Precondition: None
//Postcondition: Displays the asciiMenu and gives user the option to progress to other menus
void asciiMenu() //ascii conversion menu
{
	char option;

	string textString = "";
	string fileName = "";
	string fileText = "";

	system("cls");

	do
	{
		cout << "1> ASCII Text To ASCII Numbers\n";
		cout <<
			"==========================================================\n";
		cout << "\tA> Enter a text string\n";
		cout << "\tB> Convert the text string to ASCII numbers\n";
		cout << "\tC> Save the converted ASCII numbers into a binary file\n";
		cout << "\tD> Read the binary file\n";
		cout << "----------------------------------------------------------\n";
		cout << "\t0> return\n";
		cout <<
			"==========================================================\n";
		do
		{
			option = toupper(inputChar("\tOption: "));

			switch (option)
			{
			case 'A': fileText = "";
				textString = inputString("\n\tEnter a text line: \n\t", true);
				break;
			case 'B':
				if (textString == "")
				{
					cout << "\n\tERROR: empty input text.\n";

				}
				else
				{
					fileText = textString;

					cout << endl << "\tConverted to ASCII numbers: \n\t";

					for (int i = 0; i < textString.length(); i++)
					{
						cout << int(textString[i]) << " ";
					}

					cout << endl;
				}
				break;
			case 'C':
				if (fileText == "")
				{
					cout << "\n\tERROR: empty binary text.\n";
				}
				else
				{
					writeFile(textString, fileName);
				}
				break;
			case 'D': readFile(fileText, fileName);
				break;
			case '0': cout << endl;
				system("pause");
				system("cls");
				menu();
				chooseOption();
				break;
			default: cout << "ERROR-1A: Invalid input. Must be '0','A','B','C', or 'D'\n";



			}
		} while (option != '0' && option != 'A' && option != 'B' && option != 'C' && option != 'D');
		cout << endl;
	} while (true);
}
//PreCondition: textString must be a string and fileName must be a string
//postcondition : writes converted ASCII numbers to a file chosen by the user
void writeFile(string textString, string& fileName) //writes to a binary file
{
	ofstream binaryFile;


	cout << "\n\tEnter File Name: ";
	cin >> fileName;

	fileName = fileName + ".bin";

	binaryFile.open(fileName, ios::binary);

	if (!binaryFile)
	{
		cout << "File did not open\n";

	}

	for (int i = 0; i < textString.length(); i++)
	{
		binaryFile << int(textString[i]) << " ";
	}

	binaryFile.close();

	cout << endl << "\tFile, " << fileName << " , has been written and saved.\n";
}
//PreCondition: fileName must be an existing binary file
//PostCondition: reads out from the binary file
void readFile(string fileText, string fileName) //reads from the binary file
{
	string textLine;
	ifstream readFile;

	readFile.open(fileName, ios::binary);

	if (!readFile)
	{
		cout << "\tFile did not open\n";

	}
	else if (fileText == "")
	{
		cout << "\tFile did not open\n";
	}
	else
	{
		getline(readFile, textLine);

		readFile.close();

		cout << endl << "\tReading file, " << fileName << "...\n" << "\t" << textLine << endl;
	}
}