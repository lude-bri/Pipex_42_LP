//UTILS.C MANUAL

/*
	ft_close

	This function closes both file descriptors in the array `fd`.
	- Parameters:
		- `fd`: A pointer to an array of two file descriptors, typically used for a pipe.
	
	- This function is useful to close both ends of the pipe when they are no longer needed.
*/

/*
	ft_free

	This function frees a dynamically allocated array of strings, typically created by `ft_split`.
	- Parameters:
		- `str`: A double pointer to an array of strings, where each string was dynamically allocated.
	
	- The function iterates through the array and frees each string, then frees the array itself.
*/

/*
	find_path

	This function locates the full path of a given command by searching the `PATH` environment variable.
	- Parameters:
		- `cmd`: The command for which to find the full path.
		- `envp`: The environment variables passed to the process, where `PATH` is expected to be found.

	- The function extracts the `PATH` variable from `envp` and splits it into individual directories.
	- For each directory, it concatenates the command (`cmd`) and checks if the file exists and is executable using `access`.
	- If a valid path is found, the full path is returned. Otherwise, `NULL` is returned.

	- Memory for the split directories and constructed paths is dynamically allocated and freed after use.
*/

/*
	execute

	This function executes a command by locating its full path and passing the arguments and environment variables to `execve`.
	- Parameters:
		- `av`: The command to be executed (e.g., "ls -l").
		- `envp`: The environment variables.
		- `fd`: The file descriptors for the pipe.

	- The function splits the command string into individual arguments using `ft_split`.
	- It then calls `find_path` to locate the full path of the command.
		- If the path is not found, it prints an error message and exits.
	- If `execve` fails, the function cleans up by freeing allocated memory and closing file descriptors before exiting.
*/
