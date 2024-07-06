///
///
///
//PIPEX.C - MANUAL
///
///
///
///How to use the manual:
///
///BEGIN - is the begining of the main function
///END - is the end of the main function
///ENTER - meaning that the following lines will be inside the function
///CALL - meaning that the fucntion will me called by the system, will be activated.
///DECLARE - meaning that variables are created
///ATTRIBUTE - meaning that the variable will receive a value
///RETURN - meaning the returning value of that function
///
///
///PROJECT OBJECTIVE
///Pipex simulate the usage of pipes in shell
///
///      ./pipex file1 cmd1 cmd2 file2
///				MUST BEHAVE LIKE
///		  < file1 cmd1 | cmd2 > file2
///
///Functions used in pipex.c

void	child_process(char **av, int *fd, char **envp);
void	parent_process(char **av, int *fd, char **envp);
int		main(int ac, char **av, char **envp);
///
///
int	main(int ac, char **av, char **envp);
///MAIN function
///BEGIN
///DECLARE variable int* called fd, contains 2 files descriptors because pipe uses 2 fdS
///DECLARE variable pid_t called pid, the process identification to work on processes after fork()
///
///ENTER IF our arguments count is equals 5. Which means that everything is correct (.pipex/ file1 cmd1 cmd2 file2)
///		
///		CALL function pipe() to create pipe with the 2 files descriptors given (fd[0] - read / fd[1] - write)
///		ENTER IF during the creation of the pipe something went wrong
///			CALL function perror() to Print error saying "pipe"
///		ATTRIBUTE to variable pid the return value of fork() function, creating thus two processes
///		ENTER IF the pid variable value is equals -1 (error)
///			CALL function perror() to print error saying "fork" with perror function.
///			CALL function ft_close() to close arrays (fd[0] and fd[1])
///		ENTER ELSE IF the pid variable value is equals to 0 (means this is the child process)
///			CALL function child_process();
///		CALL function parent_process();
///		
///ENTER ELSE our arguments count is not equals 5. Which means error
///
///		CALL function ft_putstr_fd() to print in the fd our str "Not Valid..."
///		CALL function exit() to exit the process, returns EXIT_INVALID (1)
///
///RETURN number 1, the standard output
///END
///
///CHILD_PROCESS function
void	child_process(char **av, int *fd, char *envp);
///BEGIN
///DECLARE variable int called fd_op, handle the opening of our file argument
///
///CALL function close() to close the end READ (fd[0]) of the pipe
///ATTRIBUTE to fd_op variable the return value of open() function that will open file1 (av[1]), to read only (O_RDONLY), with all permitions (0777)
///ENTER IF the fd_op value is equal -1 (means that an error occurred during the opening process)
///			CALL function perror() to print error saying the name of the file1 (av[1]) with perror function.
///			CALL function ft_close() to close arrays (fd[0] and fd[1])
///			CALL function exit() to exit the process, returns EXIT_FAILURE (128)
///CALL function dup2() to change the file descriptor of standard output to fd[1], meaning that child will not write to the terminal, but to the pipe's write gate (fd[1])
///CALL function dup2() to change the file descriptor of standard input to fd_op, meaning that child will not read from the terminal, but from the opened file1 (fd_op)
///CALL function execute() to execute the command sended (av[2])
///END
///
///
///PARENT_PROCESS function
///
void	parent_process(char **av, int *fd, char *envp);
///BEGIN
////DECLARE variable int called fd_op, handle the opening of our file argument
///
///CALL function close() to close the end WRITE (fd[1]) of the pipe
///ATTRIBUTE to fd_op variable the return value of open() function that will open file2 (av[4]), to write only (O_WRONLY), if doesnt exit create it (O_CREAT) OR truncate it if there is already something there (O_TRUNC) with all permitions (0777)
///ENTER IF the fd_op value is equal -1 (means that an error occurred during the opening process)
///			CALL function perror() to print error saying the name of the file2 (av[4]) with perror function.
///			CALL function ft_close() to close arrays (fd[0] and fd[1])
///			CALL function exit() to exit the process, returns EXIT_FAILURE (128)
///CALL function dup2() to change the file descriptor of standard input to fd[0], meaning that parent will not read from the terminal, but to the pipe's read gate (fd[0])
///CALL function dup2() to change the file descriptor of standard output to fd_op, meaning that parent will not write to the terminal, but to the opened file2 (fd_op)
///CALL function execute() to execute the command sended (av[3])
///END
///
