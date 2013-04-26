/* echo program */

#include "syscall.h"
#include "copyright.h"

int main(int argc, char* argv[])
{
	char mess[255];
	OpenFileID inConsole = OpenFile("stdin", 0);
	OpenFileID outConsole = OpenFile("stdout", 1);
	while(1)
	{
		ReadFile(mess, 255, inConsole);
		WriteFile(mess, 255, outConsole);
	}
	CloseFile(inConsole);
	CloseFile(outConsole);
	return 0;
}