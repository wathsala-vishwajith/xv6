#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

#define NUM_STRUCTS 64


struct procstruct {
  uint sz;                     // Size of process memory (bytes)
  int state;        // Process state
  int pid;                     // Process ID
  char parentname[16];          // Parent process
  int parentpid;                 //Parent PID
  int killed;                  // If non-zero, have been killed
//   uint  inum;           // Current directory
  char name[16];               // Process name (debugging)
};

int main(void) {

    struct procstruct copyproc[NUM_STRUCTS];
    struct procstruct *prc;



    int return_val = myps(NUM_STRUCTS*sizeof(struct procstruct),&copyproc);
    prc = &copyproc[0];

    printf(1,"Name\t State\t PID\t  Parent\t ParentPID\t Killed\t Size\n");
    while(prc != &copyproc[NUM_STRUCTS]){
        if(prc->pid == 0){
            prc++;
            continue;
            
        }
        printf(1,"%s\t %d\t %d\t  %s\t %d\t %d\t %d \n",prc->name,prc->state, prc->pid, prc->parentname,prc->parentpid,prc->killed, prc->sz);
        prc++;
    }

    printf(1, "Program %d \n", return_val);
    exit();
}
