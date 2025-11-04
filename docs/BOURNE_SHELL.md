### CDPATH
A colon-separated list of directories used as a search path for the `cd` builtin command.

### HOME
The current user’s home directory; the default for the `cd` builtin command.
The value of this variable is also used by tilde expansion (see Tilde Expansion).

### IFS
A list of characters that separate fields;
used when the shell splits words as part of expansion.

### MAIL
If this parameter is set to a filename or directory name and the [[#MAILPATH]] variable is not set, Bash informs the user of the arrival of mail in the specified file or Maildir-format directory.

### MAILPATH
A colon-separated list of filenames which the shell periodically checks for new mail. Each list entry can specify the message that is printed when new mail arrives in the mail file by separating the filename from the message with a ‘?’. When used in the text of the message, `$_` expands to the name of the current mail file.

### OPTARG
The value of the last option argument processed by the `getopts` builtin.

### OPTIND
The index of the last option argument processed by the `getopts` builtin.

### PATH
A colon-separated list of directories in which the shell looks for commands. A zero-length (null) directory name in the value of PATH indicates the current directory. A null directory name may appear as two adjacent colons, or as an initial or trailing colon.

### PS1
The primary prompt string. The default value is ‘\s-\v\$ ’. See Controlling the Prompt, for the complete list of escape sequences that are expanded before [[#PS1]] is displayed.

### PS2
The secondary prompt string. The default value is ‘> ’. [[#PS2]] is expanded in the same way as [[#PS1]] before being displayed.
