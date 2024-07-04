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
//fazer 
#include "../src/pipex.h"

void	main_process(char **av, char **envp);

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		fd_in;
	int		fd_out;

	if (ac >= 5)
	{
		i = 2;
		fd_in = fd_open(av[1], 2);
		fd_out = fd_open(av[ac -1], 1);
		dup2(fd_in, STDIN_FILENO);
		while (i < ac - 2)
			main_process(&av[i++], envp);
		dup2(fd_out, STDOUT_FILENO);
		execute(av[ac - 2], envp, NULL);
	}
	ft_putstr_fd("Error! Try it ./pipex file1 cmd1 cmd2 cmdn cmd3 file2", 2);
}

void	main_process(char **av, char **envp)
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
		execute(*av, envp, fd);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(pid, NULL, 0);
}
