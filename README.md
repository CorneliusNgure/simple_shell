# Custom Simple Shell Program

## Overview

This is a custom shell program developed in C that provides a command-line interface for interacting with the operating system. The custom shell allows users to execute various system commands and perform basic file operations. It is designed to provide a user-friendly and interactive experience for working with a command-line interface.

## Features

- Interactive command-line interface.
- Execution of system commands.
- Command history with up and down arrow navigation.
- I/O redirection for input and output.
- Piping support for connecting multiple commands.
- Custom command parsing and execution.
- Basic scripting capabilities.

## Getting Started

### Prerequisites

To compile and run the custom shell, you need:
- A C compiler (e.g., GCC)
- Standard C library

### Compiling the Custom Shell

Use the following command to compile the custom shell:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

USAGE:

The custom shell supports a variety of commands and features, including:

- Running system commands (e.g., ls, pwd, echo).
- Redirecting input and output using < and > operators.
- Piping commands using the | operator.
- Using built-in commands (e.g., cd, exit).

Author:
	Cornelius Ngure.
	kingcornelius07@gmail.com
	https://github.com/CorneliusNgure
