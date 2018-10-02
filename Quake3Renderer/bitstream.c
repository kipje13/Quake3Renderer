#include "bitstream.h"

BITSTREAM* createBitStream(char* buffer, int length)
{
	BITSTREAM* bitstream = malloc(sizeof(BITSTREAM));
	bitstream->buffer = buffer;
	bitstream->length = length;
	bitstream->pos = 0;

	return bitstream;
}

void closeBitStream(BITSTREAM* bitstream)
{
	free(bitstream);
}

int readBits(BITSTREAM* bitstream, int count)
{
	int result = 0;

	for (int i = 0; i < count; i++)
	{
		int p = bitstream->pos + i;
		result |= ((bitstream->buffer[p / 8]) >> (p%i)) << i;;
	}

	bitstream->pos += count;

	return result;
}

char readByte(BITSTREAM* bitstream)
{
	return readBits(bitstream, 8);
}

short readShort();
int readInt();