// header files
#include <unistd.h>  // used for read()
#include <termios.h> // used for tcgetattr() and tcsetattr()
#include <stdlib.h>
#include <stdio.h>  // for printf()
#include <ctype.h>  // for iscntrl()

struct termios orig_termios;

void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);   
}

void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    
    raw.c_iflag &= ~(BRKINT | INPCK | ICRNL | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main()
{
    enableRawMode();

    while (1) 
    {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);

        if (iscntrl(c))
        {
            printf("%d\r\n", c);
        }
        
        else
        {
            printf("%d ('%c')\r\n", c, c);
        }
    
        if (c == 'q')
        {
            break;
        }
    }
	
    return 0;
}
