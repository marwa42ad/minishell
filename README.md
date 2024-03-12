# 42 Minishell Project

## Project Overview
Minishell is a simple shell program that mimics some of the functionalities of bash. This project is part of the 42 school curriculum, aimed at teaching the basics of creating a shell, process management, and handling user input.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Parsing](#parsing)
- [Execution](#execution)
- [Contributors](#contributors)

## Introduction
The minishell project challenges students to create a shell program using C. The project is divided into two main components:
1. **Parsing**: Handling user input, interpreting commands, and preparing them for execution.
2. **Execution**: Executing the parsed commands and managing processes.

## Features
- Command line input
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
- Command execution with arguments
- Redirections (`>`, `<`, `>>`, `<<`) and pipes (`|`)
- Environment variable expansion
- Proper memory management and error handling

## Installation
Before installing minishell, make sure to install the `readline` library. This is especially important for macOS Ventura users who might not have the library installed by default. You can install `readline` using Homebrew:

```bash
brew install readline
```
After installing `readline`, you can proceed with installing minishell:

```bash
git clone https://github.com/PaulaBalbino/minishell.git
cd minishell
make
```
Note: If you encounter any issues with `readline` on macOS Ventura or other systems, ensure that Homebrew is updated and try reinstalling the library. Additionally, check for any system-specific instructions or workarounds.

## Usage
After installation, run minishell with:
```bash
./minishell
```

## Parsing
### Overview
The parsing part of the project involves interpreting the user's input into a format that can be easily executed. This includes:
- Lexical analysis
- Syntax analysis
- Command and argument parsing
- Handling quotes and special characters
- Redirection and pipe parsing

### Implementation Details
(Detail the implementation specifics, tools used, challenges faced, and how they were solved)

## Execution
### Overview
The execution part involves running the commands as interpreted by the parser. This includes:
- Executing built-in commands
- Managing processes for external commands
- Handling file redirections and pipes
- Environment variable management
- Signal handling

### Implementation Details
(Detail the implementation specifics, system calls used, challenges faced, and how they were solved)

## Contributors
- [Paula Balbino](https://github.com/PaulaBalbino)
- [pbalbino AlObeidli](https://github.com/pbalbino0)
