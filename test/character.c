/*
 * =====================================================================================
 *
 *       Filename:  character.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/31/2013 06:34:45 AM
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
	char c = ReadChar();
	PrintChar(c);
	return 0;
}

