### list of allowed C functions in 42's Minishell:
```c
// readline :
char    *readline (const char *prompt); 
void    rl_on_new_line(void);
int     rl_replace_line(char *line, int i);
void    rl_redisplay(void);
// history :
void    add_history(char *line);
// string.h :
char    *strerror(int errnum);
// stdio.h :
int     printf(const char *restrict format, ...);
// stdlib.h :
void    *malloc(size_t size);
void    free(void *_Nullable ptr);
void    exit(int status);
char    *getenv(const char *name); 
void    perror(const char *s);
// fcntl.h :
int     open(const char *pathname, int flags, ... /* mode_t mode */ );
// unistd.h :
int     access(const char *pathname, int mode);
ssize_t read(int fd, void buf[.count], size_t count);
ssize_t write(int fd, const void buf[.count], size_t count);
int     close(int fd);
pid_t   fork(void);
char    *getcwd(char buf[.size], size_t size);
int     chdir(const char *path);
int     unlink(const char *pathname);
int     execve(const char *pathname, char *const _Nullable argv[],
               char *const _Nullable envp[]);
int     dup(int oldfd);
int     dup2(int oldfd, int newfd);
int     pipe(int pipefd[2]);
int     isatty(int fd);
cha     *ttyname(int fd);
int     ttyslot(void);
// sys/wait.h :
pid_t   wait(int *_Nullable wstatus);
pid_t   waitpid(pid_t pid, int *_Nullable wstatus, int options);
pid_t   wait3(int *_Nullable wstatus, int options,
              struct rusage *_Nullable rusage);
pid_t   wait4(pid_t pid, int *_Nullable wstatus, int options,
              struct rusage *_Nullable rusage);
// signal.h :
void    (*signal(int sig, void (*func)(int)))(int);
int     sigaction(int signum,
                  const struct sigaction *_Nullable restrict act,
                  struct sigaction *_Nullable restrict oldact);
int     sigemptyset(sigset_t *set);
int     sigaddset(sigset_t *set, int signum);
int     kill(pid_t pid, int sig);
// sys/stat.h :
int     stat(const char *restrict pathname,
             struct stat *restrict statbuf);
int     fstat(int fd, struct stat *statbuf);
int     lstat(const char *restrict pathname,
              struct stat *restrict statbuf);
// dirent.h :
DIR     *opendir(const char *name);
dirent  *readdir(DIR *dirp);
int     closedir(DIR *dirp);
// ioctl.h :
int     ioctl(int fildes, int request, ... /* arg */);
int     tcgetattr(int fd, struct termios *termios_p);
int     tcsetattr(int fd, int optional_actions,
                  const struct termios *termios_p);
// curser.h term.h :
int     tgetent(char *bp, const char *name);
int     tgetflag(const char *id);
int     tgetnum(const char *id);
char    *tgetstr(const char *id, char **area);
char    *tgoto(const char *cap, int col, int row);
int     tputs(const char *str, int affcnt, int (*putc)(int));
```

### tree view of used external C functions:
```c

```

