/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:38:27 by luigi             #+#    #+#             */
/*   Updated: 2024/06/27 15:39:05 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//define header
#ifndef PIPEX_H
# define PIPEX_H

//define macros
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_MISUSE 2
# define EXIT_NOTEXEC 126
# define EXIT_NOTFOUND 127
# define EXIT_INVALID 128

//define libs
# include "../lib/libft_42/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

//functions
char	*find_path(char *cmd, char **envp);
void	child_process(char **av, int *fd, char **envp);
void	parent_process(char **av, int *fd, char **envp);
void	main_process(char **av, char **envp);
void	execute(char *av, char **envp, int *fd);
void	ft_close(int *fd);
void	ft_free(char **str);
int		fd_open(char *file, int n);
void	ft_close(int *fd);

#endif
