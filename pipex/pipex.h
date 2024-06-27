#ifndef PIPEX_H
# define PIPEX_H
# define stdout stdout

# include "./libft_42_LP/libft_42/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>

char	*find_path(char *cmd, char **envp);
void	child_process(char **av, int fd, char const **envp);
void	parent_process(char **av, int fd, char const **envp);
void	execute(char *av, char const **envp);

#endif
