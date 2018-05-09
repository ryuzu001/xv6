#include "types.h"
#include "user.h"
int main(){
	int testStarvation(void);

	testStarvation();

	exit(0);

	return 0;
}

int testStarvation(){

	int pritest = 1;

	printf(1, "Setting priority to 3\n");


	for(int i = 0; i < 3; i++){	
  	  int pid = fork();
	  setPriority(3);
	  if(pid == 0){
	    printf(1, "Hello, this is child %d and I will change my priority to %d\n", getpid(), pritest);
	    setPriority(pritest);
	    for(int j = 0; j < 50000; j++){
		for(int k = 0; k < 10000; k++){
		  asm("nop");}}
	    printf(1, "child %d with priority %d has finished\n", getpid(), pritest);
	  }
	  else{
	    continue;
	  }
	}
	return 0;
}
