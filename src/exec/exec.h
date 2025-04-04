#ifndef MS_EXEC_H
#define MS_EXEC_H

enum e_std_fd
{
	STDIN = 0,
	STDOUT,
	STDERR,
};

bool	ms_exec_init(struct t_shell *sh);
bool	ms_exec_go(struct t_shell *sh);

#endif //#ifndef MS_EXEC_H
