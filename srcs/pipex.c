/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-g <rgomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:20:38 by rgomes-g          #+#    #+#             */
/*   Updated: 2025/11/19 14:20:40 by rgomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../LIBFT_/libft.h"

static int	execute_command(char *cmd, char **envp)
{
	char	*paths_temp;
	char	**paths;
	char	*path;
	int		index;
	char	**commands;

	index = 0;
	while (envp[index] && (!ft_strnstr(envp[index], "PATH", 4)))
		index++;
	paths_temp = ft_strdup(envp[index] + 5);
	if (!paths_temp)
		return (1);
	paths = ft_split(paths_temp, ':');
	if (!paths)
		return (free_splits(paths_temp, NULL, NULL, NULL));
	commands = ft_split(cmd, ' ');
	if (!commands)
		return (free_splits(paths_temp, paths, NULL, NULL));
	path = find_path(commands[0], paths);
	if (!path)
		return (free_splits(paths_temp, paths, commands, NULL));
	if (execve(path, commands, NULL) == -1)
		free(path);
	exit(free_splits(paths_temp, paths, commands, NULL));
	return (1);
}

static int	close_descriptors(int *pipefd, int *pipefd2)
{
	if (pipefd)
	{
		close(pipefd[1]);
		close(pipefd[0]);
	}
	if (pipefd2)
	{
		close(pipefd2[1]);
		close(pipefd2[0]);
	}
	return (1);
}

static void	parent_process(char **argv, char **envp, int *pipefd)
{
	int	file_output;

	close(pipefd[1]);
	file_output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_output == -1)
	{
		close(pipefd[0]);
		exit(1);
	}
	if (dup2(file_output, STDOUT_FILENO) == -1)
	{
		close(file_output);
		close(pipefd[0]);
		exit(1);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[1]);
		close(pipefd[0]);
		exit(1);
	}
	close(pipefd[0]);
	close(file_output);
	execute_command(argv[3], envp);
}

static void	child_process(char **argv, char **envp, int *pipefd)
{
	int	file_input;

	close(pipefd[0]);
	file_input = open(argv[1], O_RDONLY);
	if (file_input == -1)
	{
		close(pipefd[1]);
		exit(1);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(file_input);
		close(pipefd[1]);
		exit(1);
	}
	if (dup2(file_input, STDIN_FILENO) == -1)
	{
		close(file_input);
		close(pipefd[1]);
		exit(1);
	}
	close(pipefd[1]);
	close(file_input);
	execute_command(argv[2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	id;
	int	id2;
	int	pipefd[2];

	if (argc != 5)
	{
		ft_putendl_fd("How to use: ./pipex [input] [cmd1] [cmd2] [output]", 2);
		return (1);
	}
	if (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) == -1)
    {
        perror(argv[4]);
        return (1);
    }
	if (pipe(pipefd) == -1)
		return (1);
	id = fork();
	if (id == -1)
		return (close_descriptors(pipefd, NULL));
	if (id == 0)
		child_process(argv, envp, pipefd);
	id2 = fork();
	if (id2 == -1)
		return (close_descriptors(pipefd, NULL));
	if (id2 == 0)
		parent_process(argv, envp, pipefd);
	close_descriptors(pipefd, NULL);
	waitpid(id, NULL, 0);
	waitpid(id2, NULL, 0);
	return (0);
}
