#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

// CS153 - ADDED THIS FILE

int main()
{
	hello();		// calls system call helloworld
//	printf(1, "Hello from user space!\n");	// calls non-system call hello world
	exit(1);
	return 1; 	// not reached
}
