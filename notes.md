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

---

