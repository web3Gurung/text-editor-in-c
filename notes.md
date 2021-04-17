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
 
