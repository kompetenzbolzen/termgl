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

//Macro, to get keycode of Ctrl-(k)
#define CTRL_KEY(k) ((k) & 0x1f)

#define _EVENT_NULL		0
#define _EVENT_CHAR		1
#define _EVENT_KEY		2
#define _EVENT_MOUSE		3
#define _EVENT_TERM		4 //Obsolete
#define _EVENT_FUNCTION1	5
#define _EVENT_CTRL		6

struct sInputEvent
{
	unsigned int type;
	unsigned char c;
	unsigned int b;
	int x, y;
};
/**
* ##cInput
* * puts STDIN in raw mode
* * activates mouse tracking
* * reverts console back to normal operation on destruction.
* Compatible with xterm compatible terminal emulators
*/
class cInput
{
public:
	cInput();

	~cInput();

	/** Reads inputevents
	* returns event struct
	* ### sInputEvent.type
	* * _EVENT_NULL: No input recorded
	* * _EVENT_CHAR: A Key was pressed, stored in .c
	* * _EVENT_KEY: Escape sequence recorded, stored in .c without escape char
	* * _EVENT_MOUSE: Console registered click at (.x, .y) with origin at (0,0) (top left). Mouse button stored in b.
	* * _EVENT_TERM: Console registered Ctrl+C. **OBSOLETE** use _EVENT_CTRL
	* * _EVENT_FUNCTION1: First few (4?) F-Keys. The rest of the F-Keys is handles by another ESC-Sequence!
	* * _EVENT_CTRL: Ctrl-key combination was pressed. Use CTRL_KEY( ) Macro to compare
	*/
	sInputEvent poll();

private:
	struct termios original, raw;
};

#endif /* end of include guard:	*/
