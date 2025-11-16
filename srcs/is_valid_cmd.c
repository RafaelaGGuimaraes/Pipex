#include "pipex.h"

char	*is_valid_cmd(char *cmd, char **paths)
{
	int		index;
	char	*true_temp;
	char	*true_cmd;

	index = 0;
	while (paths[index])
	{
		true_temp = ft_strjoin(paths[index], "/");
		true_cmd = ft_strjoin(true_temp, cmd);
		if (access(true_cmd, F_OK | X_OK) == 0)
		{
			free(true_temp);
			return (true_cmd);
		}
		else
		{
			free(true_cmd);
			free(true_temp);
		}
		index++;
	}
	return (NULL);
}