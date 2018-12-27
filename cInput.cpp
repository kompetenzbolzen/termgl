#include "cInput.h"

cInput::cInput()
{
  // Save original serial communication configuration for stdin
  tcgetattr( STDIN_FILENO, &original);

  // Put stdin in raw mode so keys get through directly without
  // requiring pressing enter.
  cfmakeraw (&raw);
  tcsetattr (STDIN_FILENO, TCSANOW, &raw);

  // Switch to the alternate buffer screen
  write (STDOUT_FILENO, "\e[?47h", 6);

  // Enable mouse tracking
  write (STDOUT_FILENO, "\e[?1000h", 8);
}

cInput::~cInput()
{
  //revert changes to console
  write (STDOUT_FILENO, "\e[?1000l", 8);
  write (STDOUT_FILENO, "\e[?47l", 6);
  tcsetattr (STDIN_FILENO, TCSANOW, &original);
}

sInputEvent cInput::poll()
{
  sInputEvent ret;
  unsigned char buff [6];

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
    read (STDIN_FILENO, &buff, 5);
    if(buff[0] == '[')
    {
      if(buff[1] == 'M') //Mouse Event
      {
        ret.b = buff[2] - 32;
        ret.x = buff[3] - 32;
        ret.y = buff[4] - 32;
        ret.type = _EVENT_MOUSE;
      }
      else //e.g. Arrow Keys
      {
        ret.c = buff[1];
        ret.type = _EVENT_KEY;
      }
    }
  }
  else
  {
    ret.type = _EVENT_CHAR;
    ret.c = buff[0];
  }
    return ret;
}
