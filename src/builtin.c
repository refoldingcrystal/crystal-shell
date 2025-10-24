#include <stdio.h>
#include <unistd.h>

#include "builtin.h"

const char *builtin_names[] = {
	"cd",
	"help",
	"exit",
	"history",
	"alias"
};

size_t builtin_count(){
    return sizeof(builtin_names) / sizeof(builtin_names[0]);
}

int (*builtin_func[])(char **) = {
	&sh_cd,
	&sh_help,
	&sh_exit,
	&sh_history,
	&sh_alias
};

int sh_cd(char **args){
	if (args[1] == NULL){
		fprintf(stderr, "crystal: not yet implemented\n");
	} else {
		if (chdir(args[1])){
			perror("crystal");
		}
	}
	return EXIT_SUCCESS;
}

int sh_help(char **args){
	int i;

	printf("crystal shell\n");
	printf("builtin functions:\n");
	for (i = 0; i < builtin_count(); i++){
		printf("  %s\n", builtin_names[i]);
	}
	return EXIT_SUCCESS;
}

int sh_exit(char **args){
	printf("~ bye\n");
	/* TODO: saving to history file */
	return EXIT_FAILURE;
}

int sh_history(char **args){
	/* TODO: showing history */
	return EXIT_SUCCESS;
}

int sh_alias(char **args){
	/* TODO: evaluate expansion of alias */
	if (args[1] == NULL){
		/* TODO: show all aliases */
	} else {
		/* TODO: if alias exists show its expansion */
		/* TODO: handle error */
	}
	return EXIT_SUCCESS;
}
