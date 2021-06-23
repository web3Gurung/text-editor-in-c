// header files
#include <unistd.h>  // used for read()
#include <termios.h> // used for tcgetattr() and tcsetattr()


void enableRawMode()
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, &raw);

    raw.c_lflag &= ~(ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main()
{
    enableRawMode();

    char c;
    
    while (read(STDIN_FILENO, &c, 1) == 1 && (c != 'q'));
	
    return 0;
}
