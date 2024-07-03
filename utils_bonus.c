/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:19:38 by luigi             #+#    #+#             */
/*   Updated: 2024/07/02 14:24:04 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fd_open(char *file, int n)
{
	int	res;

	if (n == 0)
		res = open(file, O_RDONLY, 0777);
	if (n == 1)
		res = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (n == 2)
		res = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (res == -1)
		exit (0);
	return (res);
}

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


