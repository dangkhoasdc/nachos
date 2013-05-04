/* createfile syscall demo */
#include "syscall.h"
#include "copyright.h"

int main(int argc, char* argv[])
{
	int isCreate = CreateFile("hello");
	char mess[255];
	OpenFileID open; 
	if (isCreate)
	{
		PrintString("Can not create file \'hello.txt\'\n");
	} 
	else
	{
		PrintString("Successfully create file\n");
		open = OpenFileFunc("hello", 0);
		if (open==-1) PrintString("Can not open file\n");
		WriteFile("123", 3, open);
		SeekFile(0, open);
		ReadFile(mess, 3, open);
	  PrintString(mess);
		CloseFile(open);
	}
	
	return 0;
}
