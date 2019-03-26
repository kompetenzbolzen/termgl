#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <termios.h>
#include <time.h> //clock()
#include <chrono>
#include <thread>

#ifdef __linux__
	#include <unistd.h>
	#include <sys/ioctl.h>
	#include <stdint.h>

	typedef uint32_t WORD;
#elif _WIN32
	#error "Not ported"
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

	//FG
	#define _COL_DEFAULT		 	0x00
	#define _COL_BLACK 				0x1e//30
	#define _COL_RED 					0x1f//31
	#define _COL_GREEN 				0x20//32
	#define _COL_YELLOW 			0x21//33
	#define _COL_BLUE 				0x22//34
	#define _COL_WHITE 				0x25//37

	//BG
	#define _COL_BLACK_BG 		0x1e00 + 0x0a00//30
	#define _COL_RED_BG 			0x1f00 + 0x0a00//31
	#define _COL_GREEN_BG 		0x2000 + 0x0a00//32
	#define _COL_YELLOW_BG 		0x2100 + 0x0a00//33
	#define _COL_BLUE_BG 			0x2200 + 0x0a00//34
	#define _COL_WHITE_BG 		0x2500 + 0x0a00//37

	//MOD
	#define _COL_BOLD 				0x010000
	#define _COL_UNDERLINE 		0x040000
	#define _COL_INVERSE 			0x070000

	//Not needed
	#define _COL_BOLD_OFF 		21
	#define _COL_UNDERLINE_OFF 24
	#define _COL_INVERSE_OFF 	27

#endif // __linux__

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
	cRender(char _backound, WORD _color);

	virtual ~cRender();

	/** Draws _c @ _pos in screenbuffer
	* _color can be combined by OR: (FG | BG | MOD). Anyone can be left out.
	*/
	int drawPoint(char _c, sPos _pos,  WORD _color);

	/** draws Line from _pos1 to _pos2 in screenbuffer
	*/
	int drawLine(char _c, sPos _pos1, sPos _pos2,  WORD _color);

	/** Draws Text _s @ _pos in screenbuffer
	* First char is @ _pos
	*/
	int drawText(string _s, sPos _pos, WORD _color);

	/** writes rectangle to screenbuffer
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

	/** Time in (real) seconds between last and second to last renders
	*/
	double getFrametime();

	/** Sets target Framerate. 0 for unlimited
	*/
	void setTargetFPS(unsigned int _fps);

	/** Deactivates automatic screen size detection and forces screen size to _size
	*/
	void forceScreenSize(sPos _size);

	/** Disable Output
	*/
	void mute(bool _mute);

	/** Enables Debug info Printing to screen
	*/
	void enableDebugInfo(bool _enable);

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

	bool bMute;
	bool bLockScreenSize;
	bool bPrintDebugInfo;

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

	//Timekeeping
	unsigned int uTargetFPS;
	clock_t lastRenderTime;
	double lastFrameTime;
	timespec lastRender;

#ifdef _WIN32
	HANDLE hstdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
#endif

	WORD wDefColor;
	//* Default Color

	int iLastError;

private:
	void forceReRender();

	void setConsoleEcho(bool _enable);

	void printDebugInfo();

	void waitForFrametime();
#ifdef _WIN32
	int SetConsoleWindowSize(int x, int y);
	//Slightly adapted from: http://www.cplusplus.com/forum/windows/121444/

	void gotoxy( int x, int y );

#elif __linux__
	sPos getConsoleWindowSize();

	void setConsoleCursor(bool _enable);

	void setAlternateBufferScreen(bool _enable);
#endif
};
