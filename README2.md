Hi!
The readline library was not working on MacOS (Ventura), so I had to install using brew, as follow:

``` brew install readline ```

 I had to add manually this flags to the makefile (line 56), but we need to check how this will work at 42 Mac.

```
export LDFLAGS="-L/opt/homebrew/opt/readline/lib"
export CPPFLAGS="-I/opt/homebrew/opt/readline/include"
```
-------------

POINTS TO DISCUSS:


1. **Test Files Addition**: I've added test files for functionalities like `cd`, `echo`, `export`, `mkdir`, `pipe`, `random`, `mkdir`, and `unset`. These tests will be crucial in validating our project. Feel free to contribute additional tests.

2. **Handling Memory Leaks**: To address memory leaks, particularly those related to `readline`, it's recommended to create a suppression file (e.g., `readline_supp_file`). After removing identifiable leaks, this file should be saved in the `./minishell` directory. To run Valgrind with this suppression, use:

    ```bash
    valgrind --suppressions=readlinesupp_file --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes ./minishell
    ```