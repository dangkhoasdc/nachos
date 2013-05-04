/* reverse program */

#include "syscall.h"
#include "copyright.h"

int main(int argc, char* argv[])
{
	char c;
	OpenFileID srcId;
	OpenFileID dstId;
	char source[255], dest[255];
	int srcSz, srcPos;
	PrintString("Input source file:");
	ReadString(source, 255);
	PrintString("Input destination file:");
	ReadString(dest, 255);
	PrintString(source);

	srcId = OpenFileFunc(source, 1);
	CreateFile(dest);
	dstId = OpenFileFunc(dest, 0);
	if (srcId == -1 || dstId == -1)
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
	 
	while (srcSz>=0)
	{	
		SeekFile(srcSz, srcId);
		ReadFile(&c, 1, srcId);
		WriteFile(&c, 1, dstId);
		PrintString("Test = ");
		PrintChar(c);
		PrintChar('\n');
		srcSz --;
	}
	CloseFile(srcId);
	CloseFile(dstId);
	return 0;
}
