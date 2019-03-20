#include "cRender.h"


cRender::cRender(char _backound, WORD _color, unsigned int _sx, unsigned int _sy)
{
	bBlockRender = false; //If this Constructor is used, this instance is not inherited, thus render() doesn't need to be blocked
	iLastError = _OK_;
	sizeX = 0;
	sizeY = 0;

	cBackound = _backound;
	wBackColor = _color;

	uTargetFPS = 0;
	lastFrameTime = 0;
	lastRenderTime = 0;

#ifdef __linux__ //In Linux, setting Console size is not supported, so it gets Size of Console (Window) instead.

	wDefColor = _COL_DEFAULT;

	//Set up console
	setAlternateBufferScreen(true);
	setConsoleCursor(false);

	setBufferSize( getConsoleWindowSize() );

	if(sizeX < _sx || sizeY < _sy) //Notify Program tha screen is too small for desired Size
		iLastError = _ERR_SCREEN_TOO_SMALL_;

#elif _WIN32 //Windows Specific Code
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE); //get handle

	GetConsoleScreenBufferInfo(hstdout, &csbi); //get current console settings
	wDefColor = csbi.wAttributes; //Get default console color

	SetConsoleWindowSize(_sx + 1, _sy + 1); //set the windows size to _sx * _sy (+1 so no scrolling accurs)

	setBufferSize({_sx,_sy});
#endif //_WIN32

	setConsoleEcho(false);
	clear(true); //Init backround array

}//render()


cRender::cRender()
{
	cScreen = NULL;
	wColor = NULL;
	bBlockRender = false;
	cBackound = 0;
	wBackColor = 0;
	sizeX = sizeY = 0;
}

cRender::~cRender()
{
	if(bBlockRender) //Don't run destructor if inherited
		return;

	for (unsigned int i = 0; i < sizeX; i++) {
		free(cScreen[i]);
		free(wColor[i]);
		free(bChanged[i]);
	}

	free(cScreen);
	free(wColor);
	free(bChanged);

	setConsoleEcho(true);

	#ifdef __linux__
	setConsoleCursor(true);
	setAlternateBufferScreen(false);
	#endif //__linux__
}

int cRender::drawPoint(char _c, sPos _pos, WORD _color)
{
	if (_pos.x >= (int)sizeX || _pos.y >= (int)sizeY || _pos.x < 0 || _pos.y < 0)
		return _ERR_COORDINATES_INVALID_;

	cScreen[_pos.x][_pos.y] = _c;

	#ifdef _WIN32

	if (_color == _COL_DEFAULT) //_COL_DEFAULT is NOT a proper colorcode!
		wColor[_pos.x][_pos.y] = wDefColor;
	else
		wColor[_pos.x][_pos.y] = _color;

	#elif __linux__

		wColor[_pos.x][_pos.y] = _color;

	#endif

	if(!bBlockRender) //Changemap is not allocated in inherited Classes
		bChanged[_pos.x][_pos.y] = true;

	return 0;
}

int cRender::drawLine(char _c, sPos _pos1, sPos _pos2,  WORD _color)
{
	if(_pos1.x > _pos2.x)
	{
		//Shit WILL go wrong
		return drawLine(_c, _pos2, _pos1, _color);
	}

	if (_pos1.x == _pos2.x)	{ //Horizontal line
		for (int i = _pos1.y; i <= _pos2.y; i++)
		{
			drawPoint(_c, sPos{_pos1.x, i}, _color);
		}
	}
	else if (_pos1.y == _pos2.y) { //Vertical line
		for (int i = _pos1.x; i <= _pos2.x; i++)
		{
			drawPoint(_c, sPos{ i, _pos1.y }, _color);
		}
	}
	else { //Diagonal Line
		int dX = _pos1.x - _pos2.x;
		int dY = _pos1.y - _pos2.y;
		float fGradient = (float)dY / (float)dX;

		for (int i = 0; i <= abs(dX); i++)
		{
			drawPoint(_c, sPos{i + _pos1.x, (int)(i * fGradient + _pos1.y + 0.5)}, _color); //+0.5 for rounding error

			if(std::abs(fGradient) > 1.0)
			{
				int dy = (int)(((i + 1) * fGradient + _pos1.y + 0.5) - (i * fGradient + _pos1.y + 0.5));

				if(dy > 0 && ((int)(i * fGradient + _pos1.y + 0.5) + dy) <= _pos2.y)
				{
					drawLine(_c,
						sPos{i + _pos1.x, (int)(i * fGradient + _pos1.y + 0.5)},
						sPos{i + _pos1.x, (int)(i * fGradient + _pos1.y + 0.5) + dy },
						_color);
				}//if
				else if(dy < 0 && ((int)(i * fGradient + _pos1.y + 0.5) + dy) >= (_pos2.y) )
				{
					drawLine(_c,
						sPos{i + _pos1.x, (int)(i * fGradient + _pos1.y + 0.5) + dy },
						sPos{i + _pos1.x, (int)(i * fGradient + _pos1.y + 0.5)},
						_color);
				}//else if
			}//if
		}//for
	}//else

	return 0;
}//drawLine

