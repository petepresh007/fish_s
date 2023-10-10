#include "shell.h"
/**
 * getLocation - a function to get location
 * @cmd: command to be psssed
 * Return: location
 */

char *getLocation(char *cmd)
{
        char *path, *pathcopy, *pathtoken, *filepath;
        int cmd_length, directory_length;
        struct stat buff;

        path = getenv("PATH");

        if (path)
        {
                /**Duplicate the path string with strdup, remember to free -> */
                pathcopy = strdup(path);
                /**get the length of the command that is passed*/
                cmd_length = strlen(cmd);
                /**breakdown the path variable and get all the directories available*/
                pathtoken = strtok(pathcopy, ":");

                while (pathtoken != NULL)
                {
                        /**get the length of the directory*/
                        directory_length = strlen(pathtoken);
                        /**allocate memory fo storing the command name together with the directory name*/
                        filepath = malloc(cmd_length + directory_length + 2);/**added 2 for slashes*/
                        /**to build the path for command, lets copy the directory path and concatenate*/
                        strcpy(filepath, pathtoken);
                        strcat(filepath, "/");
                        strcat(filepath, cmd);
                        strcat(filepath, "\0");

                        /**let test if this file path actually exists and return it if it does, otherwise try to get the next directory*/
                        if (stat(filepath, &buff) == 0)
                        {
                                /**return value of 0 means success implying that the filepath is valid*/
                                /**free up allocated memory before returning file ath*/
                                free(pathcopy);
                                return (filepath);
                        }
                        else
                        {
                                /**free up the file path memory so you can check for another path*/
                                free(filepath);
                                pathtoken = strtok(NULL, ":");
                        }
                }
                /**if we don't get any filepath that exists for the command,we return NULL but we need to free up memory for pathway*/
                free(pathcopy);
                /**before we exit without luck, lets see if the command is a itself filepath that exists*/
                if (stat(cmd, &buff) == 0)
                {
                        return (cmd);
                }
                return (NULL);
        }
        return (NULL);
}
