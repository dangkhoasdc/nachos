/*
 * =====================================================================================
 *
 *       Filename:  help.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/31/2013 08:03:05 AM
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
	char intro[] = "Chao cac ban den voi nachOS\n";
	char ascii[] = "Chuong trinh ascii dung de in cac ki tu trong ma ASCII tu ki tu 32 tro di\n";
	char sort[] = "Chuong trinh sort dung de sap xep cac so";
	PrintString(intro);
	PrintString(ascii);
	PrintString(sort);
	return 0;
}

