# Brainfuck-Interpreter
Interpreter for brainfuck, written in C++.


# How to use it
You execute it in the command line, the second argument should be the name 
of the .txt file you want to execute.

# How it works
It starts by reading all the strings in the code, then it counts brackets,
to see if there are opening/closing brackets errors, and it separate the
commands from the other char.
finally it execute every command by looping through the std::vector<char> and
switching every position.
