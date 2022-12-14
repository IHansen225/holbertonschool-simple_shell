#include "hsh.h"

/**
 * function_caller - if path is a valid command, this function
 * starts the parent process and calls the child process to execute it.
 * @path: is the name of the command.
 * @args: are the arguments of the command
 *
 * Return: Always the pid process.
 */
int function_caller(char *path, char *args[])
{
	pid_t pid;
	int child_status, aux_exit = 0;

	pid = fork();
	if (pid == -1)
		perror("Error:");
	else if (pid > 0) /* parent process */
	{
		waitpid(pid, &child_status, 0);
		aux_exit = WEXITSTATUS(child_status);
	}
	else    /* child process */
		execve(path, args, environ), close(0);
	return (aux_exit);
}
/**
 * dir_generator - this function make a new string linking
 * the path with the user's command
 * @s1: is the path.
 * @s2: is the user's command.
 *
 * Return: The new string.
 */
char *dir_generator(char *s1, char *s2)
{
	int i, j, len1, len2;
	char *newstr;

	i = j = len1 = len2 = 0;
	while (s1[len1++] != '\0')
		;
	while (s2[len2++] != '\0')
		;
	newstr = malloc(len1 + len2 + 2);
	if (newstr == NULL)
		return (NULL);
	while (s1[i] != '\0')
		newstr[i] = s1[i], i++;
	newstr[i++] = '/';
	while (s2[j] != '\0')
		newstr[i] = s2[j], i++, j++;
	newstr[i++] = '\0';
	return (newstr);
}

/**
 * check_existance - this function check if name
 * it's a valid command.
 * @paths: are the paths of the PATH variable.
 * @nm: is the command.
 * @pgn: is the name of the program.
 * @pcp: it's a pointer to the path's number.
 * @stat: is the stat of exit.
 *
 * Return: a string with the full command path, or NULL
 * if name it's a invalid command.
 */
char *check_existance(char *paths[], char *nm, char *pgn, int *pcp, int *stat)
{
	char *dir_buf = NULL;
	int flag = 0, i = 0, j = 0;

	if (access(nm, F_OK) == 0) /* if name it's a full path */
	{
		while (nm[++i])
			;
		dir_buf = malloc(i + 1);
		for (i = 0; nm[i]; i++)
			dir_buf[i] = nm[i];
		dir_buf[i] = '\0';
		return (dir_buf);
	}
	while (((!flag) && (i < *pcp)) && (paths != NULL))
	{
		dir_buf = dir_generator(paths[i++], nm);
		flag = ((access(dir_buf, F_OK) == 0) ? 1 : 0); /* flag changes when match */
		if (!flag)
			free(dir_buf); /* free the memory if not a match */
	}
	if (!flag) /* if flag it's zero, the command was not valid */
	{
		i = 0;
		*stat = 127;
		while (pgn[i++])
			;
		i--;
		write(2, pgn, i);
		write(2, ": 1: ", 5);
		while (nm[j++])
			;
		j--;
		write(2, nm, j);
		write(2, ": not found", 11); /* cambiar por 11 */
		write(2, "\n", 1);
		return (NULL);
	}
	else
		return (dir_buf);
}

/**
 * args_isolator - this function make the array
 * of arguments
 * @input: is the user'input.
 * @arc: is a ponter to the number of arguments.
 *
 * Return: an array of pointers with the arguments,
 * or NULL if fall.
 */
char **args_isolator(char *input, int *arc)
{
	int i, j = 0, ac = 1;
	char **args, *ps;

	for (i = 0; input[i]; i++)
		ac = ((input[i] == ' ') ? ac + 1 : ac); /*number of arguments*/
	args = malloc(sizeof(char *) * (ac + 1));
	if (!args)
		return (NULL);
	ps = strtok(input, " "); /* token input */
	while (ps)
		args[j++] = ps, ps = strtok(NULL, " "); /* copy */
	args[j++] = ps;                             /* the arguments */
	*arc = ac;
	return (args); /*the final array */
}

/**
 * env_reader - this function prints the enviroment variables.
 *
 * Return: always void.
 */
void env_reader(void)
{
	int i = 0, j = 0;

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; environ[i][j]; j++)
			;
		write(1, environ[i], j + 1);
		write(1, "\n", 1);
	}
}
