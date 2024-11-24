# Summary of [bashref-2.5a.pdf](https://mirror.math.princeton.edu/pub/oldlinux/Linux.old/Ref-docs/manual%20Bash/bashref-2.5a.pdf)
Bash is left-to-right evaluation of commands / expression.
## Terminology
- blanks = `\t, ' '` (tab and space)
- metacharacters (word delimiter) = a blank or `|, &, ;, (, ), <, >`
- (control) operators = `\n, ||, &&, &, ;, ;;, (, )`
- (redirection) operators = `<, >, <<, >>`
- word = All characters exept the operators.
## Quoting
#### 'single' :
- string literal
- `\'` escapes `'`
#### "double" :
- string literal unless `&\`
- `$` is an environment variable
- `$()` is a substitution
- `$(())` or `$[]` is an arithmetic sequence
- `${}` is parameter expansion
- `\` is interpreted literal exept if the next character is `$"'\`
#### $'ANSI-C' :
- string literal but `\` escapes `abefnrtv\`, `[0-7]` and `x[0-9a-f]`
- `abefnrtv\` see man ASCII
- `\[0-7]` puts the octal ASCII value.
- `\x[0-9a-f]` puts the hexa-decimal ASCII value.
- will convert to single quote as if the `$` has not been there

## Command execution
#### Simple commands
- Sequence of words separated by blanks.
- First word being the command, the rest are it's arguments.
- Returns wait()/waitpid()'s stat_loc integer. Or 128+n if the command was terminated by signal n
#### List of commands
- Sequence of simple commands separated by one of the following control operators:
  1. `;` shell waits for previous command to finish.  
  2. `&` shell doesn't wait. Will execute following command asynchronous in the background. Always returns 0. Uses `jobcontrol`. In case of no redirections stdin will be from /dev/null
  3. `&&` shell will execute 1st command, wait, if non 0 exit status: don't execute the 2nd command.
  4. `||` shell will execute 1st command, wait, if non 0 exit status: execute the 2nd command.
`&&` and `||` return the exit status from last command that executed.
#### Pipelines
- Sequence of simple commands, separated by `|`
- if the leading command is `&`, the shell won't wait for the command in the pipeline to complete.
as soon as the leading command
- each command in a pipeline is a subshell.
- the exit status of a pipeline is the exit status of the last command

#### Looping constructs (non-interactive mode)
`until, while, for` loops are not supported.

#### Conditional constructs (non-interactive mode)
- `if, case, select`
- `((`arithmetic expression`))`
- `[[`tilde-, parameter- and variable-, arithmetic expansion,\
    command- and process substitution,\
    quote removal`]]`
are not supported.

#### Grouping
- `( list )`
- `{ list; }` `{}` be separated by blanks.
- stdin/stdout of each command in list can be redirected to/from one stream.
#### Functions (non-interactive mode)
word+`()`+`{ command-list; }` not supported.
#### Shell parameters
- An entity with a name that stores values (number, string or array)
- A parameter is set once assigned a value. NULL is a valid value.
- The builtin command `unset` can be used to unset the parameter.
- Optional attributes controlled by `declare` builtin.
- _name_`=[`tilde-, parameter- and variable-, arithmetic expansion,\
    command- and process substitution`]`
- word splitting is not performed.

