// ConsoleApplication3.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver = false;
const int width = 20;
const int height = 20;
int x, y, fx, fy, score;
int tailX[100], tailY[100];
int nTail = 3;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
	gameOver = false;
	dir = UP;
	x = width / 2;
	y = height / 2;
	fx = rand() % width;
	fy = rand() % height;
	score = 0;
}

void Draw() {
	system("cls"); //screen will clear
	for (int i = 0; i < width + 2; i++)
	{
		cout<<"#";
	}

	cout<<endl;

	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "8";
			else if (i == fy && j == fx)
				cout << "@";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if(!print)
				cout << " ";
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i<width + 2; i++)
		cout << "#";

	cout << endl << endl;
	cout << "score:" << score << endl;
	cout << "Hit 'Space' to exit";
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a': dir = LEFT;
			break;
		case 'd': dir = RIGHT;
			break;
		case 'w': dir = UP;
			break;
		case 's': dir = DOWN;
			break;
		case ' ': gameOver = true;
			break;
		default: break;
		}

	}

}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT: x--;
		break;
	case RIGHT: x++;
		break;
	case UP: y--;
		break;
	case DOWN: y++;
		break;
	}

	if (y < 0)
		y = height-1;
	if (y > height)
		y = 0;
	if (x < 0)
		x = width-1;
	if (x >= width)
		x = 0;
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}

	if (x == fx && y == fy)
	{
		score += 10;
		fx = rand() % width;
		fy = rand() % height;
		nTail++;
	}

}

void main()
{
	Setup();

	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(50);
	}

	
}

