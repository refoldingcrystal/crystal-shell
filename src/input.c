#include "input.h"

char *read_line(){
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1){
		if (feof(stdin)){
			exit(EXIT_SUCCESS);
		} else {
			perror("read_line");
			exit(EXIT_FAILURE);
		}
	}
	return line;
}

char **split_line(char *line){
	int bufsize = BUFSIZE;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens){
		fprintf(stderr, "crystal: memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, SPLIT_CHAR);
	while (token != NULL){
		tokens[position] = token;
		position++;

		if (position >= bufsize){
			bufsize += BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens){
				fprintf(stderr, "crystal: memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, SPLIT_CHAR);
	}
	tokens[position] = NULL;
	return tokens;
}
