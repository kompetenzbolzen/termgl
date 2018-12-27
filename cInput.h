/*
* cInput is responsible for Handling everything related to setting up and managing the console window
* as well as decoding keyboard and mouse events.
* Compatible with xterm compatible terminal emulators
*/

#ifndef CINPUT_H_
#define CINPUT_H_

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

#ifdef __linux__
#elif _WIN32
  #error "Platforn not supported"
#else
  #error "Platforn not supported"
#endif

#define _EVENT_NULL   0
#define _EVENT_CHAR   1
#define _EVENT_KEY    2
#define _EVENT_MOUSE  3
#define _EVENT_TERM   4

struct sInputEvent
{
  unsigned int type;
  unsigned char c;
  unsigned int b;
  unsigned int x, y;
};

class cInput
{
public:
  cInput();

  ~cInput();

  sInputEvent poll();

private:
  struct termios original, raw;
};

#endif /* end of include guard:  */
