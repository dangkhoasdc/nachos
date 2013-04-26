/* copy program */
#include "syscall.h"
#include "copyright.h"

int main(int argc, char* argv[])
{
	OpenFileID srcId;
	OpenFileID dstId;
	int filesz,srcsz, i;
	char c;
	if ( (srcId= OpenFileFunc(argv[1], 1)) != 0)
	{
		PrintString("Can not open file \n");
		return 0;
	}
	if ((dstId = OpenFileFunc(argv[2], 0)) != 0)
	{
		PrintString("Can not open file \n");
		PrintString("Try to create file\n");
		if (CreateFile(argv[2]) == 0)
		{
			PrintString("Create Successfully\n");
		}
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
