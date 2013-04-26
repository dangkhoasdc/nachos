/* reverse program */

#include "syscall.h"
#include "copyright.h"

int main(int argc, char* argv[])
{
	char c;
	OpenFileID srcId = OpenFileFunc(argv[1], 1);
	OpenFileID dstId = OpenFileFunc(argv[2], 0);
	unsigned int srcSz, srcPos;
	if (srcId != 0 || dstId != 0)
	{
		int errorId = srcId == 0 ? 1 : 2;
		PrintString("Can not open file \n");
		PrintString("Terminate program\n");
		return 0;
	}
	/* Seek source file to end of file */
	srcSz = SeekFile(-1, srcId);
	/* Seek destination file to begin of file */
	SeekFile(0, dstId);
	while (srcSz+1)
	{
		SeekFile(srcSz, srcId);
		ReadFile(&c, 1, srcId);
		WriteFile(&c, 1, dstId);
		srcSz--;
	}
	CloseFile(srcId);
	CloseFile(dstId);
	return 0;
}
