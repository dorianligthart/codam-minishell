# The following environment variables shall affect the execution of sh:
### ENV
This variable, when and only when an interactive shell is invoked, shall be subjected to parameter expansion (see Section 2.6.2, Parameter Expansion) by the  shell,  and  the
resulting value shall be used as a pathname of a file containing shell commands to execute in the current environment.  The file need not be executable. If the expanded value
of  ENV  is not an absolute pathname, the results are unspecified.  ENV shall be ignored if the real and effective user IDs or real and effective group IDs of the process are
different.

### FCEDIT
This variable, when expanded by the shell, shall determine the default value for the -e editor option's editor option-argument. If FCEDIT is null or unset, ed shall  be  used as the editor.

### HISTFILE
Determine  a  pathname  naming  a command history file. If the HISTFILE variable is not set, the shell may attempt to access or create a file .sh_history in the directory re‐
ferred to by the HOME environment variable. If the shell cannot obtain both read and write access to, or create, the history file, it shall use an unspecified mechanism  that
allows the history to operate properly.  (References to history ‘‘file'' in this section shall be understood to mean this unspecified mechanism in such cases.) An implementa‐
tion  may choose to access this variable only when initializing the history file; this initialization shall occur when fc or sh first attempt to retrieve entries from, or add
entries to, the file, as the result of commands issued by the user, the file named by the ENV variable, or implementation-defined system start-up files.  Implementations  may
choose to disable the history list mechanism for users with appropriate privileges who do not set HISTFILE; the specific circumstances under which this occurs are implementa‐
tion-defined.  If more than one instance of the shell is using the same history file, it is unspecified how updates to the history file from those shells interact. As entries
are deleted from the history file, they shall be deleted oldest first. It is unspecified when history file entries are physically removed from the history file.
### HISTSIZE
Determine a decimal number representing the limit to the number of previous commands that are accessible. If this variable is unset, an unspecified default  greater  than  or
equal to 128 shall be used. The maximum number of commands in the history list is unspecified, but shall be at least 128. An implementation may choose to access this variable
only  when initializing the history file, as described under HISTFILE.  Therefore, it is unspecified whether changes made to HISTSIZE after the history file has been initial‐
ized are effective.

### HOME
Determine the pathname of the user's home directory. The contents of HOME are used in tilde expansion as described in Section 2.6.1, Tilde Expansion.

### LANG
Provide a default value for the internationalization variables that are unset or null. (See the Base Definitions volume of  POSIX.1‐2017,  Section  8.2,  Internationalization
Variables for the precedence of internationalization variables used to determine the values of locale categories.)

### LC\_ALL
If set to a non-empty string value, override the values of all the other internationalization variables.

### LC\_COLLATE
Determine the behavior of range expressions, equivalence classes, and multi-character collating elements within pattern matching.

### LC\_CTYPE
Determine  the  locale  for the interpretation of sequences of bytes of text data as characters (for example, single-byte as opposed to multi-byte characters in arguments and
input files), which characters are defined as letters (character class alpha), and the behavior of character classes within pattern matching.

### LC\_MESSAGES
Determine the locale that should be used to affect the format and contents of diagnostic messages written to standard error.

### MAIL
Determine a pathname of the user's mailbox file for purposes of incoming mail notification. If this variable is set, the shell shall inform the user if the file named by  the
variable is created or if its modification time has changed. Informing the user shall be accomplished by writing a string of unspecified format to standard error prior to the
writing  of  the  next  primary  prompt  string. Such check shall be performed only after the completion of the interval defined by the MAILCHECK variable after the last such
check. The user shall be informed only if MAIL is set and MAILPATH is not set.

### MAILCHECK
Establish a decimal integer value that specifies how often (in seconds) the shell shall check for the arrival of mail in the files specified by the  MAILPATH  or  MAIL  variables.
The default value shall be 600 seconds. If set to zero, the shell shall check before issuing each primary prompt.
