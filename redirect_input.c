#include "minishell.h"
void redirect_input(t_line **line)
{
	t_line *file_name;
	int	fd;
	int	i;

	file_name = *line;
	fd = open(file_name->str, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(0);
	}
	i = dup2(fd, STDIN_FILENO);
	if (i == -1)
	{
		perror("Error duplicating file descriptor");
		close(fd);
		exit(0);
	}
}