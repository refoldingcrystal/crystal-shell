#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "input.h"

int sh_exec(char **args){
	pid_t pid;
	int status;

	pid = fork();
	if (!pid){
		if (execvp(args[0], args) == -1){
			perror(args[0]);
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0){
		perror(args[0]);
	} else {
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return EXIT_SUCCESS;
}

int main(int argc, char **argv){
	char *line;
	char **args;
	int status;

	while(1){
		printf("> ");
		line = read_line();
		args = split_line(line);
		status = sh_exec(args);

		free(line);
		free(args);

		if (status == EXIT_FAILURE){
			break;
		}
	}

	return EXIT_SUCCESS;
}
