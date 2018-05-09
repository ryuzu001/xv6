#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
cat(int fd)
{
  int status = 1;
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(1, buf, n) != n) {
      printf(1, "cat: write error\n");
      //exit();
      exit(status);
    }
  }
  if(n < 0){
    printf(1, "cat: read error\n");
    //exit();
    exit(status);
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;
  int status = 1;
  int failstatus = 0;

  if(argc <= 1){
    cat(0);
    //exit();
    exit(failstatus);
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      //exit();
      exit(failstatus);
    }
    cat(fd);
    close(fd);
  }
  //exit();
  exit(status);

  return 0;
}
