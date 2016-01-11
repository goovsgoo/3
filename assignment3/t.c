#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

#define PS 4096

void
rec(){
	rec();
}

void
test1(){
	int* m = (int *) malloc(PS*100);
	if(m==0)
	{
		printf(1,"malloc failed");
		exit();
	}
}
void
test2(){
	int* m = (int *) malloc(PS * 1024);
	*m=17;
	*(m+PS)=42;
	*(m+4*PS)=114;
	if(!(*m==17 && *(m+PS)==42 && *(m+PS*4)==114))
	{
		printf(1,"write didnt worked properlly");
		exit();
	}
}
void
test3(){
	int* m = (int *) malloc(PS*100*1024);
		if(m==0)
		{
			printf(1,"malloc failed");
			exit();
		}
}
void
test4(){
	int* m = (int *) malloc(KERNBASE - 100);
	if(m!=0)
	{
		printf(1,"malloc in kernel");
		exit();
	}
}
void
test5(){
	int* m1 = (int *) malloc(PS*100);
	int* m2 = (int *) malloc(PS*100);

	*m1=7;
	if(!fork())
	{
		*m1=70;
		*m2=30;
		exit();
	}
	wait();

}
void
test6(){
	if(!fork())
	{
		rec();
		exit();
	}
	wait();
}



int
main(int argc, char *argv[])
{
	 printf(1, "\n\n**************************\n***** utest starting *****\n**************************\n\n");

	  printf(1, "\n*****TEST 1 STARTED*****");
	  test1();
	  printf(1, "\n*****TEST 1 ended*****");

	  printf(1, "\n*****TEST 2 STARTED*****");
	  test2();
	  printf(1, "\n*****TEST 2 ended*****");

	  printf(1, "\n*****TEST 3 STARTED*****");
	  test3();
	  printf(1, "\n*****TEST 3 ended*****");

	  printf(1, "\n*****TEST 4 STARTED*****");
	  test4();
	  printf(1, "\n*****TEST 4 ended*****");

	  printf(1, "\n*****TEST 5 STARTED*****");
	  test5();
	  printf(1, "\n*****TEST 5 ended*****");

	  printf(1, "\n*****TEST 6 STARTED***** should fail with trap 14\n");
	  test6();
	  printf(1, "\n*****TEST 6 ended*****");


		return 0;
}
