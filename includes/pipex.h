/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-g <rgomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:20:52 by rgomes-g          #+#    #+#             */
/*   Updated: 2025/11/19 14:20:54 by rgomes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef pipex_h
# define pipex_h

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../LIBFT_/libft.h"

char	*is_valid_cmd(char *cmd, char **paths);
int	free_splits(char *normal, char **sp1, char **sp2, char **sp3);
char	*find_path(char *cmd, char **paths);

#endif /* pipex_h */