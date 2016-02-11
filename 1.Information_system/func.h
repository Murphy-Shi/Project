#ifndef __FUNC_H
#define __FUNC_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define PATH "./more.txt"

struct infor
{
	char num[10];
	char from[10];
	char to[10];
	char date[10];
	char arr[10];
	int pri;
	struct infor *next;
	struct infor *prev;
};

#endif
