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
- [stackoverflow](https://stackoverflow.com/questions/939989/invoking-gcc-as-cc-versus-gcc/30921933)
- [stackoverflow](https://stackoverflow.com/questions/1516609/difference-between-cc-gcc-and-g)

----


