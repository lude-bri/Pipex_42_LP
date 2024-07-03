/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:22:22 by luigi             #+#    #+#             */
/*   Updated: 2024/07/02 14:21:42 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	main_process(char **av, char **envp);
void	here_doc(char *limiter, int ac);

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		fd_in;
	int		fd_out;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			i = 3;
			fd_out = fd_open(av[ac - 1], 0);
			here_doc(av[3], ac);
		}
		else
		{
			i = 2;
			fd_in = fd_open(av[1], 0);
			fd_out = fd_open(av[ac -1], 1);
			dup2(fd_in, STDIN_FILENO);
		}
		while (i < ac - 2)
			main_process(av[i++], envp);
		dup2(fd_out, STDOUT_FILENO);
		execute(av[ac - 2], envp);
	}
	ft_putstr_fd("Not Valid!", 2);
}

void	main_process(char *av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_close(fd);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(av, envp, fd);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(pid, NULL, 0);
}

void	here_doc(char *limiter, int ac)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (ac < 6)
		ft_putstr_fd("Not Valid!", 2);
	if (pipe(fd) == -1)
		perror("pipe");
	reader = fork();
	if (!reader)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(0);
			ft_putstr_fd(line, fd[1]);
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(0);
}
