#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

#define BIG 100000
#define SMALL 100
#define PAGESIZE 4096


void checkSmallChunk()
{
	// malloc a big chunk
	uint numofpages = SMALL;
	char * base;
	printf(1,"malloc a big chunk - %d pages\n",numofpages);
	base = malloc(numofpages*PAGESIZE);
	if (base == 0)
	{
		printf(1,"malloc %d pages failed!\n",numofpages);
		exit();
	}
	printf(1,"malloc a big chunk succeeded\n");

	// write to pages
	printf(1,"write to several pages\n",numofpages);
	base[PAGESIZE] = 0xFF;
	base[PAGESIZE*20] = 0xFF;
	base[PAGESIZE*50] = 0xFF;
	base[PAGESIZE*numofpages] = 0xFF;
	printf(1,"check for 4 allocations\n\n");
}

void checkBigChunk() {
	// malloc enough memory for several pagedirs entries
	uint numofpages = BIG;
	printf(1,"malloc enough memory for several pagedirs entries - %d pages\n", numofpages);
	char * base;
	base = malloc(PAGESIZE*numofpages);
	if (base == 0)
	{
		printf(1,"malloc %d pages failed!\n",numofpages);
		exit();
	}
	printf(1,"malloc enough memory for several pagedirs entries succeeded\n");

	printf(1,"write to several pages\n",numofpages);
	base[PAGESIZE] = 0xFF;
	base[PAGESIZE*2000] = 0xFF;
	base[PAGESIZE*5000] = 0xFF;
	base[PAGESIZE*numofpages] = 0xFF;
	printf(1,"check for 4 allocations\n\n");
}

void mallocUpToKernel()
{
	printf(1,"malloc up to the kernel - check that no allocations will follow\n");
	char * base;
	// malloc up to kernel
	base = malloc(KERNBASE-16);
	if (base == 0)
	{
		printf(1,"malloc up to kernel succeeded\n\n");
		return;
	}
	printf(1,"malloc up to kernel failed\n\n");
	exit();
}
void
forkCheck()
{
	uint numofpages = SMALL;
	printf(1,"fork check, check that only a small amount of pages being allocated while fork\n");
	char * base = malloc(PAGESIZE*numofpages);
	if (fork() == 0) {
		printf(1,"write to several pages\n",numofpages);
		base[PAGESIZE] = 0xFF;
		base[PAGESIZE*20] = 0xFF;
		base[PAGESIZE*50] = 0xFF;
		base[PAGESIZE*numofpages] = 0xFF;
		printf(1,"check for 4 allocations\n\n");
		exit();
	}
	wait();
}
int fib(int n) {
	if (n == 0 || n == 1) return n;
	return fib(n-1) + fib(n-2);
}
void
stackOverflow(){
	printf(1,"check stack overflow - run fib(10) and then run fib(10000)\n");
	printf(1,"fib(10)=%d succeeded\n",fib(10));
	printf(1,"fib(10000) succeeded=%d -  supposed to fail\n",fib(10000));
}
int
main(int argc, char *argv[])
{
	printf(1,"\nlazy tests\n");
	checkSmallChunk();
	checkBigChunk();
	mallocUpToKernel();
	forkCheck();
	stackOverflow(); //Supposed to fail
	exit();
}
