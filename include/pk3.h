#pragma once

#include <stdio.h>
#include <stddef.h>

typedef struct
{
	char* filename;
	int offset;
} FILEINFO;

typedef struct
{
	int filecount;
	FILEINFO* files;
	FILE* stream;
} PK3FILE;

PK3FILE* openpk3(const char* path);
void closepk3(PK3FILE* pk3);
char* loadfile(PK3FILE* pk3, const char* filename, size_t *size);