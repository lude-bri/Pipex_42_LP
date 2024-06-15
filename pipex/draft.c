#include <stdio.h>
#include <time.h>

//UNDERSTANDING FORKS
int main (int ac, char **av)
{
	int id = fork(); //cria CHILD AND PARENT
	int n;
	if (id == 0) //CHILD
		n = 1;
	else //PARENT
		n = 6;
	if (id != 0) //PARENT WAITS FOR CHILD
		wait ();
 
	int i;
	for (i = n; i < n + 5; i++)
	{
		printf("%d", i);
		fflush(stdout);
	}
	if (id != 0)
		printf("\n");
	return (0);
}





//UNDERSTANDING PIPES
int main (int ac, char **av)
{
	int fd[2];
	//fd[0] - read
	//fd[1] - write
	if (pipe(fd) == -1)
	{
		printf("ERROR WITH OPENING THE PIPE\n");
		return (1);
	}
	int id = fork();
	if (id == -1)
	{
		printf("And error occured with fork\n");
		return (2);
	}
	if (id == 0) //child
	{
		close (fd[0]);
		int x;
		printf("Input a number: ");
		scanf("%d", &x);
		if (write (fd[1], &x, sizeof(int)) == -1)
		{
			printf("An error occured with writing to the pipe\n");
			return (2);
		}
		close(fd[1]);
	}
	else //parent
	{
		close (fd[1]);
		int y;
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			printf("And error occured with reading from pipe\n");
			return (2);
		}
		close (fd[0]);	
	}


	return (0);
}


//UNDERSTANDING PIPEX
int main (int ac, char **av)
{
	int fd[2];
	if (pipe(fd) == -1)
		return (1);

	//CREATE PROCESSES
	
	//FIRST PROCESS : PING
	int pid1 = fork();
	if (pid1 < 0)
		return 2;
	
	if (pid1 == 0) //CHILD
	{
		dup2(fd[1], stdout);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}

	//SECOND PROCESS : GREP
	int pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)
	{
		dup2(fd[0], stdin);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);

	}
	
	close (fd[0]);
	close (fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);

}








































