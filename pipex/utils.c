#include <stdio.h>
#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**full_path;
	char	*half_path;
	char	*path;
	int		i;

	i = 0;
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
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (full_path[i++])
		free (full_path[i]);
	free (full_path);
	return (0);
}
