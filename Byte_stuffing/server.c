#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
int main(){
char *ip = "127.0.0.1";
int port = 5562;
int server_sock, client_sock;
struct sockaddr_in server_addr, client_addr;
socklen_t addr_size;

char buffer[1024];
int n;
server_sock = socket(AF_INET, SOCK_STREAM, 0);
if (server_sock < 0){
perror("[-]Socket error");
exit(1);
}
printf("[+]TCP server socket created.\n");
memset(&server_addr, '\0', sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = port;
server_addr.sin_addr.s_addr = inet_addr(ip);
n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
if (n < 0){
perror("[-]Bind error");
exit(1);
}
printf("[+]Bind to the port number: %d\n", port);
listen(server_sock, 5);
printf("Listening...\n");
addr_size = sizeof(client_addr);
client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
printf("[+]Client connected.\n");
while(1){
bzero(buffer, 1024);
recv(client_sock, buffer, sizeof(buffer), 0);
printf("Client: %s\n", buffer);

if(strcmp(buffer,"exit")==0 || strcmp(buffer,"EXIT")==0 || strcmp(buffer,"Exit")==0 &&
strcmp(buffer,"")==9)
break;
char str[100] = {0};
int k= buffer[0]=='0'? 0:1;
int x =0 ;
str[x] = buffer[0];
for(int i=0 ; i<strlen(buffer)-1 ; i++ ){
if(k==4){++i;k=0;}
if(buffer[i] == '1' && buffer[i+1] == '1'){
str[x] = buffer[i];
k++;++x;
}else{
str[x] = buffer[i];
k=0;x++;

}}
str[x] = buffer[strlen(buffer)-1];
if(strcmp(str,"")==0)
break;
bzero(buffer, 1024);
strcpy(buffer, str);
printf("Server: %s\n", buffer);
send(client_sock, buffer, strlen(buffer), 0);
}close(client_sock);
printf("[+]Client disconnected.\n\n");
return 0;
}
