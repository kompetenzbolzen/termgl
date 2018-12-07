#pragma once

#include <string>
#include <math.h>
#include <iostream>

#ifdef __linux__
	#include <unistd.h>
	#include <term.h>
	#include <sys/ioctl.h>

	typedef int WORD;
#elif _WIN32
  #include <Windows.h>
#else
	#error "Platforn not supported"
#endif

//errors
#define _OK_ 0
#define _ERR_ 1
#define _ERR_COORDINATES_INVALID_ 2
#define _ERR_RENDER_BLOCKED_BY_CHILD_ 3
#define _ERR_SCREEN_TOO_SMALL_ 4

#define _COLLISION_ 255

//Colors
#ifdef _WIN32
	#define _COL_BLACK 0x00
	#define _COL_BLUE 0x01
	#define _COL_GREEN 0x02
	#define _COL_YELLOW 0x0E
	#define _COL_RED 0x04
	#define _COL_WHITE 0x0F
	#define _COL_DARK_WHITE 0x07
	#define _COL_INTENSITY 0x08
	#define _COL_DEFAULT 0xFF
#elif __linux__
	#define _COL_BLACK 30
	#define _COL_BLUE 34
	#define _COL_GREEN 32
	#define _COL_YELLOW 33
	#define _COL_RED 31
	#define _COL_WHITE 37
	#define _COL_DEFAULT 0

	//Linux Specific
	#define _COL_BOLD 1
	#define _COL_BOLD_OFF 21
	#define _COL_UNDERLINE 4
	#define _COL_UNDERLINE_OFF 24
	#define _COL_INVERSE 7
	#define _COL_INVERSE_OFF 27
#endif
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
	//Resizes console window for Windows
	//Sets Size to Console Window Size for Linux. Writes Error for _sx or _sy smaller than Screen. Get by getLastError()

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

	int getLastError();
	//Returns last Error that was not returnable


protected:
	cRender(); //Empty Constructor for being inheritable

	bool bBlockRender; //Used by children to block render function

	char **cScreen; //Pixel Map
	WORD **wColor;  //Color Map

	char cBackound; //Default backround
	WORD wBackColor;
	int sizeX, sizeY;

#ifdef _WIN32
	HANDLE hstdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
#endif

	WORD wDefColor; //Default Color

	int iLastError;

private:
#ifdef _WIN32
	int SetConsoleWindowSize(int x, int y);
	//Slightly adapted from: http://www.cplusplus.com/forum/windows/121444/
#endif
	void gotoxy( int x, int y );
};
