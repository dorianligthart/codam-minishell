#ifndef MS_EXEC_H
#define MS_EXEC_H

enum e_std_fd
{
	STDIN = 0,
	STDOUT,
	STDERR,
};

bool	ms_initexec(struct t_shell *sh);
bool	ms_exec(struct t_shell *sh);

#endif //#ifndef MS_EXEC_H
