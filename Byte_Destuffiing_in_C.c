
Please ignore this is bad code...




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
  char c[1024];
  // printf("Enter the number: \n");
  gets(&c);
  int k= c[0]=='1'? 1:0,x=0;
  char buff[1024] = {0};
//   printf("%s\n", buff);
  // buff[0] = c[0];
  for(int i=0 ; i<strlen(c)-1 ;i++){
    if(k==4){
      k=0;
      ++i;
//       printf("if k: %d\n", k);
    }
    else if(c[i]=='1'&& c[i+1]=='1'){
      buff[x] = c[i];
      printf("k : %d\n", k);
      ++k;x++;
    }else{
      buff[x] = c[i];
//       printf("else buff[%d]: %s\n",x,buff);
      k=0;x++;
    }
  }
  buff[x] = c[strlen(c)-1];
//   printf("x: %d\n", x);
  printf("%s\n",buff);
}
