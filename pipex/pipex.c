#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

//PIPEX
//Must execute ./pipex file1 cmd1 cmd2 file2
//MUst behave < file1 cmd1 | cmd2 file2

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
			child_process(av, fd, envp);
		parent_process(av, fd, envp);
	}
	write (1, "Not Valid! Try ./pipex file1 cmd1 cmd2 file2\n", 45);
	return (0);
}

void	child_process(char **av, int fd, char const **envp)
{
	int fd;

	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
		perror("An error ocurred with opening the fd in child\n");
	dup2(fd[1], stdout);
	dup2(av[1], stdin);
	close(fd[0]);
	execute(av[1], envp);
}

void	parent_process(char **av, int fd, char const **envp)
{
	int fd;

	fd = open(av[4], O_RDWR, 0777);
	if (fd == -1)
		perror("An error ocurred with opening the fd in parent\n");
	dup2(fd[0], stdin);
	dup2(av[4], stdout);
	close(fd[1]);
	execute(av[4], envp);
}

void	execute(char const **av, char const **envp)
{
	if (!av || !envp)
		return ;

	execve();
}
