# Minishell

## Overview

This project requires you to implement a simple Unix shell, named **minishell**, from scratch. It must mimic basic shell functionalities such as executing commands, handling built-ins, redirections, pipes, and environment variables, while adhering to specific constraints.

The shell must be interactive, support history, handle basic signals (Ctrl-C, Ctrl-D, Ctrl-\), and allow proper management of environment variables. Your implementation should not use global variables for more than just the signal number, and it must respect the behavior of common commands such as `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

### Mandatory Setup Requirements

You will implement the shell using the following:
- **File Structure**:
  - `Makefile`
  - `*.c` files for your shell's logic
  - `*.h` files for header declarations

- **Makefile Targets**:
  - `NAME` – Name of the program to compile (e.g., `minishell`)
  - `all` – Build the program
  - `clean` – Clean up intermediate files (e.g., object files)
  - `fclean` – Clean up the program’s binary
  - `re` – Rebuild the project (using `clean` and `all`)

- **Required External Functions**:
  Your implementation should use the following system and library calls:
  - `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`
  - `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`
  
- **Libft**: You are authorized to use your **Libft** (or any other external libraries that are allowed) to implement your solution.

### Key Features of Minishell

1. **Prompt & Input Handling**:
   - Display a prompt when waiting for a new command.
   - Implement a working history feature for commands using `readline` and `add_history`.
  
2. **Command Execution**:
   - Correctly search and execute executables, either from the **PATH** or using relative/absolute paths.
  
3. **Redirection Handling**:
   - Implement input/output redirection using the following:
     - `<` for input redirection
     - `>` for output redirection
     - `<<` for input redirection using a delimiter
     - `>>` for output redirection in append mode

4. **Pipes**:
   - Implement pipes (`|`) to allow chaining multiple commands where the output of one command becomes the input of the next.

5. **Environment Variables**:
   - Implement expansion for environment variables (`$variable`) within the commands.
   - Implement the `$?` special variable to represent the exit status of the most recently executed foreground pipeline.

6. **Signal Handling**:
   - Implement proper handling of common signals:
     - **Ctrl-C**: Display a new prompt on a new line.
     - **Ctrl-D**: Exit the shell.
     - **Ctrl-\**: Do nothing.
  
7. **Built-in Commands**:
   The following built-ins must be implemented:
   - `echo` with option `-n`
   - `cd` with only a relative or absolute path
   - `pwd` with no options
   - `export` with no options
   - `unset` with no options
   - `env` with no options or arguments
   - `exit` with no options
  
8. **Memory Management**:
   - While memory leaks caused by `readline()` should not be fixed (it is outside the scope of this project), ensure that **your own code** does not have any memory leaks.

9. **Error Handling**:
   - Properly handle errors and return appropriate exit statuses for each command.

### Additional Notes

- **Signal Handling & Global Variables**: 
  You are only allowed to use a **single global variable** to store the received signal number. It is essential that this variable is not used to store any other data or provide access to other information. The use of complex structures or additional data in global scope is strictly forbidden.

- **Unclosed Quotes & Special Characters**:
  - Do not interpret unclosed quotes or special characters like backslashes (`\`) or semicolons (`;`).
  - Handle single quotes (`'`) and double quotes (`"`) appropriately:
    - Single quotes should prevent the shell from interpreting any metacharacters inside the quotes.
    - Double quotes should prevent metacharacters from being interpreted, except for `$`.

### Bonus Part

1. **Wildcards**: Implement support for wildcards (`*`) to match files and directories in the current working directory.

---

