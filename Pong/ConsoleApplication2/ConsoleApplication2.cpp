// SnakeGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
using namespace std;

//SETS THE SIZE OF THE ARENA
const int width = 60;
const int height = 20;

//GLOBAL VARIABLES
int p1x, p1y, p1y2, p1y3, p2x, p2y, p2y2, p2y3, ballX, ballY, score, score2;
enum bDirection { STOP = 0, LEFTD, RIGHTD, LEFTU, RIGHTU };
bDirection dir;
enum uDirection { STOP2 = 0, UP, DOWN };
uDirection p1;
uDirection p2;
int gameType;
bool gameOver;


//SETS UP AN INDIVIDUAL GAME
//
void Setup()
{
	//Resets scores from previous games
	score = 0;
	score2 = 0;
	///Generates a new random numbeer seed
	srand(time(NULL)); 
	gameOver = false; //Resets the game
	dir = LEFTD; //Sets initial ball direction

	//Original player 1 location
	p1x = width-2;
	p1y = height/2;
	p1y2 = p1y - 1;
	p1y3 = p1y + 1;

	//Original player 2 location
	p2x = 2;
	p2y = height / 2;
	p2y2 = p1y - 1;
	p2y3 = p1y + 1;

	//Original ball location
	ballX = p1x - 1;
	ballY = p1y;
}


//WILL DRAW EVENTS TO CONSOLE
//
void Draw()
{
	//Clears screen
	system("cls");

	// Writes Upper Border
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	//Draws inner box
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// Draws Border on left side
			if (j == 0)
				cout << "#";
			// Will draw a player 1 piece if it matches the location that is currently being drawn
			if ((i == p1y || i == p1y2 || i == p1y3) && j == p1x)
				cout << "0";
			// Wil draw a player 2 piece if it matches the location that is currently being drawn
			else if ((i == p2y || i == p2y2 || i == p2y3) && j == p2x)
				cout << "0";
			// Will draw a ball if it matches the location that is currently being drawn
			else if (i == ballY && j == ballX)
			{
				cout << "X";
			}	
			// Draws empty spaces
			else
			{
					cout << " ";
			}

			// Draws border on right side
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;

	}

	// Draws bottom border
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	// Prints player scores
	cout << "Player 1 Score: " << score << endl;
	cout << "Player 2 Score: " << score2 << endl;

}

// PROCESSES INPUTS AND DETERMINES NEW DIRECTIONS
//
void Input()
{
	//Determines if the game is using AI or 2 Player Mode
	if (gameType == 2) // 2 - player mode
	{
		// W key will set move state to up
		if (GetAsyncKeyState('W') & 0x8000)
		{
			// Will not move if it is at the top
			if (p2y2 < 1)
				p2 = STOP2;
			else
				p2 = UP;
		}
		// S key will set move state to down
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			// Will not move if it is at the bottom
			if (p2y3 > height - 2)
				p2 = STOP2;
			else
				p2 = DOWN;
		}
		// If no key is pressed, don't move
		else
			p2 = STOP2;
	}

	else if(gameType == 1) // AI Mode
	{
		// The AI Difficulty setting
		// Uses a random number to determine the chance on it not moving a particular iteration. 
		if (rand()% 100 < 80) // Change this number to change the chance of it sitting
		{
			//Determines a spot between the end of the board and halfway to begin watching the ball again
			if (ballX < width - (rand() % (width/2)))
				//If the ball is lower, set the move state to down
				if (ballY > p2y2)
					// Will not move if it is at the bottom
					if (p2y3 > height - 2)
						p2 = STOP2;
					else
						p2 = DOWN;
				// If the ball is higher, move up
				else if (ballY < p2y3)
				{
					// Will not move if it is at the top
					if (p2y2 < 1)
						p2 = STOP2;
					else
						p2 = UP;
				}
				else {}

			// If it is near the center, move up and down onle a little
			else if (ballX > width / 2)
				if (p2y > height / 2)
					p2 = UP;
				else if (p2y < height / 2)
					p2 = DOWN;
				else {}
		}
		
	}
		

	// Player 1 Controls
	// Sets the move state to up if O is pressed
	if (GetAsyncKeyState('O') & 0x8000)
		// Will not move if it is at the top
		if (p1y2 < 1)
			p1 = STOP2;
		else
			p1 = UP;
	// Set the move state to down if L is pressed
	else if (GetAsyncKeyState('L') & 0x8000)
		// Will not move if it is at the bottom
		if (p1y3 > height - 2)
			p1 = STOP2;
		else
			p1 = DOWN;
	// If no button is pressed, do not move
	else
		p1 = STOP2;
}

