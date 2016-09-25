#pragma once

#include <string>
#include <Windows.h>
#include <math.h>
#include <iostream>


//errors
#define _OK_ 0
#define _ERR_ 1
#define _ERR_COORDINATES_INVALID_ 2
#define _ERR_RENDER_BLOCKED_BY_CHILD_ 3

#define _COLLISION_ 255

//Colors
#define _COL_BLACK 0x00
#define _COL_BLUE 0x01
#define _COL_GREEN 0x02
#define _COL_YELLOW 0x0E
#define _COL_RED 0x04
#define _COL_WHITE 0x0F
#define _COL_DARK_WHITE 0x07
#define _COL_INTENSITY 0x08
#define _COL_DEFAULT 0xFF

using namespace std;

struct sPos
{
	int x;
	int y;
};

class cRender
{
public:
	cRender(char _backound, WORD _color, int _sx, int _sy);
	//Constructor
	//sets cBackround[][] to _backround & wColor[][] to _color
	//Resizes console window

	~cRender();
	//frees allocated memory

	int drawPoint(char _c, sPos _pos, bool _overrideCollision, WORD _color);
	//Draws _c @ _pos
	//Returns _COLLOSION_ if _pos is already set to !cBackround && _overrideCollision isnt set

	int drawLine(char _c, sPos _pos1, sPos _pos2, bool _overrideCollision, WORD _color);
	//x Value of pos1 MUSTNT exceed the x value of pos2!

	int drawText(string _s, sPos _pos, WORD _color);
	//Draws Text _s @ _pos
	//First char is @ _pos

	int drawRectangle(char _border, char _fill, sPos _pos1, sPos _pos2, WORD _borderColor, WORD _fillColor);
	//x Value of pos1 MUSTNT exceed the x value of pos2!

	int render(void);
	//Prints cScreen

	int clear(void);
	//clears cScreen + wColor
	

protected:
	cRender(); //Empty Constructor for being inheritable
	
	bool bBlockRender; //Used by children to block render function

	char **cScreen; //Pixel Map
	WORD **wColor;  //Color Map 

	char cBackound; //Default backround
	WORD wBackColor;
	int sizeX, sizeY;

	HANDLE hstdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	WORD wDefColor; //Default Color
private:
	int SetConsoleWindowSize(int x, int y);
	//Slightly adapted from: http://www.cplusplus.com/forum/windows/121444/
};