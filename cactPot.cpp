/*

	cactPot.cpp

	Cactus Pot (CactPot) is a lottery game where the player wins Gold Point Rewards.
	Menu driven interface program in which the user will be able to:
		1- See rules of the game
		2- Play the game
		3- See the high score
		4- Quit

*/

// Header Files
#include <iostream>
#include <string>
#include "cactPot.h"
using namespace std;

// Functions
// Rules
void displayRules() 
{
	cout << "\nThe Rules:" << endl;
	cout << "\nEvery lottery ticket has nine cells \u002d a 3x3 matrix, "
		<< "and eight lines \u002d vertical, horizontal, and diagonal. Each "
		<< "cell hides a random number from one to nine \u002d no repeats. "
		<< "When a game starts, eight of these nine numbers are hidden." << endl;
	cout << "\t1. Select Three Numbers: To begin, you must select "
		<< "three cells from the eight with hidden values on the ticket, "
		<< "and uncover their numbers." << endl;
	cout << "\t2. Select a Line: Next, the you must select one of eight "
		<< "lines \u002d vertical, horizontal, or diagonal." << endl;
	cout << "\t3. Receive a Reward: Once you have selected a line, all its "
		<< "numbers are uncovered and you are awarded Gold Point Rewards based on "
		<< "the sum of the line chosen, using the Payout table shown.\n" << endl;
	cout << "You are able to play as many times as you wish.\n"
		<< "Have Fun!\n" << endl;
}

// Game Start
void playGame(Matrix currentMatrix) 
{
	currentMatrix.setMatrix();
	currentMatrix.getCMatrix();
	currentMatrix.handleGamePlay();
}

// Display Menu
void displayMenu() 
{
	int userSelection = 0;
	Matrix currentMatrix;

	//Menu with switch cases
	do 
	{
		// Intro
		cout << "Main Menu:" << endl;
		cout << "\t1) See Rules\n\t2) Play Game\n\t3) See Highest Score\n\t4) Quit" << endl;
		cout << "Your choice: ";
		cin >> userSelection;

		switch (userSelection) 
		{
		case 1:				// Display the rules
			displayRules();
			break;
		case 2:				// Play the game
			playGame(currentMatrix);
			break;
		case 3:				// Display high score
			currentMatrix.displayHighScore();
			break;
		case 4:				// QUIT
			cout << "\nGood Bye ..." << endl;
			break;
		default:			// Validation
			cout << "\nError ... Invalid choice. Try again." << endl;
		}
	} while (userSelection != 4);
}

// Main
int main() 
{
	displayMenu();
	return 0;
}
