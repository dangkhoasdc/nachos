// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------
#define MAX_FILE_HANDLER 10
#include "string.h"
void ExceptionHandler(ExceptionType which)
{

    int Systype = machine->ReadRegister(2);
    switch (which)
    {
		case SyscallException:
		switch (Systype)
			{
				case SC_Halt:
					DEBUG('a', "Shutdown, initiated by user program.\n");
   				interrupt->Halt();
				break;
				case SC_ReadInt:
				{
				/*Read integer number 
					and return it*/
					DEBUG('a', "Read integer number from console.\n");
					int number = 0;
					int nDigit = 0;
					int i;
					char* bufer = new char[MAX_INT_LENGTH];
					nDigit = gSynchConsole->Read(bufer, MAX_INT_LENGTH);
					i = bufer[0] == '-' ? 1:0 ;
					for (; i < nDigit; ++i)
					{
						number = number*10 + (int) (bufer[i] & MASK_GET_NUM);
					}
					number = bufer[0] == '-' ? -1*number : number;
					machine->WriteRegister(2, number);
					delete bufer;
				}
				break;
				case SC_PrintInt:
				{
					char s[MAX_INT_LENGTH], neg, tmp;
					neg = '-';
					int i, n, mid, sz;
					i = n = 0;
					DEBUG('a', "Read argument value at r4");
					n = machine->ReadRegister(4);
					if (n < 0)
					{
						gSynchConsole->Write(&neg,1);
						n = -n;
					}
					do {
						s[i++] = n%10 + '0';
					}	while (( n /= 10) > 0);
					sz = i;
					s[sz] = '\n';
					mid = i / 2;
					while (i-->mid)
					{
						tmp = s[sz-i-1];
						s[sz-i-1] = s[i];
						s[i] = tmp;
					}
					gSynchConsole->Write(s, sz);
				}
				break;
				case SC_PrintChar:
				{
					char ch;
					ch = (char) machine->ReadRegister(4);
					//printf("ch = %c",ch);
					gSynchConsole->Write(&ch, 1);
					break;
				}
				case SC_ReadChar:
				{
					int sz;
					char buf[MAX_INT_LENGTH];
					sz = gSynchConsole->Read(buf, MAX_INT_LENGTH);
					machine->WriteRegister(2, buf[sz-1]);
				}
				break;
				case SC_PrintString:
				{
					int bufAddr = machine->ReadRegister(4);
					int i = 0;
					char *buf = new char[LIMIT];
					buf = machine->User2System(bufAddr, LIMIT);
					while (buf[i] != 0 && buf[i] != '\n')
					{
						gSynchConsole->Write(buf+i, 1);
						i++;
					}
					buf[i] = '\n';
					gSynchConsole->Write(buf+i,1);
					delete[] buf;
				}
				break;
				case SC_ReadString:
				{
					char *buf = new char[LIMIT];
					if (buf == 0) break;
					int bufAddrUser = machine->ReadRegister(4);
					int length = machine->ReadRegister(5);
					int sz = gSynchConsole->Read(buf, length);
					machine->System2User(bufAddrUser, sz, buf);
					delete[] buf;
				}
				break;
				case SC_CreateFile:
				{
					int bufAddr = machine->ReadRegister(4); // read string pointer from user
					char *buf = new char[LIMIT];
					buf = machine->User2System(bufAddr, LIMIT);
					// create a new file 
					if (fileSystem->Create(buf, 0) == false)
					{
						DEBUG('f',"can not create file");
						machine->WriteRegister(2, -1);
					} else 
					{
						DEBUG('f',"create file successfully");
						machine->WriteRegister(2, 0);
					};
					delete [] buf;
					break;
				}
				case SC_OpenFileID:
				{
					int bufAddr = machine->ReadRegister(4); // read string pointer from user
					int type = machine->ReadRegister(5);
					char *buf = new char[LIMIT];
					if (fileSystem->index > 10)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					buf = machine->User2System(bufAddr, LIMIT);
					if (strcmp(buf,"stdin") == 0)
					{
						printf("stdin mode\n");
						machine->WriteRegister(2, 0);
						break;
					}
					if (strcmp(buf,"stdout") == 0)
					{
						printf("stdout mode\n");
						machine->WriteRegister(2, 1);
						break;
					}
					if ((fileSystem->openf[fileSystem->index] = fileSystem->Open(buf, type)) != NULL)
					{
						DEBUG('f',"open file successfully");
						machine->WriteRegister(2, fileSystem->index-1);
					} else 
					{
						DEBUG('f',"can not open file");
						machine->WriteRegister(2, -1);
					};
					delete [] buf;
					break;
				}
				case SC_CloseFile:
				{
					int m_index = machine->ReadRegister(4);
					if (fileSystem->openf[m_index] == NULL) break;
					delete fileSystem->openf[m_index];
					fileSystem->openf[m_index] = NULL;
					break;
				}
				case SC_ReadFile:
				{
					int bufAddr = machine->ReadRegister(4);
					int NumBuf = machine->ReadRegister(5);
					int m_index = machine->ReadRegister(6);	
					int OldPos;
					int NewPos;
					char *buf = new char[NumBuf];
					int i = 0;
					// Check m_index
					if (m_index < 0 || m_index > 10)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					// check openf[m_index]
					if (fileSystem->openf[m_index] == NULL)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					OldPos = fileSystem->openf[m_index]->GetCurrentPos();
					buf = machine->User2System(bufAddr, NumBuf);
					if (fileSystem->openf[m_index]->type == 2)
					{
						/*  printf("NumBuf = %d\n", NumBuf);*/
						int sz = gSynchConsole->Read(buf, NumBuf);
						/*  machine->System2User(bufAddr, sz, buf);*/
					
						machine->System2User(bufAddr, sz, buf);
						machine->WriteRegister(2, sz);
						break;
					}
					
					if ((fileSystem->openf[m_index]->Read(buf, NumBuf) ) > 0)
					{
						// Copy data from kernel to user space
					  NewPos = fileSystem->openf[m_index]->GetCurrentPos();
						machine->System2User(bufAddr, NewPos - OldPos +1, buf);
						machine->WriteRegister(2, NewPos - OldPos + 1);
					}
					else
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					// read data from console 
					
					/*  
					if (fileOpen.type == 2)
					{
						int sz = gSynchConsole->Read(buf, NumBuf);
						machine->System2User(bufAddr, sz, buf);
						machine->WriteRegister(2, sz);
					}*/
					delete[] buf;
					break;
				}
				case SC_WriteFile:
				{
					int bufAddr = machine->ReadRegister(4);
					int NumBuf = machine->ReadRegister(5);
					int m_index =  machine->ReadRegister(6);
					int OldPos;
					int NewPos;
					char *buf = new char[NumBuf];
					// Check m_index
					if (m_index < 0 || m_index > 10)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					// check openf[m_index]
					if (fileSystem->openf[m_index] == NULL)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					OldPos = fileSystem->openf[m_index]->GetCurrentPos();
					
					// type must equals '0'
					buf = machine->User2System(bufAddr, NumBuf);
					if (fileSystem->openf[m_index]->type  == 0 || fileSystem->openf[m_index]->type == 3)
					{	
					if ((fileSystem->openf[m_index]->Write(buf, NumBuf)) > 0) 
					{
						// Copy data from kernel to user space
						printf("%s",buf);
						NewPos = fileSystem->openf[m_index]->GetCurrentPos();
						machine->WriteRegister(2, NewPos - OldPos + 1);
					}
					else if (fileSystem->openf[m_index]->type == 1);
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					}
					// Write data to console
					if (fileSystem->openf[m_index]->type == 3)
					{
						int i = 0;
						printf("stdout mode\n");
						while (buf[i] != 0 && buf[i] != '\n')
						{
							gSynchConsole->Write(buf+i, 1);
							i++;
						}
						buf[i] = '\n';
						gSynchConsole->Write(buf+i,1);
						machine->WriteRegister(2, i-1);
					}
					delete[] buf;
					break;
				}
				case SC_SeekFile:
				{
					int pos = machine->ReadRegister(4);
					int m_index = machine->ReadRegister(5);
					if (m_index < 0 || m_index > 10)
					{
						machine->WriteRegister(2, -1);
						break;
					}
					// check openf[m_index]
					if (fileSystem->openf[m_index] == NULL)
					{
						printf("seek fail \n");
						machine->WriteRegister(2, -1);
						break;
					}
						pos = (pos == -1) ? fileSystem->openf[m_index]->Length() : pos;
					if (pos > fileSystem->openf[m_index]->Length() || pos < 0) {
						machine->WriteRegister(2, -1);
					} else 
					{
						fileSystem->openf[m_index]->Seek(pos);
						machine->WriteRegister(2, pos);
					}
					break;
				}
			}
    // Advance program counters.
    machine->registers[PrevPCReg] = machine->registers[PCReg];	// for debugging, in case we
						// are jumping into lala-land
    machine->registers[PCReg] = machine->registers[NextPCReg];
    machine->registers[NextPCReg] += 4;
		break;
	case  PageFaultException:    // No valid translation found
		printf("No valid translation found %d %d\n", which, Systype);
		ASSERT(FALSE);
		break;
	case  ReadOnlyException:     // Write attempted to page marked 
		printf("Write attempted tp page marked %d %d\n", which, Systype);
		ASSERT(FALSE);
		break;
	case  BusErrorException:     // Translation resulted in an 
		printf("Translaion resulted in an %d %d\n", which, Systype);
		ASSERT(FALSE);
		break;
	case  AddressErrorException: // Unaligned reference or one that
		printf("Unaligned reference or one that %d %d\n", which, Systype);
		ASSERT(FALSE);
		break;
	case  OverflowException:     // Integer overflow in add or sub.
		printf("Integer overflow in add or sub %d %d\n", which, Systype);
		ASSERT(FALSE);
		break;
	case  IllegalInstrException: // Unimplemented or reserved instr.
		printf("Unimplemented or reserved instr %d %d\n", which, Systype);
		ASSERT(FALSE);
		break;
   }
		/*Old exception struct*/
    /*if ((which == SyscallException) && (type == SC_Halt)) {
    } else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(FALSE);
    }*/
}
