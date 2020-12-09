/*****************************************************************************
  @file         MyShell.c
  @author       Juhua Hu

*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include <unistd.h>

#include <errno.h>


/**
DONOT change the existing function definitions. You can add functions, if necessary.
*/


/**
  @brief Fork a child to execute the command using execvp. The parent should wait for the child to terminate
  @param args Null terminated list of arguments (including program).
  @return returns 1, to continue execution and 0 to terminate the MyShell prompt.
 */
int execute(char **args)
{
	int returnValue = 1;
	int rc = fork();
	if (rc < 0)
	{
		printf("Error\n");
	}
	else if (rc == 0)
	{
		if(execvp(*args, args) == -1)
		{
			printf("Error\n");
		}	
	}
	else
	{
		wait(NULL);
	}
	free(*args);
	free(args);
	return returnValue;
}


/**
  @brief gets the input from the prompt and splits it into tokens. Prepares the arguments for execvp
  @return returns char** args to be used by execvp
 */
char** parse(void)
{
	char * prompt = malloc(255 * sizeof(char));
	char* temp = malloc(255 * sizeof(char*));	
	char** arg = malloc(255 * sizeof(char*));
	fgets(prompt, 255, stdin);
	temp = strtok(prompt, " \n");
	*arg = temp;
	int i = 1;
	while (temp != NULL)
	{
		temp = strtok(NULL, " \n");
		*(arg + i) = temp;
		i++;
	}
	*(arg + i) = NULL;
	return arg;
}


/**
   @brief Main function should run infinitely until terminated manually using CTRL+C or typing in the exit command
   It should call the parse() and execute() functions
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
 
 void handle_sigint(int sig) 
{
	printf("\n");
	exit(1);
} 
 
int main(int argc, char **argv)
{
	signal(SIGINT, handle_sigint);
	int loop = 1;
	while(loop)
	{
		printf("MyShell> ");
		char** x = parse();
		if (!strcmp(x[0], "exit"))
		{
			printf("exiting\n");
               	exit(0); 
		}
		printf("%s\n", x[0]);
		if (strcmp(x[0], ""))
		{
			loop = execute(x);
		}
		
		
	}
  	return EXIT_SUCCESS;
}

