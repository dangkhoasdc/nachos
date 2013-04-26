/*
 * =====================================================================================
 *
 *       Filename:  string.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/31/2013 08:01:18 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "syscall.h"
#include "copyright.h"
int main()
{
	char str[100];
	char a = 'A';
	a = ReadChar();
		PrintChar(a);
	a = ReadChar();
		PrintChar(a);
	a = ReadChar();
		PrintChar(a);
	a = ReadChar();
		PrintChar(a);
	/*  PrintString("Nhap 1 chuoi:");
	ReadString(str, 100);
	PrintString("Chuoi vua nhap:");	
	PrintString(str);*/
	return 0;
}