int cRender::drawText(string _s, sPos _pos, WORD _color)
{
	for (unsigned int i = 0; i < _s.length(); i++)
	{
		drawPoint(_s[i], sPos{ (int)i + _pos.x,_pos.y },  _color);
	}
	return 0;
}

int cRender::drawRectangle(char _border, char _fill, sPos _pos1, sPos _pos2, WORD _borderColor, WORD _fillColor)
{
	//Draw the four outside lines
	drawLine(_border, _pos1, sPos{ _pos1.x, _pos2.y }, _borderColor);
	drawLine(_border, _pos1, sPos{ _pos2.x, _pos1.y }, _borderColor);
	drawLine(_border, sPos{ _pos1.x, _pos2.y }, _pos2, _borderColor);
	drawLine(_border, sPos{ _pos2.x, _pos1.y }, _pos2, _borderColor);

	//Fill rectangle if _fill isn't NULL
	if (_fill) {
		for (int i = _pos1.y + 1; i < _pos2.y; i++) {
			for (int o = _pos1.x + 1; o < _pos2.x; o++) {
				drawPoint(_fill, sPos{ o,i }, _fillColor);
			}
		}
	}

	return 0;
}

int cRender::render(void)
{
	if (bBlockRender)
		return _ERR_RENDER_BLOCKED_BY_CHILD_;

	waitForFrametime();

	//Resize screenbuffer if needed
	setBufferSize( getConsoleWindowSize( ) );

	printDebugInfo();

	//For measuring render time
	clock_t startTime = clock();

	for (unsigned int i = 0; i < sizeY; i++) {
		for (unsigned int o = 0; o < sizeX; o++) {
			if(bChanged[o][i])
			{
				#ifdef _WIN32

				gotoxy(o,i);
				SetConsoleTextAttribute(hstdout, wColor[o][i] | _COL_INTENSITY);

				printf("%c", cScreen[o][i]);

				#elif __linux__

				char buffer[20];
				char colorstr[20];
				uint8_t color[3] = {(uint8_t) (0x0000ff & wColor[o][i]),				//Color
														(uint8_t)((0x00ff00 & wColor[o][i]) >> 8),	//Background
														(uint8_t)((0xff0000 & wColor[o][i]) >> 16)};//Modifier

				{////
					int cc = 0;
					cc = cc + sprintf(&colorstr[cc], "%u", color[0]);
					if(color[1])
					{
						colorstr[cc] = ';';
						colorstr[cc + 1] = color[1];
						cc += 1 + sprintf(&colorstr[cc + 1], "%u", color[1]);
					}
					if(color[2])
					{
						colorstr[cc] = ';';
						cc += 1 + sprintf(&colorstr[cc + 1], "%u", color[2]);
					}
				}////

				int cbuf = sprintf(buffer,"\e[%u;%uH\e[%sm%c\e[0m", i + 1, o + 1, colorstr, cScreen[o][i]);
				//      										Position  Color        Origin is at 1,1
				//int cbuf = sprintf(buffer,"\e[%u;%uH%c", i + 1, o + 1, cScreen[o][i]);
				write (STDOUT_FILENO, buffer, cbuf);

				#endif //__linux__
			}
			bChanged[o][i] = false;
		}
	}

	//calc render time
	lastRenderTime = clock() - startTime;

	//calc time since last render
	timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	lastFrameTime = (now.tv_sec - lastRender.tv_sec);
	lastFrameTime += (now.tv_nsec - lastRender.tv_nsec) / 1000000000.0;
	//save current time
	clock_gettime(CLOCK_MONOTONIC, &lastRender);

	return 0;
}

int cRender::clear(bool _forceReRender)
{
	for (unsigned int i = 0; i < sizeY; i++) {
		for (unsigned int o = 0; o < sizeX; o++) {
			if(((cScreen[o][i] == cBackound) && (wColor[o][i] == wBackColor)) && !_forceReRender)
				bChanged[o][i] 	= false;
			else
			{
				cScreen[o][i] 	= cBackound;
				wColor[o][i] 		= wBackColor;
				bChanged[o][i] 	= true;
			}
		}
	}
	return 0;
}

int cRender::clear()
{
	return clear(false);
}


