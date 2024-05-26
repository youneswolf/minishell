#include "../minishell.h"
void    redirect_append(int fd)
{
	int i;

	if (fd == -1)
	{
		perror("Error opening file");
	}
	i = dup2(fd, STDOUT_FILENO);
	if (i == -1)
	{
		perror("Error duplica33ting file descriptor");
		close(fd);
	}
}