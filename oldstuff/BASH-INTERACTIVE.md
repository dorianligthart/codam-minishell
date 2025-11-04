# Summary of GNU bash
Bash is left-to-right evaluation of expressions and execution of commands.
## Terminology
- blanks = `\t, ' '` (tab and space)
- metacharacters (word delimiter) = `IFS(default: \n), |, &, ;, (, ), <, >`
- (control) operators = `\n, ||, &&, &, ;, |, |&, (, )` which give logic to program execution.
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
- `\` is interpreted literal exept if the next character is `$`, `"`, `'`, or `\`.
#### $'ANSI-C' :
- string literal but `\` escapes `abefnrtv\`, `[0-7]` and `x[0-9a-f]`
- `abefnrtv\` see man ASCII.
- `\[0-7]` puts the octal ASCII value.
- `\x[0-9a-f]` puts the hexa-decimal ASCII value.
- will convert to single quote as if the `$` has not been there

## Command execution
#### Simple commands
- Sequence of words separated by blanks.
- First word being the command, the rest are it's arguments.
- Returns wait()/waitpid()'s stat\_loc integer. Or 128+n if the command was terminated by signal n
#### List of commands
Sequence of simple commands separated by one of the following control operators:
  1. `;` shell waits for previous command to finish.  
  2. `&` shell doesn't wait. Will execute following command asynchronous in the background. Always returns 0. Uses `jobcontrol`. In case of no redirections stdin will be from /dev/null
  3. `&&` shell will execute 1st command, wait, if non 0 exit status: don't execute the 2nd command.
  4. `||` shell will execute 1st command, wait, if non 0 exit status: execute the 2nd command.

`&&` and `||` return the exit status from last command that executed.
#### Pipelines
- Sequence of simple commands or lists or mixed, separated by `|`
- if the leading command is `&`, the shell won't wait for the command in the pipeline to complete. As soon as the leading command ends it will print `<PID> exited with <EXITCODE>`.
- each command in a pipeline is a subshell.
- the exit status of a pipeline is the exit status of the last command.
#### Redirections
- `>`
- `<`
- `>>`
- `<<`
#### Looping constructs (non-interactive mode)
`until, while, for` loops are not supported.

#### Conditional constructs (non-interactive mode)
- `if`, `case`, `select`, `then`,
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
word+`()`+`{ list; }` not supported.
#### Shell parameters
- An entity with a name that stores values (number, string or array)
- A parameter is set once assigned a value. empty string is a valid value.
- The builtin command `unset` can be used to unset the parameter, to make a variable's
  slot free.
- Optional attributes controlled by `declare` builtin.
- \_name_`=[`tilde-, parameter- and variable-, arithmetic expansion, command- and process substitution`]`
- word splitting is not performed.
## ORDER:
 1. Tokenise
 2. Check for unclosed and validate.
 3. Brace Expansion, `{}`
 4. Tilde Expansion, `~/` becomes `$HOME` but `~user` is path of `user`'s `$HOME`.
 5. Parameter Expansion, `$\_word`
 6. Command Substitution, `$(cmd)` or `cmd`
 7. Arithmetic Expansion, `$((expr))` or `$[expr]`
 8. Process Substitution, `<(list)` or `>(list)`
 3-6. is done traversively from left to right.
 9. Word Splitting
 10. Filename Expansion
 11. Quote Removal


