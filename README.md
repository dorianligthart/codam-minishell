# codam-minishell
[subject.pdf](https://cdn.intra.42.fr/pdf/pdf/47172/en.subject.pdf)

#### definitions:
- meta\_char="|&;()<>"
- ctrl\_operator= '\n', ';', '||', '&&', '&', '|', '|&', '(', ')'
- redirect= '<', '>', '<<', '>>', '|'

####' program flow:
`A => B | C` means token A's next token is either B or C.\
`A = B | C` means token A is either B or C.

- start => cmd | assign | '('
- cmd => arg | quote | ctrl\_operator | redirect
- assign => arg | quote | ctrl\_operator | redirect(weird behaviour)
- '(' => start

- arg = $variable | text(non-meta\_char/non-space\_char)
- quote = '' | "$var" | $''
- end = '\0'

### What Minishell doesn't support (with bash in mind):
- no program options (set builtin or invocation)
- no history(3) syntax. 
- limited quoting, doesn't handle locale specific translation.
- no background/list/compound commands.
- no [coprocesses GNU parallel](https://www.gnu.org/software/bash/manual/html_node/Coprocesses.html).
- no brace, tilde, arithmetic, filename expansion.
- no command/process substitution. 
- no keywords like 'if'.
- no functions.
- no arrays.
- no shell scripts and no argv `$@` or argc `$#`.
- no jobcontrol.
- no comments.

### and what Minishell does support:
- interactive mode.
- syntax: [_command_, <, >, <<, >>, "$...", $?, |]
- builtins = [echo [-n], cd, pwd, export, unset, env, exit]
