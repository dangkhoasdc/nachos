/* copy program */
#include "syscall.h"
#include "copyright.h"

int main(int argc, char* argv[])
{
	OpenFileID srcId;
	OpenFileID dstId;
	char source[255], dest[255];
	int filesz,srcsz, i;
	char c;
	
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
	filesz = SeekFile(-1, srcId);
	SeekFile(0, srcId);
	SeekFile(0, dstId);
	for (i = 0; i < filesz; ++i)
	{
		ReadFile(&c, 1, srcId);
		WriteFile(&c, 1, dstId);
	}
	CloseFile(srcId);
	CloseFile(dstId);
	return 0;
}
