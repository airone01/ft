<div align="center">
	<img src="https://github.com/ayogun/42-project-badges/raw/main/covers/cover-minishell.png" />
</div>

## Build

### Whole project

```sh
make
```

## Authorized external functions

> readline, rl_clear_history, rl_on_new_line,
> rl_replace_line, rl_redisplay, add_history,
> printf, malloc, free, write, access, open, read,
> close, fork, wait, waitpid, wait3, wait4, signal,
> sigaction, sigemptyset, sigaddset, kill, exit,
> getcwd, chdir, stat, lstat, fstat, unlink, execve,
> dup, dup2, pipe, opendir, readdir, closedir,
> strerror, perror, isatty, ttyname, ttyslot, ioctl,
> getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
> tgetnum, tgetstr, tgoto, tputs


## Simple explaination

Your shell should:

- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Avoid using more than one global variable to indicate a received signal. Consider the implications: this approach ensures that your signal handler will not access your main data structures.
  Be careful. This global variable cannot provide any other information or data access than the number of a received signal.
  Therefore, using "norm" type structures in the global scope is forbidden.
- Not interpret unclosed quotes or special characters which are not required by the subject such as `\` (backslash) or `;` (semicolon).
- Handle `’` (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.
- Handle `"` (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).
- Implement redirections:
  - `<` should redirect input.
  - `>` should redirect output.
  - `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
  - `>>` should redirect output in append mode.
- Implement pipes (`|` character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- Handle environment variables (`$` followed by a sequence of characters) which should expand to their values.
- Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.
- Handle `^C`, `^D` and `^\` which should behave like in bash.
- In interactive mode:
  - `^C` displays a new prompt on a new line.
  - `^D` exits the shell.
  - `^\` does nothing.
- In a blocking command like `cat`:
  - `^C` stops the command and sets the return code to 130.
  - `^D` stops the command successfully (cuts stdin).
  - `^\` quits with `^\Quit (core dumped)`.
- Your shell must implement the following builtins:
  - `echo` with option `-n` (and `-nnnn`, but not `echo -n` or `--n`)
  - `cd` with only a relative or absolute path (we also did `~`)
  - `pwd` with no options
  - `export` with no options (`export HELLO=world`, `export` with sorted output)
  - `unset` with no options (`unset PATH`, ...)
  - `env` with no options or arguments
  - `exit` with no options (`exit 13`, `exit 1 a`, `exit`, ...)
