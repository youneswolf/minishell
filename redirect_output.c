#include "minishell.h"
void    redirect_output(int fd)
{
	int	i;

	if (fd == -1)
	{
		perror("Error opening file");
	}
	i = dup2(fd, STDOUT_FILENO);
	printf("%d\n",i);
	// close(fd);
	if (i == -1)
	{
		perror("Error ;l file descriptor");
	}
}