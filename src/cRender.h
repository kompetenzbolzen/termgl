#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <termios.h>

#ifdef __linux__
	#include <unistd.h>
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
/** cRender manages a framebuffer the size of the console (window) it is run in.
*
* puts console in alternate screen mode
*/
class cRender
{
public:
	/** Constructor
	* sets cBackround[][] to _backround & wColor[][] to _color
	* Resizes console window for Windows
	* Sets Size to Console Window Size for Linux. Writes Error for _sx or _sy smaller than Screen. Get by getLastError()
	*/
	cRender(char _backound, WORD _color, int _sx, int _sy);

	virtual ~cRender();

	/** Draws _c @ _pos in screenbuffer
	* Returns _COLLOSION_ if _pos is already set to !cBackround && _overrideCollision isnt set
	*/
	int drawPoint(char _c, sPos _pos, bool _overrideCollision, WORD _color);

	/** draws Line from _pos1 to _pos2 in screenbuffer
	* x Value of pos1 MUSTNT exceed the x value of pos2!
	*/
	int drawLine(char _c, sPos _pos1, sPos _pos2, bool _overrideCollision, WORD _color);

	/** Draws Text _s @ _pos in screenbuffer
	* First char is @ _pos
	*/
	int drawText(string _s, sPos _pos, WORD _color);

	/** writes rectangle to screenbuffer
	* x Value of pos1 MUSTNT exceed the x value of pos2!
	*/
	int drawRectangle(char _border, char _fill, sPos _pos1, sPos _pos2, WORD _borderColor, WORD _fillColor);

	/** Dumps screenbuffer to stdout
	* prints changed pixels
	*/
	int render(void);

	/** clears cScreen + wColor
	* for _forceReRender == true, the bChanged[][] is set to true to force Re-Render of whole Screen
	* clear(void) calls clear(_forceReRender = false)
	*/
	int clear();
	int clear(bool _forceReRender);

	/** Returns last Error that was not returnable
	*/
	int getLastError();

	/** Returns size of screenbuffer
	*/
	sPos getSize();


protected:
	/** Empty Constructor for being inheritable
	*/
	cRender();

	/** Sets screenbuffer size
	* Uses sizeX, sizeY to determine previous screenbuffer size. Do NOT change sizeX, sizeY manually!!
	*/
	void setBufferSize(sPos _size);

	bool bBlockRender;
	//* Used by children to block render function

	char **cScreen;
	//* Pixel Map
	WORD **wColor;
	//* Color Map
	bool **bChanged;
	//* Pixel Change Map

	char cBackound;
	//* Default backround
	WORD wBackColor;
	//* Default backround color
	unsigned int sizeX, sizeY;
	//* Size of screen array

#ifdef _WIN32
	HANDLE hstdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
#endif

	WORD wDefColor;
	//* Default Color

	int iLastError;

private:
#ifdef _WIN32
	int SetConsoleWindowSize(int x, int y);
	//Slightly adapted from: http://www.cplusplus.com/forum/windows/121444/

	void gotoxy( int x, int y );
#endif

	void forceReRender();

	void setConsoleEcho(bool _enable);
#ifdef __linux__
	sPos getConsoleWindowSize();

	void setConsoleCursor(bool _enable);

	void setAlternateBufferScreen(bool _enable);
#endif
};
