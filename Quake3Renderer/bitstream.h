#ifndef BITSTREAM_H
#define BITSTREAM_H

typedef struct {
	char* buffer;
	int length;
	int pos;
} BITSTREAM;

BITSTREAM* createBitStream(char* buffer, int length);
void closeBitStream(BITSTREAM* bitstream);
int readBits(int count);
char readByte();
short readShort();
int readInt();

#endif


