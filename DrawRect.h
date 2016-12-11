//DrawRect.h
//Caner Korkmaz
#pragma once
 
//The libs
#include <iostream>
#include <Windows.h>
using namespace std;
/*
 *This method sets the cursor position.
 *Usage:
 *setxy(1,1);
 */
BOOL setxy(int x, int y)
{
	COORD c = {x,y};
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
 
/*
 *This method draws the rectangle.
 *Usage:
 *DrawRect(1,1,10,10);
 *or
 *DrawRect(1,1,10,10,20,5);
 */
void DrawRect(int x, int y, int width, int height, int curPosX=0, int curPosY=0)
{
	setxy(x,y);cout << char(201);
	for(int i = 1; i < width; i++)cout << char(205);
	cout << char(187);
	setxy(x,height + y);cout << char(200);
	for(int i = 1; i < width; i++)cout << char(205);
	cout << char(188);
	for(int i = y + 1; i < height + y; i++)
	{
		setxy(x,i);cout << char(186);
		setxy(x + width,i);cout << char(186);
	}
	setxy(curPosX,curPosY);
}


