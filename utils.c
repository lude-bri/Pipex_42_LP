/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:37:37 by luigi             #+#    #+#             */
/*   Updated: 2024/06/27 15:37:40 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free (str[i++]);
	free (str);
}

char	*find_path(char *cmd, char **envp)
{
	char	**full_path;
	char	*half_path;
	char	*path;
	int		i;

	i = 0;
	if (!envp[i])
		return (NULL);
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	full_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (full_path[i])
	{
		half_path = ft_strjoin(full_path[i], "/");
		path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free(full_path), path);
		free(path);
		i++;
	}
	return (ft_free(full_path), NULL);
}

void	execute(char *av, char **envp, int *fd)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		ft_free(cmd);
		ft_putstr_fd("command not found\n", 2);
		ft_close(fd);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free(cmd);
		ft_close(fd);
		exit(EXIT_FAILURE);
	}
}

