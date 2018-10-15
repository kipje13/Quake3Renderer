#include "pk3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <miniz_tinfl.h>

int getfileindex(PK3FILE* pk3, const char* filename)
{
	FILEINFO* files = pk3->files;

	for (int i = 0; i < pk3->filecount; i++)
	{
		if (strcmp(files[i].filename, filename) == 0)
		{
			return i;
		}
	}

	return -1;
}

PK3FILE* openpk3(const char* path)
{
	FILEINFO files[5000];

	FILE* f = fopen(path, "rb");

	fseek(f, 0, SEEK_END);
	int end = ftell(f);

	fseek(f, end - 6, 0);

	int headeroffset;
	fread(&headeroffset, sizeof(headeroffset), 1, f);

	int filecount = 0;

	while (!feof(f))
	{
		fseek(f, headeroffset, 0);
		int id;
		fread(&id, sizeof(id), 1, f);

		if (id == 0x02014b50)
		{
			fseek(f, headeroffset + 28, 0);
			short n;
			fread(&n, sizeof(n), 1, f);

			short m;
			fread(&m, sizeof(m), 1, f);

			short k;
			fread(&k, sizeof(k), 1, f);

			fseek(f, headeroffset + 42, 0);
			int offset;
			fread(&offset, sizeof(offset), 1, f);

			char* name = (char*)malloc(sizeof(char) * (n + 1));
			fread(name, sizeof(char), n, f);
			name[n] = '\0';

			files[filecount].filename = name;
			files[filecount].offset = offset;

			headeroffset += 46 + n + m + k;

			filecount++;
		}
		else
		{
			break;
		}
	}

	FILEINFO* buffer = (FILEINFO*)malloc(sizeof(FILEINFO) * filecount);
	memcpy(buffer, files, sizeof(FILEINFO) * filecount);

	PK3FILE* pk3 = (PK3FILE*)malloc(sizeof(PK3FILE));
	pk3->filecount = filecount;
	pk3->files = buffer;
	pk3->stream = f;

	return pk3;
}

void closepk3(PK3FILE* pk3)
{
	FILEINFO* files = pk3->files;

	for (int i = 0; i < pk3->filecount; i++)
	{
		free(files[i].filename);
	}

	free(pk3->files);
	free(pk3);

	fclose(pk3->stream);
}

char* loadfile(PK3FILE* pk3, const char* filename, size_t* size)
{
	int fileindex = getfileindex(pk3, filename);

	if (fileindex < 0)
		return NULL;

	FILE* f = pk3->stream;

	FILEINFO* files = pk3->files;
	fseek(f, files[fileindex].offset + 18, 0);
	int compressed;
	fread(&compressed, sizeof(compressed), 1, f);

	int uncompressed;
	fread(&uncompressed, sizeof(uncompressed), 1, f);

	short n;
	fread(&n, sizeof(n), 1, f);

	short m;
	fread(&m, sizeof(m), 1, f);

	fseek(f, files[fileindex].offset + 30 + n + m, 0);

	char* data = (char*)malloc(sizeof(char) * compressed);
	fread(data, sizeof(char), compressed, f);

	char* decompressedData = (char*)tinfl_decompress_mem_to_heap(data, compressed, size, 0);

	free(data);

	return decompressedData;
}

