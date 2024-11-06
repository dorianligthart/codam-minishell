# codam-minishell
[subject.pdf](https://cdn.intra.42.fr/pdf/pdf/47172/en.subject.pdf)

### note:
This project is simplified bash in interactive mode. It does not make use of a parse tree, it simply converts input into tokens, then handles the environment variables, heredoc, pipes, redirects, commands. 

### list of allowed external functions:
```c
char    *readline (const char *prompt); 
void    rl_on_new_line(void);
int     rl_replace_line(char *line, int i);
void    rl_redisplay(void);
void    add_history(char *line);

int     printf(const char *restrict format, ...);
void    *malloc(size_t size);
void    free(void *_Nullable ptr);
int     open(const char *pathname, int flags, ... /* mode_t mode */ );
int     access(const char *pathname, int mode);
ssize_t read(int fd, void buf[.count], size_t count);
ssize_t write(int fd, const void buf[.count], size_t count);
int     close(int fd);
pid_t   fork(void);
pid_t   wait(int *_Nullable wstatus);
pid_t   waitpid(pid_t pid, int *_Nullable wstatus, int options);
pid_t   wait3(int *_Nullable wstatus, int options,
                     struct rusage *_Nullable rusage);
pid_t   wait4(pid_t pid, int *_Nullable wstatus, int options,
                   struct rusage *_Nullable rusage);

void    (*signal(int sig, void (*func)(int)))(int);
int     sigaction(int signum,
                  const struct sigaction *_Nullable restrict act,
                  struct sigaction *_Nullable restrict oldact);
int     sigemptyset(sigset_t *set);
int     sigaddset(sigset_t *set, int signum);
int     kill(pid_t pid, int sig);
void    exit(int status);
char    *getcwd(char buf[.size], size_t size);
int     chdir(const char *path);
int     stat(const char *restrict pathname,
             struct stat *restrict statbuf);
int     fstat(int fd, struct stat *statbuf);
int     lstat(const char *restrict pathname,
              struct stat *restrict statbuf);

int     unlink(const char *pathname);
int     execve(const char *pathname, char *const _Nullable argv[],
               char *const _Nullable envp[]);
int     dup(int oldfd);
int     dup2(int oldfd, int newfd);
int     pipe(int pipefd[2]);

// directories:
DIR     *opendir(const char *name);
dirent  *readdir(DIR *dirp);
int     closedir(DIR *dirp);

// tty:
int     isatty(int fd);
cha     *ttyname(int fd);
int     ttyslot(void);

// misc:
int     ioctl(int fildes, int request, ... /* arg */);
char    *getenv(const char *name); 
int     tcgetattr(int fd, struct termios *termios_p);
int     tcsetattr(int fd, int optional_actions,
                     const struct termios *termios_p);

// ncurses:
char PC;
char * UP;
char * BC;
short ospeed;

int     tgetent(char *bp, const char *name);
int     tgetflag(const char *id);
int     tgetnum(const char *id);
char    *tgetstr(const char *id, char **area);
char    *tgoto(const char *cap, int col, int row);
int     tputs(const char *str, int affcnt, int (*putc)(int));

// error handling:
void    perror(const char *s);
char    *strerror(int errnum);
```

### disallowed filename characters in Linux:
- \# pound
- \% percent
- \& ampersand
- \{ left curly bracket
- \} right curly bracket
- \\ back slash
- \< left angle bracket
- \> right angle bracket
- \* asterisk
- \? question mark
- \/ forward slash
- \  blank spaces
- \$ dollar sign
- \! exclamation point
- \' single quotes
- \" double quotes
- \: colon
- \@ at sign
- \+ plus sign
- \` backtick
- \| pipe
- \= equal sign
- \emojis
- \alt codes

### this shell compared to bash:
- no program options (bash has many)
- no &, &&, ||, ${}, $(), (), *, `, !, !!, ;, \\, =(arrays).
- no keywords like 'if'.
- no arithmatic operations like +, -, *, %, **, ++, --.
- limited builtin commands, this shell has: [echo [-n], cd, pwd, export, unset,
  env, exit]
- supports: [<, >, <<, >>, "$...", $?, $$, |]
- alters behaviour of [SIGINT, SIGQUIT]
