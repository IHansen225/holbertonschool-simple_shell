#include "hsh.h"

/**
 * _strcmp - Write a function that compares two strings.
 * @s1: is the first string
 * @s2: is the second string
 *
 * Return: zero if the string are equal, a integer if are diferents.
 */
int _strcmp(char *s1, char *s2)
{
		while (*s1 && *s2 && (*s1 == *s2))
				s1++, s2++;

		return (*s1 - *s2);
}

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
		int child_status;

		pid = fork();
		if (pid == -1)
				perror("Fork failed");
		else if (pid > 0) /* parent process */
				waitpid(pid, &child_status, 0);
		else    /* child process */
				execve(path, args, NULL), close(0);
		return (pid);
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
		while(s1[len1++] != '\0');;
		while(s2[len2++] != '\0');;
		newstr = malloc(len1 + len2 + 2);
		if (newstr == NULL)
				return (NULL);
		while(s1[i] != '\0')
				newstr[i] = s1[i], i++;
		newstr[i++] = '/';
		while(s2[j] != '\0')
				newstr[i] = s2[j], i++, j++;
		newstr[i++] = '\0';
		return (newstr);
}

/**
 * function_caller - this function check if name
 * it's a valid command.
 * @paths: are the paths of the PATH variable.
 * @name: is the command.
 * @programname: is the name of the program.
 * @pcp: it's a pointer to the path's number.
 *
 * Return: a string with the full command path, or NULL
 * if name it's a invalid command.
 */
char *check_existance(char *paths[], char *name, char *programname, int *pcp)
{
		char *dir_buf = NULL;
		int flag = 0, i = 0;

		if (access(name, F_OK) == 0) /* if name it's a full path */
		{
				while(name[++i]);;
				dir_buf = malloc(i + 1);
				for (i = 0; name[i]; i++)
						dir_buf[i] = name[i];
				dir_buf[i] = '\0';
				return (dir_buf);
		}
		while ((!flag) && (i < *pcp))
		{
				dir_buf = dir_generator(paths[i++], name);
				flag = ((access(dir_buf, F_OK) == 0) ? 1 : 0); /* the flag change when it's a match */
				if (!flag)
						free(dir_buf); /* free the memory if not a match */
		}
		if (!flag) /* if flag it's zero, the command was not valid */
		{
				i = 0;
				while (programname[i++]);;
				write(1, programname, i), write(1, ": No such file or directory\n", 28);
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
		int a = 0, i, j = 0, k = 0, ac = 1;
		char **args, *ps;

		for (i = 0; input[i]; i++)
				ac = ((input[i] == ' ') ? ac + 1 : ac); /*number of arguments*/
		args = malloc(sizeof(char *) * (ac + 1));
		if (!args)
				return(NULL);
		ps = strtok(input, " "); /* token input */
		while (ps)
				args[j++] = ps, ps = strtok(NULL, " "); /* copy */
		args[j++] = ps;                             /* the arguments */
		*arc = ac;
		return (args); /*the final array */
}

/**
 * env_reader - this function prints the enviroment variables.
 * @env: is the array of pointers to the enviroment variables.
 *
 * Return: always void.
 */
void env_reader (char **env)
{
		int i = 0, j = 0, flag = 0;
		char *c_env = "env";

		for(i = 0; env[i]; i++)
		{
				for(j = 0; env[i][j]; j++);;
				write(1, env[i], j + 1), write(1, "\n", 1);
		}
}

/**
 * init - saves the directions of the variable PATH.
 * @env: is the array of pointers to the enviroment variables.
 * @pcp: is a pointer to the number 
 *
 * Return: an array of string with the differents directories,
 * or NULL if fall.
 */
char **init (char **env, int *pcp)
{
		int i = 0, j = 0, k = 0, p_found = 0, pc = 0, a = 0, cc = 0;
		char *p = "PATH", **p_array, *ps;

		while (!p_found) /* find PATH inside of env */
		{
				i++;
				for (j = 0; p[j]; j++)
				{
						if (p[j] != env[i][j])
								break;
						p_found = (((p[j] == env[i][j]) && (p[j + 1] == '\0')) ? 1 : 0);
				}
		}
		for (j = 5; env[i][j]; j++)
				pc = ((env[i][j] == ':') ? pc + 1 : pc); /* number of directories */
		p_array = malloc(sizeof(char *) * pc), a = 5, pc = 0;
		if (!p_array)
				return(NULL);
		for (j = 5; env[i][j]; j++)
		{
				cc++;
				if ((env[i][j + 1]) && (env[i][j + 1] == ':'))
				{
						ps = malloc(cc + 1), k = 0;
						for (; a <= j; a++)
								ps[k++] = env[i][a]; /* copy the directories */
						ps[k] = '\0', p_array[pc++] = ps, j++, a++, cc = 0;
				}
		}
		*pcp = pc; /* number of directories */
		return (p_array); /* the final array */
}

/**
 * main - simle shell main function. This function calls for execution in case of a valid path or program argument. 
 * 
 * @argc - argument count
 * @argv - argument vector
 * @env - env variable array
 * 
 * Return: always 0 
 */

int main (int argc, char **argv, char **env)
{
	int x, i, pc, *pcp = &pc, ac, *acp = &ac, interactive = 1;
	char **paths, **args, *input = NULL, *exec_path;
	size_t len = 0;

	paths = init(env, pcp);		/* save paths in variable */
	while(interactive)
	{
		interactive = isatty(0);	/* check for interactive mode */
		if (interactive) {write(1, "$ ", 2);}
		if (getline(&input, &len, stdin) == -1)		/* check for EOF */
		{
			write(1, "\n", 1), free(input);
			break;
		}
		if (input[0] == '\n')
			continue;
		for (i = 0; input[i]; i++)
			input[i] = ((input[i] == '\n') ? '\0' : input[i]);		/* trim trailing '\n' */
		if ((_strcmp(input, "exit") == 0) || (_strcmp(input, "EXIT") == 0))	/* check for exit */
		{
			free(input);
			break;
		}
		if (_strcmp(input, "env") == 0)		/* check for env command */
		{
			env_reader(env);
			continue;
		}
		args = args_isolator(input, acp);	/* tokenize arguments to array */
		exec_path = check_existance(paths, args[0], argv[0], pcp);	/* check for valid executable path */
		if (exec_path)
			function_caller(exec_path, args), free(exec_path);	/* execute program */
		free(args);
	}
	for(x = 0; x < *pcp; x++)
		free(paths[x]);
	free(paths);
	return (0);
}
