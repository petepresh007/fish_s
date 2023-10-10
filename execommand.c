#include "shell.h"
/**
 * execommand - a function to execute command
 * @argument_v: argument to be executed
 * Return: void
 */

void execommand(char **argument_v)
{
        char *cmd = NULL, *actual_cmd = NULL;
	pid_t processID, Wwpid;
	int stats;

	processID = fork();

	if(processID == 0)
	{
        	if (argument_v)
        	{
                	/**get command*/
                	cmd = argument_v[0];

                	/**generate the path to this command before passing it to execve */
                	actual_cmd = getLocation(cmd);

                /**execute the command with execve*/
                	if (execve(actual_cmd, argument_v, NULL) == -1)
                	{
                        	perror("Error: ");
                	};
			exit(-1);
        	}
		else if (processID < 0)
		{
			/**ERROR FORKING*/
			perror("Error: ");
		}
		else
		{
			/**Pareent process*/
			do 
			{
				 Wwpid = waitpid(processID, &stats, WUNTRACED);
			}
			while (!WIFEXITED(stats) && !WIFSIGNALED(stats));
		}
	}
}
