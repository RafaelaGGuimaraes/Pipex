/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafagg <rafagg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:52:19 by rgomes-g          #+#    #+#             */
/*   Updated: 2025/11/16 17:24:53 by rafagg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	clean(char *normal)
{
	if (normal)
		free(normal);
}

int	free_splits(char *normal, char **sp1, char **sp2, char **sp3)
{
	int	index;

	clean(normal);
	if (sp1)
	{
		index = 0;
		while (sp1[index])
			free(sp1[index++]);
		free(sp1);
	}
	if (sp2)
	{
		index = 0;
		while (sp2[index])
			free(sp2[index++]);
		free(sp2);
	}
	if (sp3)
	{
		index = 0;
		while (sp3[index])
			free(sp3[index++]);
		free(sp3);
	}
	return (1);
}

char	*find_path(char *cmd, char **paths)
{
	char	*true_temp;
	char	*true_path;
	int		index;

	index = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	while (paths[index])
	{
		true_temp = ft_strjoin(paths[index], "/");
		if (!true_temp)
			return (NULL);
		true_path = ft_strjoin(true_temp, cmd);
		free(true_temp);
		if (!true_path)
			return (NULL);
		if (access(true_path, F_OK | X_OK) == 0)
			return (true_path);
		free(true_path);
		index++;
	}
	return (NULL);
}
