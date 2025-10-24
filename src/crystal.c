#include <linux/limits.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "input.h"
#include "builtin.h"

int sh_exec(char **args){
	pid_t pid;
	int status, i;

	if (args[0] == NULL){
		return EXIT_SUCCESS;
	}
	for (i = 0; i < builtin_count(); i++){
		if (!strcmp(args[0], builtin_names[i])){
			return (*builtin_func[i])(args);
		}
	}

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
	char **args = NULL;
	char cwd[PATH_MAX], hostname[HOST_NAME_MAX + 1];
	char *username = getlogin();
	int status;

	sh_logo();
	gethostname(hostname, HOST_NAME_MAX + 1);

	while(1){
		getcwd(cwd, sizeof(cwd));
		printf("[\033[1m%s\033[0m@\033[1m%s\033[0m] \033[1m%s\033[0m >", username, hostname, cwd);

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
