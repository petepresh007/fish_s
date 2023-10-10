#include "shell.h"
/**
 * main - a function to create a shell
 * Return: 0 if success
 */

int main(int argument_c, char **argument_v)
{
        char *prompt_s = "$ ";
        char *linepointer;
        size_t num = 0;
        ssize_t numchars_read;
        char *linepointer_c = NULL;
        const char *delimeter = " \n";
        int number_token = 0;
        char *token;
        int j;

        /**Declaring void variables*/
        (void)argument_c;

        /**creating an infinit loop*/
        while(1){
                printf("%s", prompt_s);
                /**getline for reading and printing what the end users types*/
                numchars_read = getline(&linepointer, &num, stdin);

                /**CHECK IF THE GETLINE FUNCTION FAIL OR REACH EOF OR Ctrl + D*/
                if (numchars_read == -1)
                {
                        printf("Exit...\n");
                        return (-1);
                }
                /**ALLOCATE SPACE FOR COPY OF THE LINE POINTER*/
                linepointer_c = malloc(sizeof(char) * numchars_read);
                if (linepointer_c == NULL)
                {
                        perror("Failed to allocate memory...");
                        return (-1);
                }

                /**COPY LINEPOINTER TO LINEPOITER_C */
                strcpy(linepointer_c, linepointer);
                /**split the linpointer string into an array of words*/
                /**calculate the total number of tokens*/
                token = strtok(linepointer, delimeter);

                while (token != NULL)
                {
                        number_token++;
                        token = strtok(NULL, delimeter);
                }
                number_token++;

                /**ALLOCATE SPACE TO HOLD TO HOLD THE ARRAY OF STRING*/
                argument_v = malloc(sizeof(char *) * number_token);

                /**STORE EACH TOKEN IN THE argv array*/
                token = strtok(linepointer_c, delimeter);

                for (j = 0; token != NULL; j++)
                {
                         argument_v[j] = malloc(sizeof(char) * strlen(token));
                         strcpy(argument_v[j], token);

                         token = strtok(NULL, delimeter);
                }
                argument_v[j] = NULL;
                /**EXECUTE THE COMMAND*/
                execommand(argument_v);
        }

        /**FREE ALLOCATED MEMORY*/
        free(linepointer_c);
        free(linepointer);

        return (0);
}
