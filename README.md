# MINISHELL
As beautiful as shell

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
- [Challenges and Learning Outcomes](#challenges-and-learning-outcomes)
- [Contributing](#contributing)
- [Grade](#grade)

## Introduction

Minishell is a shell implementation project, part of the curriculum at School 42. This project aims to recreate a basic version of a Unix shell, providing fundamental command-line interface functionalities. It is an good educational tool to deepen understanding of process creation and control, file descriptors, and signal handling in a Unix environment.

## Features

- Basic command execution
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Environment variable expansion
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\\)
- Input/Output redirection (`<`, `>`, `>>`)
- Pipes (`|`)
- Quoting (simple and double quotes)
- Logical operators (`&&`, `||`)

## Installation

To install and run Minishell, follow these steps:

1. Clone the repository:
   ```sh
   git clone https://github.com/AurelienMarin/minishell42.git
   ```
2. Navigate to the project directory:
   ```sh
   cd minishell42
   ```
3. Install libreadline
    ```sh
    sudo apt install libreadline-dev
    ```
4. Compile the project:
   ```sh
   make
   ```

## Usage

After compilation, run the shell:

```
./minishell
```

You can now enter commands as you would in a standard Unix shell.

## Implementation Details

Minishell is implemented in C following the 42 coding standards. Key components include:

- Lexer and parser for command interpretation
- Process creation and management using `fork()` and `execve()`
- Signal handling
- File descriptor manipulation for I/O redirection
- Custom implementations of built-in commands

## Challenges and Learning Outcomes

Developing Minishell presented several challenges, including:

- Accurate parsing of complex command structures
- Proper handling of environment variables and their expansion
- Implementing signal handling without disrupting the shell's operation
- Managing file descriptors for I/O redirection and piping

Through overcoming these challenges, I gained valuable insights into:

- Low-level system programming in Unix environments
- Process creation and inter-process communication
- Shell behavior and command interpretation
- Robust error handling and memory management

## Contributing

While this project was completed as part of the School 42 curriculum, suggestions and discussions are welcome. Feel free to open an issue or submit a pull request.

## Grade
92/100 

![First correction](https://github.com/AurelienMarin/minishell42/blob/main/evaluation_screenshots/Correction%201.png)
![Second correction](https://github.com/AurelienMarin/minishell42/blob/main/evaluation_screenshots/Correction%202.png)
![Third correction](https://github.com/AurelienMarin/minishell42/blob/main/evaluation_screenshots/Correction%203.png)
