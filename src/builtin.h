#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdlib.h>

int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);
int sh_history(char **args);
int sh_alias(char **args);

extern const char *builtin_names[];
size_t builtin_count();
extern int (*builtin_func[])(char **);

#endif
