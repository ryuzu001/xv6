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
  int status;
  if(argint(0, &status) < 0)
    return -1;

    exit(status);
  return 0;  // not reached
}

int
sys_wait(void)
{
  int *status;
  argptr(0, (char**)&status, sizeof(int*));
  return wait(status);
}

// CS153 - wait, exit, waitpid, helloworld

void
sys_hello()
{
	// cprintf("Hello from kernel space!\n");
	return;
}
// CS153 - added hello and waitpid, touched exit and wait
int
sys_waitpid(void)
{
	int *status;
	int pid, options;
	if(argint(0, &pid) < 0)	// SET PID
	  return -1;

	argptr(1, (char**)&status, sizeof(int*));	// SET STATUS

	if(argint(2, &options) < 0)	// SET OPTIONS
	  return -1;

	return waitpid(pid, status, options);
}


// CS153 - change priority lab2
void
sys_setPriority(void){
   int pr;
   if(argint(0, &pr) < 0)
	return;
   setPriority(pr);
   return; 
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
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

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
    if(myproc()->killed){
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
