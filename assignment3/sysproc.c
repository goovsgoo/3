#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr=proc->sz;

  if(n >= 0)
    {
      if (proc->sz + n >= KERNBASE){ //not allow a process to request virtual addresses that belong kernel
        return -1;
      }
      else
      {
    	  //cprintf("test missed kernbase--------------------------\n");
//    	  if(growproc(n) < 0)
//    	         return -1;
        proc->sz += n; //we increase the sz which is the way we cheat the process that it got the enough resources.
      }
    }
  else if (n < 0) //Reduce heap size by deallocating
   {
     if(growproc(n) < 0)
       return -1;
   }
  return addr;  //we returned the origin memory address as the result and comment the page allocation call.
}


//int
// sys_sbrk(void)
// {
//   int addr;
//   int n;
//
//   if(argint(0, &n) < 0)
//     return -1;
//   addr = proc->sz;
//   if(growproc(n) < 0)
//     return -1;
//   return addr;
// }


int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
