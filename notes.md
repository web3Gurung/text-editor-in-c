## step 1

**what does "echo $?" do?**

- This is the exit status of the last executed command.
- By convention an exit status of 0 means success, and non-zero return status means failure.
- true will always return a status of 0 and false will return 1.

reference [stackoverflow](https://stackoverflow.com/questions/7248031/meaning-of-dollar-question-mark-in-shell-scripts)

<br>

**difference between "cc" and "gcc"**

- CC is an environment variable referring to the system's C compiler.
- there is no difference as such. 
- On most linux platforms, cc almost always points to /usr/bin/gcc (which is GNU's gcc compiler).

reference 

- check this first [stackoverflow](https://stackoverflow.com/questions/939989/invoking-gcc-as-cc-versus-gcc/30921933)
- [stackoverflow](https://stackoverflow.com/questions/1516609/difference-between-cc-gcc-and-g)

----

**how to use .gitignore file**

- [stackoverflow](https://stackoverflow.com/questions/4308610/how-to-ignore-certain-files-in-git)
- [Bitbucket](https://www.atlassian.com/git/tutorials/saving-changes/gitignore)

<br>

**Git push results in “Authentication Failed”**

- if you face this issue then head over to [stackoverflow](https://stackoverflow.com/questions/17659206/git-push-results-in-authentication-failed)

----

## Step 2

made the makefile and noted what all was used -

- $(CC) is an implicit variable where CC = gcc. More variables in GNU's [site](https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html)
- quick intro to makefiles by [washington uni](https://courses.cs.washington.edu/courses/cse451/99wi/Section/makeintro.html)
- -Wall gives **all w**arnings - basically it gives more warning out of your C code.
- -Wextra - gives more warnings (yes, it seems I want the code to be *thoroughly* checked).
- -pedantic - it makes the code to follow ANSI way of writing code (it is the standard of writing C code). [purpose of using](https://stackoverflow.com/questions/2855121/what-is-the-purpose-of-using-pedantic-in-gcc-g-compiler) and [this](https://softwareengineering.stackexchange.com/questions/88532/whether-to-use-pedantic-flag-in-g-or-not)
- -std=c99 specifies the exact version of the C language standard we’re using, which is C99.

<br>

(*note: just found out that "vimtutor" exists in the CLI and you can learn vim basics in ~30 min*)


----

## Step 3

- `STDIN_FILENO` is the default data stream for input from the command line, and its value is `0`. [man page](https://man7.org/linux/man-pages/man3/stdin.3.html)
- [Stack Overflow](https://stackoverflow.com/questions/5256599/what-are-file-descriptors-explained-in-simple-terms) has simpler definition given one of them which is -> 

```
a) File Descriptors (FD) are non-negative integers (0, 1, 2, ...) that are associated with files that are opened. 
b)  0, 1, 2 are standard FD's that corresponds to STDIN_FILENO, STDOUT_FILENO and STDERR_FILENO (defined in unistd.h) opened by default on behalf of shell when the program starts.
```

- The thing to note is that each process which deals with a file (can say almost every process since everything is a file in Linux), has its own file descriptor (FD), which is **unique per process**.

From the man page for the `read()` function.

```bash
SYNOPSIS
       #include <unistd.h>

       ssize_t read(int fd, void *buf, size_t count);

DESCRIPTION
       read()  attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.
```

What we can get from this is that `*buf` is a ptr to the variable which points to the variable's address space. `count` accepts the number of bytes to the `*buf`. And `fd` is a file descriptor.

<br>

Canonical mode vs raw mode - [Unix Stack Exchange](https://unix.stackexchange.com/questions/21752/what-s-the-difference-between-a-raw-and-a-cooked-device-driver)

In cooked (canonical) mode, the terminal's commands can be edited before executing it (pressing `enter`). This means we can use backspace and modify it all before executing the command, the computer won't know about it.

In Raw mode, the terminal send each character it gets in it to the computer. So, if we press backspace to edit strings, the computer knows about it.

----

## Step 4

We want the terminal to exit the moment we press 'q' anywhere in the string. This means the program does not read the character entered after 'q'.

```bash
$ ./kilo 
asdasdasd
asdasdasdasdqdasd  # added a 'q' in the 5th value from the last
$ dasd
Command 'dasd' not found, did you mean:
  command 'fasd' from deb fasd (1.0.1-1)
  command 'dad' from deb debian-dad (1)
  command 'nasd' from deb nas (1.9.4-6build1)
  command 'dash' from deb dash (0.5.10.2-7)
Try: sudo apt install <deb name>
```

----

## Step 5

Since the tutorial says about "tcgetattr()", we search about it in the man pages. Typing `man 3p tcgetattr`, we get the following:

```
NAME
       tcgetattr — get the parameters associated with the terminal

SYNOPSIS
       #include <termios.h>

       int tcgetattr(int fildes, struct termios *termios_p);

DESCRIPTION
       The tcgetattr() function shall get the parameters associated  with  the
       terminal  referred to by fildes and store them in the termios structure
       referenced by termios_p.  The fildes argument is an open file  descrip‐
       tor associated with a terminal.

       The termios_p argument is a pointer to a termios structure.

       The tcgetattr() operation is allowed from any process.
```

in the above man page doc, `fildes` = `file descriptor`.

<br>

When we type `man 3 tcgetattr`, we get a ton of material from the man pages. Somewhere after scrolling, we find this:

```
tcgetattr() gets the parameters associated with the object referred by fd and stores  them  in
the termios structure referenced by termios_p.  This function may be invoked from a background;
however, the terminal attributes may be subsequently changed by a foreground process.

tcsetattr() sets the parameters associated with the terminal (unless support is required  from
the  underlying  hardware  that  is  not  available) from the termios structure referred to by
termios_p.
```

<br>

Last but not the least, after going through the same above man page, we find a interesting thing abou   t the terminal. About the size of input it excepts.

```
The maximum line length is 4096 chars (including the terminating newline  character);  lines
longer than 4096 chars are truncated.  After 4095 characters, input processing (e.g., ISIG
and ECHO* processing) continues, but any input data after 4095 characters up to (but not in‐
cluding)  any  terminating  newline is discarded.  This ensures that the terminal can always
receive more input until at least one line can be read.
```



<br>



Step 5 seems a lot, but it's alright. After we edit the step 5 from the tutorial to our kilo.c, we dig deep into `man tcgetattr` and find out what `TCSAFLUSH` and `ECHO` (ECHO is one of the constraint under `c_lflag` flag) is:

```
ECHO   Echo input characters.

TCSAFLUSH
              the change occurs after all output written to the object
              referred  by fd has been transmitted, and all input that
              has been received but not read will be discarded  before
              the change is made.
```



<br>



Since we turned off the `ECHO` property of the terminal, whatever we type is not printed on the terminal (just like the password field when we type `sudo`).

Now, after quitting kilo (it responds to 'q' in the input btw) our bash shell got stuck since it was acting as if it was still running kilo. The tutorial says what to do if this happens -

```
After the program quits, depending on your shell, you may find your terminal is still 
not echoing what you type. Don’t worry, it will still listen to what you type. Just 
press Ctrl-C to start a fresh line of input to your shell, and type in reset
and press Enter. This resets your terminal back to normal in most cases. Failing that,
you can always restart your terminal emulator. 
```

<br>



**Now, some theory** -

The terminal attributes which we fed are read into a termios structure with the help of `tcgetattr`. After modyfying the attributes, we apply them to the terminal using `tcsetattr`. The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.

From the tutorial -

The `c_lflag` field is for “local flags”. A comment in macOS’s <termios.h> describes it as a “dumping ground for other state”. So perhaps it should be thought of as “miscellaneous flags”. The other flag fields are `c_iflag` (input flags), `c_oflag` (output flags), and `c_cflag` (control flags), all of which we will have to modify to enable raw mode.

`ECHO` is a bit flag, and its value is defined as `00000000000000000000000000001000` in binary. We use the NOT operator ( ` ~`) to reverse the bits and get `11111111111111111111111111110111`. Now to modify the value of `c_lflag` with this bitflag's value, we use the AND operator.

----

## Step 6

In this step, we are making our text editor keep the original values of the terminal attributes and execute it after it gets terminated. We do this by using `atexit()` function to register our disableRawMode() function to be called automatically when the program exits, whether it exits by returning from main(), or by calling the exit() function.

We're storing the original terminal attributes in a global variable, `orig_termios`. We assign the orig_termios struct to the raw struct in order to make a copy of it before we start making our changes. One thing to remeember is that our text editor exits after pressing 'q' or `Ctrl + c` and it it discards any unread input before applying the changes to the terminal.


from the man page of `man atexit`
```
NAME
       atexit - register a function to be called at normal process termination

SYNOPSIS
       #include <stdlib.h>

       int atexit(void (*function)(void));

DESCRIPTION
       The  atexit()  function  registers  the given function to be called at normal process termination, either via
       exit(3) or via return from the program's main().  Functions so registered are called in the reverse order  of
       their registration; no arguments are passed.

       The same function may be registered multiple times: it is called once for each registration.

RETURN VALUE
       The atexit() function returns the value 0 if successful; otherwise it returns a nonzero value.
```

----

## Step 7

from `man tcgetattr`, there is a line which tells what `ICANON` flag does (one of the constraint under `c_lflag` flag) -

```
The setting of the ICANON canon flag in c_lflag determines whether the terminal is operating in canonical mode  (ICANON  set)  or  non‐canonical mode (ICANON unset).  By default, ICANON is set.
       
ICANON Enable canonical mode.
```

What this flag does is that it allows us to turn off canonical mode. This means we will be reading input byte-by-byte, instead of line-by-line. Thanks to this step, the program will quit as soon as we press `q`.

----

## Step 8

This step seemed as if kilo is imbued with magic. See for yourself:

```bash
$ ./kilo 
116 ('t')
104 ('h')
105 ('i')
115 ('s')
105 ('i')
115 ('s')
99 ('c')
111 ('o')
111 ('o')
111 ('o')
108 ('l')
33 ('!')
```

Pressed 'q' to exit kilo.

<br>

What we've added in this step is `iscntrl()` and `printf()`, from `ctype.h` and `stdio.h`, respectively. Now pasting notes from the turorial since it explainsit in a great manner -

`iscntrl()` tests whether a character is a control character. Control characters are nonprintable characters that we don’t want to print to the screen. ASCII codes 0–31 are all control characters, and 127 is also a control character. ASCII codes 32–126 are all printable. We can check out [ASCII table](https://www.asciitable.com/) for more info on ASCII characters.

printf() can print multiple representations of a byte. %d tells it to format the byte as a decimal number (its ASCII code), and %c tells it to write out the byte directly, as a character.

<br>

Arrow keys, Page Up, Page Down, Home, and End - There are all escape sequences, we can see that after pressing these buttons, the first byte is `27`, `[` followed by 1-2 bytes. All escape sequences start with `27`. And one nice observation is that the `Esc` button shows us `27` as the decimal output when pressed.

<br>

From the turorial:

```
By the way, if you happen to press Ctrl-S, you may find your program seems to be frozen. What you’ve done is you’ve asked your program to stop sending you output. Press Ctrl-Q to tell it to resume sending you output.

Also, if you press Ctrl-Z (or maybe Ctrl-Y), your program will be suspended to the background. Run the fg command to bring it back to the foreground. 
```

----

## Step 9

In this step, we are turning off the default signal `Ctrl+C` and `Ctrl+Z` sends to the terminal. By default, Ctrl-C sends a SIGINT signal to the current process which causes it to terminate, and Ctrl-Z sends a SIGTSTP signal to the current process which causes it to suspend (we can type `fg`)

```
c_lflag flag constants:

       ISIG   When  any  of  the characters INTR, QUIT, SUSP, or DSUSP are received, generate the corresponding signal.
```

<br>

Now we can only exit kilo by pressing 'q' and not `Ctrl+C` or `Ctrl+Z`.

```bash
$ ./kilo
1
2
3  # Ctrl+C
4
26  # Ctrl+Z
```

----

## Step 10

Just came across this (down below) from the man page of termios -
**This will be handy - you'll understand this after step 15.**

```
Raw mode
       cfmakeraw()  sets  the  terminal to something like the "raw" mode of the old Version 7 terminal driver: input is available character by
       character, echoing is disabled, and all special processing of terminal input and output  characters  is  disabled.   The  terminal  at‐
       tributes are set as follows:

           termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                           | INLCR | IGNCR | ICRNL | IXON);
           termios_p->c_oflag &= ~OPOST;
           termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
           termios_p->c_cflag &= ~(CSIZE | PARENB);
           termios_p->c_cflag |= CS8;

```

We see that we our kilo's `c_lflag` matches the flags from the above doc.

<br>

By default, Ctrl-S and Ctrl-Q are used for [software flow control](https://en.wikipedia.org/wiki/Software_flow_control). Ctrl-S stops data from being transmitted to the terminal until you press Ctrl-Q.


From the man pages of termios, we get what `IXON` means -

```
IXON   Enable XON/XOFF flow control on output.
```

The "I" here means input flag (unlike ISIG and ICANON). `XON` comes from the names of the two control characters that `Ctrl-S` and `Ctrl-Q` produce: `XOFF` to pause transmission and `XON` to resume transmission.

<br>

```bash
$ ./kilo
19
17  
```

Now Ctrl-S can be read as a 19 byte and Ctrl-Q can be read as a 17 byte.

----

## Step 11

From the tutorial -

```
On some systems, when you type Ctrl-V, the terminal waits for you to type another character and then 
sends that character literally. For example, before we disabled Ctrl-C, you might’ve been able to type 
Ctrl-V and then Ctrl-C to input a 3 byte. We can turn off this feature using the IEXTEN flag.
```

This is something which didn't happen in my terminal when kilo was running. Nevertheless, I will be adding the flag `IEXTEN` to the c_lflag.

From the man pages -

```
IEXTEN Enable  implementation-defined  input processing.  This flag, as well as ICANON must be enabled for the special characters EOL2, LNEXT, REPRINT, WERASE to be interpreted, and for the IUCLC flag to be effective.
```


