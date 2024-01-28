// SnakeGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
bool tailHit;
bool gameOver;
int tailX[100];
int tailY[100];
int prevTailX[100];
int prevTailY[100];
void Setup()
{
	gameOver = false;
	tailHit = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "X";
			else
			{
				bool printed = false;
				for (int k = 0; k < score; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << 'o';
						printed = true;
					}
				}
				if (!printed)
					cout << " ";
			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;

	}
	
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;

}

void Input()
{
		if(GetAsyncKeyState('W') & 0x8000)
		{
			dir = UP;
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			dir = LEFT;
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			dir = DOWN;
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			dir = RIGHT;
		}
}

void Logic()
{
	int prevTailX = tailX[0];
	int prevTailY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < score; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevTailX;
		tailY[i] = prevTailY;
		prevTailX = prev2X;
		prevTailY = prev2Y;
	}

	
	if (x < 0 || x > width || y < 0 || y > height )
		gameOver = true;
	if (x == fruitX && y == fruitY)
	{
		score++;
		fruitX = rand() % width;
		fruitY = rand() % height;
		for (int k = 0; k < score; k++)
		{
			if (fruitX == tailX[k] && fruitY == tailY[k])
			{
				fruitX = rand() % width;
				fruitY = rand() % height;
			}
		}
	}
	
	switch (dir)
	{
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
	}
	for (int k = 0; k < score; k++)
	{
		if (x == tailX[k] && y == tailY[k])
		{
			gameOver = true;
		}
	}
	
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(50);
	}
    return 0;
}

