# Simple Shell Project README

This repository contains a series of iterations for building a simple UNIX command line interpreter, also known as a shell. The project aims to progressively enhance the functionality of the shell with each iteration.

## Table of Contents

1. [Simple Shell 0.1](#simple-shell-01)
2. [Simple Shell 0.2](#simple-shell-02)
3. [Simple Shell 0.3](#simple-shell-03)
4. [Simple Shell 0.4](#simple-shell-04)
5. [Simple Shell 1.0](#simple-shell-10)

## Simple Shell 0.1

The initial version of the shell requires writing a UNIX command line interpreter. The basic functionality includes:

- Displaying a prompt and waiting for user input.
- Executing commands entered by the user.
- Displaying the prompt again after command execution.
- Handling simple, single-word commands.
- Printing an error message when an executable is not found.
- Handling the "end of file" condition (Ctrl+D).

## Simple Shell 0.2

Building upon the previous version, this iteration extends the shell's capabilities by allowing command lines with arguments.

## Simple Shell 0.3

In this iteration, the shell adds further enhancements:

- Handling the PATH environment variable to find executables.
- Implementing a mechanism to avoid unnecessary forking when the command doesn't exist.

## Simple Shell 0.4

The shell now includes the built-in `exit` command, which allows the user to exit the shell. The `exit` command doesn't require any arguments.

## Simple Shell 1.0

The final version of the shell includes the implementation of the `env` built-in command. This command displays the current environment variables.

## How to Use

1. Clone the GitHub repository: [simple_shell](https://github.com/YOUR_USERNAME/simple_shell).
2. Navigate to the appropriate directory for the desired version of the shell.
3. Compile the shell's source code using the appropriate commands (not provided in this README).
4. Run the compiled executable to start the shell.
5. Enter commands as specified in the version's requirements.
6. To exit the shell, use the `exit` command.

Please note that the specific compilation and execution steps are not included in this README, as they depend on the programming language used and the environment in which the code is being executed.

Feel free to explore each version of the shell in the provided GitHub repository and enhance its functionality according to the specified requirements.

**Disclaimer:** This README is a simplified summary of the project's requirements and goals. For the most accurate and detailed instructions, refer to the actual project repository and any accompanying documentation.
