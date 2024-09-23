//PIPEX BONUS MANUAL

/*
	main

	This program simulates the behavior of Unix pipes with multiple commands. It allows for piping several commands together, starting with input from a file (`file1`) and ending with output to another file (`file2`).

	- Parameters:
		- `ac`: Argument count, representing the number of command-line arguments.
		- `av`: Argument values, an array of strings where each string represents a file or command.
		- `envp`: Environment variables passed to the process.

	- The program requires at least 5 arguments: `file1`, `cmd1`, `cmd2`, ..., `cmdn`, and `file2`.
	- It opens `file1` as the input source and `file2` as the output destination.
	- It sets up piping between the commands and executes each command in sequence.
	- The output from `file1` is fed through a series of commands, with the final result being written to `file2`.
	- If fewer than 5 arguments are provided, it prints an error message and exits.
*/

/*
	main_process

	This function handles the execution of intermediate commands in the pipeline.
	- For each command, it creates a pipe to connect the output of the current command to the input of the next command.
	- It uses `fork()` to create a child process, which runs the current command and sends its output through the pipe.
	- The parent process waits for the child to finish and redirects the input of the next command to the output of the current pipe.

	- Parameters:
		- `av`: The current command to execute.
		- `envp`: Environment variables passed to the process.

	- It sets up the pipe, forks the process, and uses `dup2` to handle input/output redirection.
*/
