#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
int main(){
char *ip = "127.0.0.1";
int port = 5562;
int sock;
struct sockaddr_in addr;
socklen_t addr_size;
char buffer[1024];
int n;
sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock < 0){
perror("[-]Socket error");
return 1;
}
printf("[+]TCP server socket created.\n");
memset(&addr, '\0', sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_port = port;
addr.sin_addr.s_addr = inet_addr(ip);
connect(sock, (struct sockaddr*)&addr, sizeof(addr));
printf("Connected to the server.\n");

while(1){
bzero(buffer, 1024);
char str[100];
printf("Client: ");
gets(str);
if(strcmp(str,"exit")==0 || strcmp(str,"EXIT")==0 || strcmp(str,"Exit")==0){
close(sock);
break;
}
char str1[100]={0};
int k=(str[0]=='0')? 0:1;
int x=0;
str1[x] = str[0];
for(int i= 1; i<strlen(str); i++){
if(k==5){
str1[++x] = '0';
k=0;
}
if(str[i] == '1' && str[i-1] == '1' ){
str1[++x] = str[i];
// printf("%s\n", str1);
k++;
}else{
str1[++x] = str[i];
k=0;
}
}

strcpy(buffer, str1);
printf("Client: %s\n", buffer);
send(sock, buffer, strlen(buffer), 0);

bzero(buffer, 1024);
recv(sock, buffer, sizeof(buffer), 0);
printf("Server: %s\n", buffer);
}
close(sock);
printf("Disconnected from the server.\n");
return 0;
}
