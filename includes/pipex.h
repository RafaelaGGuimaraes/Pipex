#ifndef pipex_h
# define pipex_h

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../LIBFT_/libft.h"

char	*is_valid_cmd(char *cmd, char **paths);
int	free_splits(char *normal, char **sp1, char **sp2, char **sp3);
char	*find_path(char *cmd, char **paths);

#endif /* pipex_h */