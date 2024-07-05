/*

	cactPot.h

	Cactus Pot (CactPot) is a lottery game where the player wins Gold Point Rewards.
	
	Specification file for the class Matrix.
*/

#pragma once
#include <random>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/*
	Matrix
*/

// Matrix class
class Matrix 
{
	//Members
private:
	int matrix[3][3];		// 3x3 Matrix
	int revealed[3][3];
	int highScore = 0;		// High score tracker
	// Matrix Display
	string cells[3][3] = {
	{"A1", "B1", "C1"},
	{"A2", "B2", "C2"},
	{"A3", "B3", "C3"}
	};
public:
	// Accessors
	int getMatrix(int x, int y) 
	{
		return matrix[x][y];
	}
	// Mutator
	void setMatrix() {
		// Random engine 
		srand(time(0));
		int r = rand() % 362880;
		vector<string> lines;
		string randomLine;
		ifstream inFile;
		int total_lines = 0;

		// Open file
		inFile.open("cactpotTickets.txt");

		// Validation
		if (!inFile)
		{
			cout << "Error ... Could not open " << "cactpotTickets.txt" << endl;
			return;
		}

		// Read from file a random line
		getline(inFile, randomLine);	
		while (getline(inFile, randomLine))
		{
			total_lines++;
			lines.push_back(randomLine);
		}

		int random_number = rand() % total_lines;
		string chosenRandomLine = lines[random_number];

		int numberIndex = 0;

		for (int i = 0; i < chosenRandomLine.length(); i++) {
			string currentNum = chosenRandomLine.substr(i, 1);
			if (currentNum != " ") {
				matrix[numberIndex / 3][numberIndex % 3] = stoi(currentNum);
				numberIndex++;
			}
		}
	}

