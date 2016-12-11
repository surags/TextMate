#pragma once

#include<windows.h>
#include<iostream>

HANDLE hConsole;

void BColor(int x)
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, x);
	//std::cout<<endl;
	
		
}

void WindowSize(int px,int py,int l,int b)
{
	HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, px, py, l, b, TRUE); // 800 width, 600 height
}

void Line()
{
	for(int i=0;i<80;i++)
	{
		cout<<"=";
	}
}




 

void Font(int x,int y)
{ 
 // Obtain the Console handle
 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Obtain the Console handle
 
 PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX() ;
 
 // set the size of the CONSOLE_FONT_INFOEX
 lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
 
 // get the current value
 GetCurrentConsoleFontEx(hConsole,0,lpConsoleCurrentFontEx);
 
 // set size to be 8x18, the default size is 8x16
 lpConsoleCurrentFontEx->dwFontSize.X = x;
 lpConsoleCurrentFontEx->dwFontSize.Y = y;
 
 // submit the settings
 SetCurrentConsoleFontEx(hConsole,0,lpConsoleCurrentFontEx);
 

 
 
 //cin.get(); // wait return 0;
}
