/* cat program */
#include "syscall.h"
#include "copyright.h"

int main(int argc, char* argv[])
{
	OpenFileID fileId;
	unsigned int filesz, i;
	char c;
	if ( (fileId= OpenFileFunc(argv[1], 1)) != 0)
	{
		PrintString("Can not open file ");
		return 0;
	}
	filesz = SeekFile(-1, fileId);
	i = 0;
	for (; i < filesz; ++i)
	{
		ReadFile(&c, 1, fileId);
		PrintChar(c);
	}
	CloseFile(fileId);
	return 0;
}