	// used for creating the original matrix
	void getCMatrix() 
	{
		srand(time(0));
		int r = rand() % 3;
		int a = rand() % 3;

		// Build original matrix
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				cout << " |";
				if (i == r && j == a)
				{
					cout << " " << matrix[i][j] << "  | ";
					revealed[i][j] = true;
				}
				else {
					cout << "*" << cells[i][j] << "*| ";
					revealed[i][j] = false;
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	// Plays the game
	void handleGamePlay() 
	{
		bool isDone = false;		// Keep going till end of game

		for (int i = 0; i < 3; i++) 
		{
			do 
			{
				// Variables
				isDone = false;
				string userCellReveal;		// User choice

				// Ask user for column and row
				cout << "Please enter the col and row number of the cell you want to reveal (ex. A1): ";
				cin >> userCellReveal;

				for (int k = 0; k < 3; k++) 
				{
					for (int j = 0; j < 3; j++) 
					{
						//cells and revealed are parallel
						if (userCellReveal == cells[k][j]) 
						{
							if (!revealed[k][j]) 
							{
								revealed[k][j] = true;
								isDone = true;
								displayRevealedMatrix();
								cout << endl;
							}
							//if the user has already guessed this one...
							else {
								cout << "Error ... That cell is already revealed. Please choose a different one." << endl;
								isDone = false;
							}
							break;
						}
					}
				}
				if (!isDone)	// Validation
				{
					cout << "Error ... Invalid cell. Please try again." << endl;
				}
			} while (!isDone);
		}
		lineSelect();
	}

	//displays the full matrix after user runs out of guesses
	void displayRevealedMatrix() 
	{
		for (int i = 0; i < 3; i++) 
		{
			for (int k = 0; k < 3; k++) 
			{
				cout << " |";

				if (revealed[i][k]) 
				{
					cout << " " << matrix[i][k] << "  | ";
				}
				else {
					cout << "*" << cells[i][k] << "*| ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	// Selection of Line
	void lineSelect() 
	{
		// Variables
		int choice = 0;

		//ask user for their selection of line
		do 
		{
			cout << "Please select from one of the following lines, (1-8):\n"
				<< "Line 1: Row 1 \nLine 2: Row 2\nLine 3: Row 3\n"
				<< "Line 4: A1, B2, C3\n"
				<< "Line 5: Col A \nLine 6: Col B\nLine 7: Col C\n"
				<< "Line 8: A3, B2, C3\n";
			cin >> choice;

			// Validation
			if (choice > 8 || choice < 1) 
			{
				cout << "Error ... Invalid line." << endl;
			}
		} while (choice > 8 || choice < 1);

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << " |";
				cout << " " << matrix[i][j] << "  | ";
			}
			cout << endl;
		}

		// Determine payout
		getPayout(choice);
	}

	//adds up the payout for the user's selected line
	void getPayout(int choice) 
	{
		int sum = 0;
		int score = 0;

		switch (choice) {
		case 1:
		case 2:
		case 3:
			sum += matrix[choice - 1][0];
			sum += matrix[choice - 1][1];
			sum += matrix[choice - 1][2];
			break;
		case 4:
			sum += matrix[0][0];
			sum += matrix[1][1];
			sum += matrix[2][2];
			break;
		case 5:
		case 6:
		case 7:
			sum += matrix[0][choice - 5];
			sum += matrix[1][choice - 5];
			sum += matrix[2][choice - 5];
			break;
		default:
			sum += matrix[0][2];
			sum += matrix[1][1];
			sum += matrix[2][0];
			break;
		}

		// Determine the Gold Point Rewords depending on the User's sum of points
		score = determineScore(sum);

		cout << "Payout: " << score << "\n" << endl;

		//only update high score if new score > old high score
		if (sum > highScore) 
		{
			cout << "You achieved the highest reward on the leaderboard!" << endl;
			highScore = score;
			updateHighScore();
		}
	}

	// Translates sum into Gold Point Rewards
	int determineScore(int sum)
	{
		int goldPointRewards = 0;

		if (sum == 6)
		{
			goldPointRewards = 10000;
		}
		if (sum == 7)
		{
			goldPointRewards = 36;
		}
		if (sum == 8)
		{
			goldPointRewards = 720;
		}
		if (sum == 9)
		{
			goldPointRewards = 360;
		}
		if (sum == 11)
		{
			goldPointRewards = 252;
		}
		if (sum == 12)
		{
			goldPointRewards = 108;
		}
		if (sum == 13)
		{
			goldPointRewards = 72;
		}
		if (sum == 14)
		{
			goldPointRewards = 54;
		}
		if (sum == 15)
		{
			goldPointRewards = 180;
		}
		if (sum == 16)
		{
			goldPointRewards = 72;
		}
		if (sum == 17)
		{
			goldPointRewards = 180;
		}
		if (sum == 18)
		{
			goldPointRewards = 119;
		}
		if (sum == 19)
		{
			goldPointRewards = 36;
		}
		if (sum == 21)
		{
			goldPointRewards = 1080;
		}
		if (sum == 22)
		{
			goldPointRewards = 144;
		}
		if (sum == 23)
		{
			goldPointRewards = 1800;
		}
		if (sum == 24)
		{
			goldPointRewards = 3600;
		}
		return goldPointRewards;
	}

	// Updates the high score on the .txt file
	void updateHighScore() 
	{
		// Variables
		string userName;

		// Ask user for Name to put in file
		cout << "Please enter your name: ";
		cin >> userName;

		// Write high score into .txt
		ofstream scoreFile;
		scoreFile.open("highestRewards.txt");
		scoreFile << "Current Highscore: " << highScore << ", by " << userName;
	}

	// Displays the high score from the .txt file
	void displayHighScore() 
	{
		// Variables
		ifstream infile;
		string textLine;

		infile.open("highestRewards.txt");
		while (getline(infile, textLine)) 
		{
			cout << textLine << endl;
		}
		if (textLine.empty())				// If there is no High Score
		{
			cout << endl << "There Is Currently No High Score" << endl << endl;
		}
		infile.close();
	}
};