// PROCESSES INPUTS AND DETERMINES CHANGES FOR THE NEXT ITERATION
//
void Logic()
{
	// If the ball touches player 1's paddle
	if (p1x == ballX && (p1y == ballY || p1y2 == ballY || p1y3 == ballY))
	{
		//Increment player 1 score
		score++;
		//Change direction of the ball
		if (dir == RIGHTU)
			dir = LEFTU;
		else if (dir == RIGHTD)
			dir = LEFTD;
		else
		{}

	}
	// If the ball touches player 2's paddle
	else if(p2x == ballX && (p2y == ballY || p2y2 == ballY || p2y3 == ballY))
	{
		//Increment player 2 score
		score2++;
		//Change direction of the ball
		if (dir == LEFTU)
			dir = RIGHTU;
		else if (dir == LEFTD)
			dir = RIGHTD;
		else
		{}
	}

	//Determines player 1 movements based on move state
	switch (p1)
	{
	case STOP2:
		break;
	// Moves all paddle pieces up 1
	case UP:
		p1y--;
		p1y2--;
		p1y3--;
		break;
	// Moves all paddle pieces down 1
	case DOWN:
		p1y++;
		p1y2++;
		p1y3++;
		break;

	}

	//Determines player 2 movements based on move state
	switch (p2)
	{
	case STOP2:
		break;
	// Moves all paddle pieces up 1
	case UP:
		p2y--;
		p2y2--;
		p2y3--;
		break;
	// Moves all paddle pieces down 1
	case DOWN:
		p2y++;
		p2y2++;
		p2y3++;
		break;

	}

	// Determines movement of the ball based on move state
	switch (dir)
	{
	// Ball will move left and up
	case LEFTU:
		ballX--;
		ballY--;
		break;
	// Ball will move right and up
	case RIGHTU:
		ballX++;
		ballY--;
		break;
	// Ball will move left and down
	case LEFTD:
		ballX--;
		ballY++;
		break;
	// Ball will move right and down
	case RIGHTD:
		ballX++;
		ballY++;
		break;
	}

	// If the ball hits a border, change directions
	if (ballX < 1 || ballX > width || ballY < 1 || ballY > height-2)
	{
		
		if (dir == LEFTU)
			dir = LEFTD;
		else if (dir == RIGHTU)
			dir = RIGHTD;
		else if (dir == LEFTD)
			dir = LEFTU;
		else if (dir == RIGHTD)
			dir = RIGHTU;
		else
		{}
		
		
		// If the ball hits the sides, end the game
		if (ballX > width || ballX < 0)
			gameOver = true;
	}
}

int main()
{
	//Will loop infintely, allowing multiple games to be played
	bool gameloop = true;
		while (gameloop = true)
		{
			//New Game Screen
			system("cls");
			cout << "Left Player Controls (2 Player): W + S" << endl
				 << "Right Player Controls          : O + L" << endl;
			cout << "Enter 1 for AI, or 2 for 2-Player: ";
			cin >> gameType;
			Setup();

			//Game loop
			while (!gameOver)
			{
				Draw();
				Input();
				Logic();
				Sleep(30);
			}

			//Game Over Screen
			system("cls");
			cout << "GAME OVER! " << endl;
			cout << "Your Score: " << score << endl;
			system("pause");
	}
	
	return 0;
}

