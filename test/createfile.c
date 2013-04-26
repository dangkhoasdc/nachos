/* createfile syscall demo */
#include "syscall.h"
#include "copyright.h"

int main(int argc, char* argv[])
{
	int isCreate = CreateFile("hello.txt");
	if (isCreate)
	{
		PrintString("Can not create file \'hello.txt\'\n");
	} 
	else
	{
		PrintString("Successfully create file\n");
	}
	
	return 0;
}
