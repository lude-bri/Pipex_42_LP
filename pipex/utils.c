#include <stdio.h>
#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	// to find path i need to use the envp
	get_env("PATH=", envp);
	
}

char	*get_env(char *name, char **envp)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (!ft_strncmp(envp, name, ft_strlen(name)))
		{
			while (envp[i][j] && envp[i][j] != '=')
				j++;
			path = ft_substr(envp[i], j, (ft_strlen(envp[i]) - j));
		}
		printf("%s\n", path);
	}
	return (path);
}
