/*
 * =====================================================================================
 *
 *       Filename:  ascii.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/01/2013 03:24:00 AM
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
	char i = 32;
	for (; i < 127; i++)
	{
		PrintInt((int)i);
		PrintChar(':');
		PrintChar(i);
		PrintChar('\n');
	}
}

