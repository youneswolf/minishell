#include "minishell.h"
void redirect_input(int fd)
{
	int	i;

	if (fd == -1)
	{
		perror("Error opening file");
	}
	i = dup2(fd, STDIN_FILENO);
	if (i == -1)
	{
		perror("Error dupli33cating file descriptor");
		close(fd);
	}
}