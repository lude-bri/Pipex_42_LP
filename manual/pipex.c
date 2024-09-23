
//PIPEX.C - MANUAL

/*
	main

	This program emulates a simple version of the Unix `pipe` system call. It takes four command-line arguments:
		- `file1`: The input file.
		- `cmd1`: The first command to execute.
		- `cmd2`: The second command to execute.
		- `file2`: The output file.
	
	- The program creates a pipe and forks a child process to execute `cmd1`. The output of `cmd1` is passed through the pipe.
	- The parent process executes `cmd2`, which takes the output of `cmd1` from the pipe and writes the result to `file2`.

	- Parameters:
		- `ac`: The number of command-line arguments.
		- `av`: The array of command-line arguments.
		- `envp`: The environment variables passed to the child and parent processes.
	
	- If the number of arguments is not 5, the program displays an error message and exits.
	
	- The pipe (`fd`) is used to create a communication channel between the child and parent processes.
	- `fork()` is used to create a child process. The child process executes `cmd1`, and the parent process executes `cmd2`.

	- The program handles errors for `pipe`, `fork`, and file operations (e.g., opening files).
*/
/*
	child_process

	This function handles the child process, which executes the first command (`cmd1`).

	- Parameters:
		- `av`: Command-line arguments (to access file1 and cmd1).
		- `fd`: File descriptors for the pipe.
		- `envp`: Environment variables passed to `execve`.
	
	- The child process:
		- Closes the read end of the pipe (`fd[0]`).
		- Opens `file1` (the input file) for reading.
		- Redirects the output (`STDOUT_FILENO`) to the write end of the pipe (`fd[1]`).
		- Redirects the input (`STDIN_FILENO`) to `file1`.
		- Executes `cmd1` using `execve` (via the `execute` function).
	
	- If any file operations (e.g., opening `file1`) fail, an error is printed, and the process exits with `EXIT_FAILURE`.
*/
/*
	parent_process

	This function handles the parent process, which executes the second command (`cmd2`).

	- Parameters:
		- `av`: Command-line arguments (to access file2 and cmd2).
		- `fd`: File descriptors for the pipe.
		- `envp`: Environment variables passed to `execve`.
	
	- The parent process:
		- Closes the write end of the pipe (`fd[1]`).
		- Opens `file2` (the output file) for writing (creates/truncates the file).
		- Redirects the input (`STDIN_FILENO`) to the read end of the pipe (`fd[0]`).
		- Redirects the output (`STDOUT_FILENO`) to `file2`.
		- Executes `cmd2` using `execve` (via the `execute` function).
	
	- If any file operations (e.g., opening `file2`) fail, an error is printed, and the process exits with `EXIT_FAILURE`.
*/
