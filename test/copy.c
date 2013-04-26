/* copy program */
#include "syscall.h"
#include "copyright.h"

int main(int argc, char* argv[])
{
	OpenFileID srcId;
	OpenFileID dstId;
	unsigned int srcsz, i;
	char c,
	if ( (srcId= OpenFile(argv[1], 1)) != 0)
	{
		PrintString("Can not open file %s\n", argv[1]);
		return 0;
	}
	if ((dstId = OpenFile(argv[2], 0)) != 0)
	{
		PrintString("Can not open file %s\n", argv[2]);
		PrintStirng("Try to create file %s\n", argv[2]);
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