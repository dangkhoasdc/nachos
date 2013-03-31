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
	ReadString(str, 100);
	PrintString(str);
	return 0;
}
