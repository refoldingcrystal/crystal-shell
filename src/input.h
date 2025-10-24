#ifndef INPUT_H
#define INPUT_H

#define BUFSIZE 64
#define SPLIT_CHAR " \t\n"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line();
char **split_line(char *line);

#endif
