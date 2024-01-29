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

int sys_getkernelstartaddr(void){
  return KERNBASE;
}

int sys_getkernelendaddr(void){
  return KERNBASE+PHYSTOP;
}

int sys_getkernelvaraddr(void){
  int a = 0;
  // address &a
  return  (int)&a;
}

int sys_getsystemcalladdr(void){
  return (int)sys_fork;
}

int
sys_getyear(void)
{
  return 1975;
}

int
sys_getmysize(void)
{
  return myproc()->sz;
}

int sys_setpriority(void){
  int a;
  if(argint(0, &a) < 0)
    return -1;
  myproc()->priority = a;
  return a;
}

int
sys_myps(void)
{
    char *copy;
    char *s;
    int copysize;
    struct proc *pt;

    if (argint(0, &copysize) <0){
        return -1;
    }


    if (argptr(1, &copy,copysize) <0){
        return -1;
    }

    struct proc *procCopy;

    procCopy = procps();

    

    s=copy;


    // while(pt + copysize > s){
    //     *(int *)s = 1;
    //     s+=4;
    //     *(int *)s = 2;
    //     s+=4;
    // }
    int  counter =0;
    for(pt = procCopy; pt < &procCopy[NPROC]; pt++){
      //  if(pt->state == UNUSED) {
          // cprintf("%d %s", pt->sz, pt->name);
          *(uint *)s = pt->sz;
          s += sizeof(uint);

          *(int *)s = pt->state;
          s += sizeof(int);

          *(int *)s=pt->pid;
          s+=sizeof(int);

          strncpy(s, pt->parent->name, 16);
          s += (sizeof(char)) * 16;

          *(int *)s=pt->parent->pid;
           s+=sizeof(int);

          *(int *)s=pt->killed;
           s+=sizeof(int);

          // *(uint *)s=pt->cwd->inum;
          //  s+=sizeof(uint);

          //  *(int *)s=*(pt->cwd)->inum;
          //  *(uint *)s=01010;
          //  s+=sizeof(int);


          strncpy(s, pt->name, 16);
          s += (sizeof(char)) * 16;

          counter++;
          if(counter>5) break;
      //  }
      
    }

    return 1;
}
