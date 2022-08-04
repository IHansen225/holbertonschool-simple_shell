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
 * init - saves the directions of the variable PATH.
 * @env: is the array of pointers to the enviroment variables.
 * @pcp: is a pointer to the number
 *
 * Return: an array of string with the differents directories,
 * or NULL if fall.
 */
char **init(int *pcp)
{
		int i = 0, j = 0, k = 0, p_found = 0, pc = 0, a = 0, cc = 0;
		char *p = "PATH", **p_array, *ps;
		extern char **environ;

		while (!p_found && environ[i]) /* find PATH inside of env */
		{
			for (j = 0; p[j]; j++)
			{
				if (p[j] != environ[i][j])
					break;
				p_found = ((p[j + 1] == '\0') ? 1 : 0);
			}
			i++;
		}
		i--;
		if (!p_found)
			return (NULL);
		for (j = 5; environ[i][j]; j++)
				pc = ((environ[i][j] == ':') ? pc + 1 : pc); /* number of directories */
			p_array = malloc(sizeof(char *) * pc), a = 5, pc = 0;
			if (!p_array)
				return (NULL);
			for (j = 5; environ[i][j]; j++)
			{
				cc++;
				if ((environ[i][j + 1]) && (environ[i][j + 1] == ':'))
				{
					ps = malloc(cc + 1), k = 0;
					for (; a <= j; a++)
						ps[k++] = environ[i][a]; /* copy the directories */
					ps[k] = '\0', p_array[pc++] = ps, j++, a++, cc = 0;
				}
			}
		*pcp = pc; /* number of directories */
		return (p_array); /* the final array */
}

/**
 * main - simple shell main function. Calls for execution in case of valid path
 *
 * @argc: argument count
 * @argv: argument vector
 * @env: env variable array
 *
 * Return: always 0
 */

void free_exit(char **paths, int *pcp)
{
	int x = 0;

	for (x = 0; x < *pcp; x++)
	{
		if (paths[x])
		free(paths[x]);
	}
	free(paths);
}

int main(int argc, char **argv)
{
	int i, aux_exit = 0, *stat = &aux_exit, pc, *pcp = &pc, ac, *acp = &ac, interactive = 1;
	char **paths, **args, *input = NULL, *exec_path;
	size_t len = 0;
	extern char **environ;

	(void) argc;
	paths = init(pcp);		/* save paths in variable */
	while (interactive)
	{
		interactive = isatty(0);	/* check for interactive mode */
		if (interactive)
			write(1, "$ ", 2);
		if (getline(&input, &len, stdin) == -1)		/* check for EOF */
		{
			write(1, "\n", 1), free(input);
			break;
		}
		if (input[0] == '\n')
			continue;
		for (i = 0; input[i]; i++)
			input[i] = ((input[i] == '\n') ? '\0' : input[i]);		/* trim trailing '\n' */
		if (_strcmp(input, "exit") == 0)	/* check for exit */
		{
			free(input);
			free_exit(paths, pcp);
			exit(*stat);
		}
		if (_strcmp(input, "env") == 0)		/* check for env command */
		{
			env_reader();
			free(input);
			continue;
		}
		args = args_isolator(input, acp);       /* tokenize arguments to array */
                if (!args[0])
                {
                        free(args);
                        free(input);
                        continue;
                }
		exec_path = check_existance(paths, args[0], argv[0], pcp, stat);
                if (exec_path)
                        function_caller(exec_path, args, stat), free(exec_path);
                free(args);
		free(input);
	}
	if (paths)
		free_exit(paths, pcp);
	exit (aux_exit);
}
