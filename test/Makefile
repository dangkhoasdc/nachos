# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = ../../../gnu-decstation-ultrix/decstation-ultrix/2.95.3/

LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)

PATH = $(GCCDIR):/lib:/usr/bin:/bin

CC = $(GCCDIR)gcc -B../../../gnu-decstation-ultrix/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = gcc -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult sort readint PrintInt string \
	help ascii bubblesort createfile cat copy echo reverse

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult
readint.o: readint.c
	$(CC) $(CFLAGS) -c readint.c
readint: readint.o start.o
	$(LD) $(LDFLAGS) start.o readint.o -o readint.coff
	../bin/coff2noff readint.coff readint

PrintInt.o: PrintInt.c
	$(CC) $(CFLAGS) -c PrintInt.c
PrintInt: PrintInt.o start.o
	$(LD) $(LDFLAGS) start.o PrintInt.o -o PrintInt.coff
	../bin/coff2noff PrintInt.coff PrintInt 

string.o: string.c
	$(CC) $(CFLAGS) -c string.c
string: string.o start.o
	$(LD) $(LDFLAGS) start.o string.o -o string.coff
	../bin/coff2noff string.coff string
	

help.o: help.c
	$(CC) $(CFLAGS) -c help.c
help: help.o start.o
	$(LD) $(LDFLAGS) start.o help.o -o help.coff
	../bin/coff2noff help.coff help

bubblesort.o: bubblesort.c
	$(CC) $(CFLAGS) -c bubblesort.c
bubblesort: bubblesort.o start.o
	$(LD) $(LDFLAGS) start.o bubblesort.o -o bubblesort.coff
	../bin/coff2noff bubblesort.coff bubblesort 

ascii.o: ascii.c
	$(CC) $(CFLAGS) -c ascii.c
ascii: ascii.o ascii.o
	$(LD) $(LDFLAGS) start.o ascii.o -o ascii.coff
	../bin/coff2noff ascii.coff ascii
	
ascii.o: ascii.c
	$(CC) $(CFLAGS) -c ascii.c
ascii: ascii.o ascii.o
	$(LD) $(LDFLAGS) start.o ascii.o -o ascii.coff
	../bin/coff2noff ascii.coff ascii

createfile.o: createfile.c
	$(CC) $(CFLAGS) -c createfile.c
createfile: createfile.o createfile.o
	$(LD) $(LDFLAGS) start.o createfile.o -o createfile.coff
	../bin/coff2noff createfile.coff createfile

cat.o: cat.c
	$(CC) $(CFLAGS) -c cat.c
cat: cat.o cat.o
	$(LD) $(LDFLAGS) start.o cat.o -o cat.coff
	../bin/coff2noff cat.coff cat

copy.o: copy.c
	$(CC) $(CFLAGS) -c copy.c
copy: copy.o copy.o
	$(LD) $(LDFLAGS) start.o copy.o -o copy.coff
	../bin/coff2noff copy.coff copy

echo.o: echo.c
	$(CC) $(CFLAGS) -c echo.c
echo: echo.o echo.o
	$(LD) $(LDFLAGS) start.o echo.o -o echo.coff
	../bin/coff2noff echo.coff echo

reverse.o: reverse.c
	$(CC) $(CFLAGS) -c reverse.c
reverse: reverse.o reverse.o
	$(LD) $(LDFLAGS) start.o reverse.o -o reverse.coff
	../bin/coff2noff reverse.coff reverse


