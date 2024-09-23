//UNTILS BONUS MANUAL

/*
	ft_close

	This function closes two file descriptors, typically used for pipes.
	
	- Parameters:
		- `fd`: A pointer to an array of two file descriptors.
	
	- It closes both the reading (`fd[0]`) and writing (`fd[1]`) ends of the pipe.
	- This function is useful for ensuring proper cleanup of resources once the pipe is no longer needed.
*/

/*
	ft_free

	This function frees a dynamically allocated array of strings, usually created by functions like `ft_split`.

	- Parameters:
		- `str`: A pointer to an array of strings (char**).
	
	- The function iterates through the array and frees each string.
	- Once all strings are freed, it frees the array itself.
	- This ensures that memory leaks are avoided by releasing the memory associated with the array and its contents.
*/

/*
	fd_open

	This function opens a file and returns its file descriptor based on the provided mode.

	- Parameters:
		- `file`: The name or path of the file to be opened.
		- `n`: The mode in which the file should be opened.
			- If `n == 1`, the file is opened for writing, creating it if it doesn’t exist, and truncating it if it does.
			- If `n == 2`, the file is opened for appending.
	
	- The file is opened with permission mode `0777`, allowing full read, write, and execute permissions.
	- If the file cannot be opened, the function exits the program with `EXIT_SUCCESS`.
	- Returns the file descriptor of the opened file.
*/

/*
	find_path

	This function searches for the full path of a given command by looking through the directories in the `PATH` environment variable.

	- Parameters:
		- `cmd`: The command to search for.
		- `envp`: The environment variables passed to the process, which contain the `PATH`.
	
	- The function extracts the `PATH` environment variable, splits it into individual directories, and appends the command name to each directory.
	- It uses `access` to check if the command exists and is executable in any of the directories.
	- If a valid path is found, the function returns the full path.
	- If no valid path is found, it frees the allocated memory and returns `NULL`.
	- This function helps in locating the command in any of the directories listed in the `PATH`.
*/

/*
	execute

	This function executes a command by locating its full path and passing the arguments and environment variables to `execve`.

	- Parameters:
		- `av`: The command to be executed, typically passed as a string (e.g., "ls -l").
		- `envp`: The environment variables passed to the process.
		- `fd`: An array of file descriptors, typically for a pipe.

	- The function splits the command string into individual arguments using `ft_split`.
	- It then calls `find_path` to locate the full path of the command.
		- If the path is not found, an error message is printed, resources are freed, and the program exits with `EXIT_NOTFOUND`.
	- If the command path is found, `execve` is used to execute the command with the given arguments and environment.
	- If `execve` fails, the function frees the allocated memory, closes file descriptors, and exits with `EXIT_FAILURE`.
*/

