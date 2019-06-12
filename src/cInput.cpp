#include "cInput.h"

cInput::cInput()
{
	// Save original serial communication configuration for stdin
	tcgetattr( STDIN_FILENO, &original);

	// Put stdin in raw mode so keys get through directly without
	// requiring pressing enter.
	cfmakeraw (&raw);
	tcsetattr (STDIN_FILENO, TCSANOW, &raw);

	// Enable mouse tracking
	write (STDOUT_FILENO, "\e[?1000h", 8);
}

cInput::~cInput()
{
	//revert changes to console
	write (STDOUT_FILENO, "\e[?1000l", 8);
	tcsetattr (STDIN_FILENO, TCSANOW, &original);
}

sInputEvent cInput::poll()
{
	const unsigned int buff_len = 5;
	sInputEvent ret;
	unsigned char buff [buff_len];

	//setup for select
	fd_set rfds;
	struct timeval tv;
	FD_ZERO(&rfds);
	FD_SET(STDIN_FILENO, &rfds);
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	ret.type = _EVENT_NULL;

	//Check for Input. return of none
	if(!select(1, &rfds, NULL, NULL, &tv))
		return ret;

	read (STDIN_FILENO, &buff, 1);
	if (buff[0] == 3) {
			// User pressd Ctr+C
			ret.type = _EVENT_TERM;
	}
	else if (buff[0] == '\x1B') //Escape sequence
	{
		read (STDIN_FILENO, &buff, buff_len);
		if(buff[0] == '[')
		{
			if(buff[1] == 'M') //Mouse Event
			{
				ret.b = buff[2] - 32;
				ret.x = buff[3] - 32 - 1; //Console sees origin at 1,1
				ret.y = buff[4] - 32 - 1; //Program at 0,0
				ret.type = _EVENT_MOUSE;
			}
			else //e.g. Arrow Keys
			{
				ret.c = buff[1];
				ret.type = _EVENT_KEY;
			}
		}
		else if(buff[0] == 'O')
		{
			ret.c = buff[1];
			ret.type = _EVENT_FUNCTION1;
		}
	}
	else
	{
		ret.type = _EVENT_CHAR;
		ret.c = buff[0];
	}
		return ret;
}
