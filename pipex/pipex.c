#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

//PIPEX
//Must execute ./pipex file1 cmd1 cmd2 file2
//MUst behave < file1 cmd1 | cmd2 file2


void	execute(const char *pathname, char const **av, char const **envp)
{

	if (!path || !av || !envp)
		return ;

}

void	child_process(char **av, pid_t pid, char const **envp)
{
	int fd;
	char *path;

	path = "/usr/bin/";
	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
		perror("An error ocurred with opening the fd in child\n");
	dup2(fd[1], stdout);
	dup2(filein, stdin);
	close(fd[0]);
	execute(path, av[1], envp);
}

void	parent_process(char **av, pid_t pid, char const **envp)
{
	int fd;

	char *path;

	path = "/usr/bin/";
	fd = open(av[4], O_RDWR, 0777);
	if (fd == -1)
		perror("An error ocurred with opening the fd in parent\n");
	dup2(fd[0], stdin);
	dup2(outfile, stdout);
	close(fd[1]);
	execute(path, av[4], envp);
}

int main (int ac, char **av, char const **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac == 5)
	{
		pipe(fd);
		if (pipe(fd) == -1)
			perror("An error ocurred with opening the pipe\n");
		pid = fork();
		if (pid == -1)
			perror("An error occured with fork\n");
		else if (pid == 0)
			child_process(av, pid, envp);
		parent_process(av, pid, envp);
	}
	write (1, "Not Valid! Try ./pipex infile cmd1 cmd2 outfile\n", 47);
	return (0);
}
