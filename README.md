# Minishell

Minishell is a simple shell implementation written in C.

## Table of Contents

- [About](#about)
- [Demo](#demonstration)
- [Features](#features)
- [Installation and Usage](#installation-and-usage)
- [Implementation Details](#implementation-details)
- [Sources](#sources)

## About
This program was developed together with [Eleonore](https://github.com/elecarlier). Taking [bash](https://www.gnu.org/software/bash/) as a reference, it aims to replicate the basic functionalities of a Unix shell. In general, a shell is an interface that acts as an intermediary between the user and the operating system kernel. It serves as a command interpreter, allowing users to interact with the system through a text-based interface.

## Demo

Below is a quick demonstration of this program showcasing the processing of some basic commands:

TODO: add demo video


https://github.com/user-attachments/assets/beb8e8de-5191-4bf3-a878-d87dd816a1d0



## Features

### Interactive CLI
- Prompt for entering commands
- Command history functionality for easy access to previous commands
- Ability to search and launch executables on the system
- Support of the following built-in commands:
	- `echo` (with -n option) to print messages
	- `cd` to change the current directory
	- `pwd` to print the current directory
	- `export` to set environment variables
	- `unset` to remove environment variables
	- `env` to display environment variables
	- `exit` to exit the shell
- Pipe implementation (|) for chaining commands together

### Input/Output Redirection
- Input redirection (<) to read input from a file
- Output redirection (>) to write output to a file
- Here-document functionality (<<) with a custom delimiter for multiline input
- Append output redirection (>>) to append output to a file

### Environment and Signal Handling
- Environment variable expansion ($VAR) for using variables in commands
- Handling of $? variable to access the exit status of the last command
- Signal handling (ctrl-C, ctrl-D, ctrl-\\) similar to bash behavior

For the comprehensive project requirements, please refer to the [subject](./en.subject.pdf).

## Installation and Usage
1. Clone this repository to your local machine, navigate to the directory, and build the program using the provided Makefile:
	```
	git clone https://github.com/deniz-oezdemir/Minishell
	cd Minishell
	make
	```

2. Run the executable `./minishell`.

3. Try out different commands supported by executables on your system or the [built-ins](#features) listed above.

## Implementation Details

When a command is entered into Minishell, the program processes it through several stages to execute it correctly.
First, the `lexer` reads the input string, handles spaces, and splits the input into individual commands while managing the command history and signals.
Second, the `parser` takes these commands and constructs a command list, checking for syntax errors and preparing the commands for execution.
Third, the `expander` then processes any environment variables and special characters within the commands, ensuring that all variables are correctly expanded.
Finally, `execute_cmds` runs the commands by forking processes, handling built-in commands, and managing input/output redirections.

The development of Minishell was a collaborative effort and the work was split as follows. [Eleonore](https://github.com/elecarlier) was responsible for the lexer, parser, and expander components, ensuring that the input commands were correctly handed over to the execution. [Deniz](https://github.com/deniz-oezdemir) focused on the command execution, implementing built-in commands and creating a first version of a simple [garbage collector](https://github.com/deniz-oezdemir/simple_garbage_collector) to support memory handling in the parser.

For testing purposes, [this tester](https://github.com/LucasKuhn/minishell_tester) by a fellow student was used.

The project adheres to the [Norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf), the coding standard of School 42, which includes restrictions such as no use of certain control structures (e.g., `for`, `do...while`, `switch`), a maximum of 25 lines per function, 80 columns per line, up to 4 named parameters per function, no mixed declarations and assignments, and a limit of 5 variables per function.

## Sources

- [Chapter 5](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/) of *Introduction to Systems Programming:
a Hands-on Approach*: Explains lexer, parser, expander, and executor.
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/): Used as a reference manual.
- [Explainshell](https://explainshell.com/): Write down a command-line to see the help text that matches each argument.