#ifdef _WIN32
//Source: http://www.cplusplus.com/forum/windows/121444/
int cRender::SetConsoleWindowSize(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (h == INVALID_HANDLE_VALUE)
		return 1;

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	if (!GetConsoleScreenBufferInfo(h, &bufferInfo))
		return 1;

	SMALL_RECT& winInfo = bufferInfo.srWindow;
	COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

	if (windowSize.X > x || windowSize.Y > y)
	{
		// window size needs to be adjusted before the buffer size can be reduced.
		SMALL_RECT info =
		{
			0, 0,
			x < windowSize.X ? x - 1 : windowSize.X - 1,
			y < windowSize.Y ? y - 1 : windowSize.Y - 1
		};

		if (!SetConsoleWindowInfo(h, TRUE, &info))
			return 1;
	}

	COORD size = { x, y };
	if (!SetConsoleScreenBufferSize(h, size))
		return 1;

	SMALL_RECT info = { 0, 0, x - 1, y - 1 };
	if (!SetConsoleWindowInfo(h, TRUE, &info))
		return 1;
}
#endif //_WIN32

int cRender::getLastError()
{
	return iLastError;
}

#ifdef _WIN32
void cRender::gotoxy( int x, int y )
{
  COORD p = { x, y };
  SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}

#elif __linux__

sPos cRender::getConsoleWindowSize()
{
	struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	return {w.ws_col, w.ws_row};
}

void cRender::setAlternateBufferScreen(bool _enable)
{
	_enable ? write (STDOUT_FILENO, "\e[?47h", 6):write (STDOUT_FILENO, "\e[?47l", 6);
}

void cRender::setConsoleCursor(bool _enable)
{
	_enable ? write (STDOUT_FILENO, "\e[?25h", 6) : write (STDOUT_FILENO, "\e[?25l", 6);
}

#endif // __linux__

void cRender::setBufferSize(sPos _size)
{
	if(_size.x == (int)sizeX && _size.y == (int)sizeY)
		return;

	if(_size.x < 0 || _size.y < 0)
		return;

	if(sizeX!=0 && sizeY!=0) //resize. delete first
	{
		for (unsigned int i = 0; i < sizeX; i++) {
			free(cScreen[i]);
			free(wColor[i]);
			free(bChanged[i]);
		}

		free(cScreen);
		free(wColor);
		free(bChanged);
	}

	sizeX = _size.x;
	sizeY = _size.y;

	//Initialize 2D array
	cScreen = (char**)malloc(sizeof *cScreen * sizeX);
	for (unsigned int i = 0; i < sizeX; i++)
		cScreen[i] = (char*)malloc(sizeof *cScreen[i] * sizeY);

	wColor = (WORD**)malloc(sizeof *wColor * sizeX);
	for (unsigned int i = 0; i < sizeX; i++)
		wColor[i] = (WORD*)malloc(sizeof *wColor[i] * sizeY);

	bChanged = (bool**)malloc(sizeof *bChanged * sizeX);
	for (unsigned int i = 0; i < sizeX; i++)
		bChanged[i] = (bool*)malloc(sizeof *bChanged[i] * sizeY);

	clear(true);
}

sPos cRender::getSize()
{
	return {(int)sizeX, (int)sizeY};
}

void cRender::forceReRender()
{
	for (unsigned int i = 0; i < sizeY; i++) {
		for (unsigned int o = 0; o < sizeX; o++) {
				bChanged[o][i] 	= true;
		}
	}
}

void cRender::setConsoleEcho(bool _enable)
{
#ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if( !_enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode );

#elif __linux__
    /*struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !_enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);*/

		_enable ? write (STDOUT_FILENO, "\e[?8h", 5) : write (STDOUT_FILENO, "\e[?8l", 5);
#endif //__linux__
}

double cRender::getFrametime()
{
	return lastFrameTime;
}

void cRender::setTargetFPS(unsigned int _fps)
{
	uTargetFPS = _fps;
}

void cRender::printDebugInfo()
{
	char dbgtxt[30];

	sprintf(dbgtxt, "R: %f F: %f", ((float)lastRenderTime) / CLOCKS_PER_SEC, 1/getFrametime());

	drawText(dbgtxt, {0,0}, _COL_BLACK | _COL_WHITE_BG);
}

void cRender::waitForFrametime()
{
	if(!uTargetFPS)
		return;

	timespec now;
	double elapsed;
	double left;
	clock_gettime(CLOCK_MONOTONIC, &now);
	elapsed = (now.tv_sec - lastRender.tv_sec);
	elapsed += (now.tv_nsec - lastRender.tv_nsec) / 1000000000.0;

	if(elapsed > (1/(double)uTargetFPS))
		return;

	left = (1/(double)uTargetFPS) - elapsed - (((double)lastRenderTime) / CLOCKS_PER_SEC);

	std::this_thread::sleep_for(std::chrono::milliseconds(int (left * 1000)));


}
