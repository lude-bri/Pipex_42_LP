/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:38:06 by luigi             #+#    #+#             */
/*   Updated: 2024/06/27 15:38:09 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//#include "lib/libft_42/libft.h"
//Must execute ./pipex file1 cmd1 cmd2 file2
//MUst behave < file1 cmd1 | cmd2 file2

void	child_process(char **av, int *fd, char **envp);
void	parent_process(char **av, int *fd, char **envp);
void	execute(char *av, char **envp);

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac == 5)
	{
		pipe(fd);
		if (pipe(fd) == -1)
			perror("pipe");
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
			child_process(av, fd, envp);
		parent_process(av, fd, envp);
	}
	else
	{
		ft_putstr_fd("Not Valid! Try ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit (127);
	}
	return (1);
}

void	child_process(char **av, int *fd, char **envp)
{
	int	fd_op;

	close(fd[0]);
	fd_op = open(av[1], O_RDONLY, 0777);
	if (fd_op == -1)
	{
		perror(av[1]);
		exit (127);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_op, STDIN_FILENO);
	execute(av[2], envp);
}

void	parent_process(char **av, int *fd, char **envp)
{
	int	fd_op;

	close(fd[1]);
	fd_op = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_op == -1)
	{
		perror(av[4]);
		exit (127);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_op, STDOUT_FILENO);
	execute(av[3], envp);
}

void	execute(char *av, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_split(av, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[i])
			free (cmd[i++]);
		free(cmd);
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		while (cmd[i])
			free(cmd[i++]);
		exit(EXIT_FAILURE);
	}
}
