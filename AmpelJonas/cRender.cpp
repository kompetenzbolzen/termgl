#include "cRender.h"


cRender::cRender(char _backound, WORD _color, int _sx, int _sy)
{
	bBlockRender = false; //If this Constructor is used, this instance is not inherited, thus render() doesn't need to be blocked
	iLastError = _OK_;
	sizeX = 0;
	sizeY = 0;

	cBackound = _backound;
	wBackColor = _color;

#ifdef __linux__ //In Linux, setting Console size is not supported, so it gets Size of Console (Window) instead.

	struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	wDefColor = _COL_DEFAULT;

	setBufferSize( getConsoleWindowSize() );

	if(sizeX < _sx || sizeY < _sy) //Notify Program tha screen is too small for desired Size
		iLastError = _ERR_SCREEN_TOO_SMALL_;

#elif _WIN32 //Windows Specific Code
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE); //get handle

	GetConsoleScreenBufferInfo(hstdout, &csbi); //get current console settings
	wDefColor = csbi.wAttributes; //Get default console color

	SetConsoleWindowSize(_sx + 1, _sy + 1); //set the windows size to _sx * _sy (+1 so no scrolling accurs)

	setBufferSize({_sx,_sy});
#endif

	setConsoleEcho(false);
	clear(true); //Init backround array
	//forceReRender();
}//render()


cRender::cRender() {}

cRender::~cRender()
{
	//Free allocated memory
	for (int i = 0; i < sizeX; i++) {
		free(cScreen[i]);
		free(wColor[i]);
		free(bChanged[i]);
	}

	free(cScreen);
	free(wColor);
	free(bChanged);
}

int cRender::drawPoint(char _c, sPos _pos, bool _overrideCollision, WORD _color)
{
	if (_pos.x >= sizeX || _pos.y >= sizeY || _pos.x < 0 || _pos.y < 0)
		return _ERR_COORDINATES_INVALID_;

	if (cScreen[_pos.x][_pos.y] != cBackound && _overrideCollision != true) //detect Collsision
		return _COLLISION_;

	cScreen[_pos.x][_pos.y] = _c;
	if (_color == _COL_DEFAULT) //_COL_DEFAULT is NOT a proper colorcode!
		wColor[_pos.x][_pos.y] = wDefColor;
	else
		wColor[_pos.x][_pos.y] = _color;

	if(!bBlockRender) //Changemap is not allocated in inherited Classes
		bChanged[_pos.x][_pos.y] = true;

	return 0;
}

int cRender::drawLine(char _c, sPos _pos1, sPos _pos2, bool _overrideCollision, WORD _color)
{
	if (_pos1.x == _pos2.x)	{ //Horizontal line
		for (int i = _pos1.y; i <= _pos2.y; i++)
		{
			drawPoint(_c, sPos{_pos1.x, i}, _overrideCollision, _color);
		}
	}
	else if (_pos1.y == _pos2.y) { //Vertical line
		for (int i = _pos1.x; i <= _pos2.x; i++)
		{
			drawPoint(_c, sPos{ i, _pos1.y }, _overrideCollision, _color);
		}
	}
	else { //Diagonal Line
		int dX = _pos1.x - _pos2.x;
		int dY = _pos1.y - _pos2.y;
		float fGradient = (float)dY / (float)dX;

		for (int i = 0; i <= abs(dX); i++)
		{
			drawPoint(_c, sPos{i + _pos1.x, (int)(i * fGradient + _pos1.y + 0.5)}, _overrideCollision, _color); //+0.5 for rounding error
		}
	}

	return 0;
}

int cRender::drawText(string _s, sPos _pos, WORD _color)
{
	for (int i = 0; i < _s.length(); i++)
	{
		drawPoint(_s[i], sPos{ i + _pos.x,_pos.y }, true,  _color);
	}
	return 0;
}

int cRender::drawRectangle(char _border, char _fill, sPos _pos1, sPos _pos2, WORD _borderColor, WORD _fillColor)
{
	//Draw the four outside lines
	drawLine(_border, _pos1, sPos{ _pos1.x, _pos2.y }, true, _borderColor);
	drawLine(_border, _pos1, sPos{ _pos2.x, _pos1.y }, true, _borderColor);
	drawLine(_border, sPos{ _pos1.x, _pos2.y }, _pos2, true, _borderColor);
	drawLine(_border, sPos{ _pos2.x, _pos1.y }, _pos2, true, _borderColor);

	//Fill rectangle if _fill isn't NULL
	if (_fill) {
		for (int i = _pos1.y + 1; i < _pos2.y; i++) {
			for (int o = _pos1.x + 1; o < _pos2.x; o++) {
				drawPoint(_fill, sPos{ o,i }, true, _fillColor);
			}
		}
	}

	return 0;
}

int cRender::render(void)
{
	if (bBlockRender)
		return _ERR_RENDER_BLOCKED_BY_CHILD_;

	setBufferSize(getConsoleWindowSize());

	for (int i = 0; i < sizeY; i++) {
		for (int o = 0; o < sizeX; o++) {
			gotoxy(o,i); //Moving this out of if fixed Render problem... Not optimal, though better for performance
			if(bChanged[o][i])
			{
				#ifdef _WIN32

				SetConsoleTextAttribute(hstdout, wColor[o][i] | _COL_INTENSITY);
				//cout << cScreen[o][i];
				printf("%c", cScreen[o][i]);

				#elif __linux__
				//cout << "\033["<< wColor[o][i] <<"m"<< cScreen[o][i];
				printf("\033[%im%c", wColor[o][i], cScreen[o][i]);
				#endif
			}
		bChanged[o][i] = false;
		}

	}

	gotoxy(sizeX - 1, sizeY - 1);

	return 0;
}

int cRender::clear(bool _forceReRender)
{
	for (int i = 0; i < sizeY; i++) {
		for (int o = 0; o < sizeX; o++) {
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
	return clear(false); //false doesn't work!
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
#endif

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

void cRender::gotoxy( int x, int y )
{
  int err;
  if (!cur_term)
    setupterm( NULL, STDOUT_FILENO, &err );
  putp( tparm( tigetstr( "cup" ), y, x, 0, 0, 0, 0, 0, 0, 0 ) );
}

sPos cRender::getConsoleWindowSize()
{
	struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	return {w.ws_col, w.ws_row - 1};
}
#endif

void cRender::setBufferSize(sPos _size)
{
	if(_size.x == sizeX && _size.y == sizeY)
		return;

	if(sizeX!=0 && sizeY!=0) //resize. delete first
	{
		for (int i = 0; i < sizeX; i++) {
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
	for (int i = 0; i < sizeX; i++)
		cScreen[i] = (char*)malloc(sizeof *cScreen[i] * sizeY);

	wColor = (WORD**)malloc(sizeof *wColor * sizeX);
	for (int i = 0; i < sizeX; i++)
		wColor[i] = (WORD*)malloc(sizeof *wColor[i] * sizeY);

	bChanged = (bool**)malloc(sizeof *bChanged * sizeX);
	for (int i = 0; i < sizeX; i++)
		bChanged[i] = (bool*)malloc(sizeof *bChanged[i] * sizeY);

	clear(true);
}

sPos cRender::getSize()
{
	return {sizeX, sizeY};
}

void cRender::forceReRender()
{
	for (int i = 0; i < sizeY; i++) {
		for (int o = 0; o < sizeX; o++) {
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

#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !_enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}
