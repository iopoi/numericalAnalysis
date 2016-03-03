Instructions to compile and run the program.

1. type "make" to compile the program

2. type "./roots" with the correct arguments to run the program.

eg. "./roots 1.4 1.6"

The first argument is the lower bound and the second argument is the upper bound for the bisection method.
The first argument also doubles as the starting point for newtons method.

Once the program is run the results from both methods should print out to the console.
s

The make file includes an optional argument, type in  "make clean". This will delete the compiled program should you need to do it before recompiling the program.
There is an accuracy variable at the top of the roots.c file. You can edit it if you'd like. It is currently set to accept results that have errors of 0.0001 or less.

