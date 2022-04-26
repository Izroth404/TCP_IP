#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(){

    char *ip = "127.0.0.1";
    int port = 5562;

    int sock;
    struct sockaddr_in addr;
    socklen_t a_size;
    char buffer[1024];
    int n;

    sock = socket(AF_INET, SOCK_STREAM , 0);
    if(sock < 0){
        perror("[-]Socket Error");
        //exit(1);
        return 1;
    }
    printf("[+]TCP Socket Created\n");

    memset(&addr , '\0' , sizeof(addr));
    addr.sin_family = AF_INET;    
    addr.sin_port = port;
    addr.sin_addr.s_addr =inet_addr(ip);

    connect(sock , (struct sockaddr*)&addr , sizeof(addr));
    printf("Connected to the server\n");

    while(1){
        bzero(buffer , 1024);
        char str[100];
        printf("[+]Client: ");
        gets(str);
        strcpy(buffer , str);
        //printf("Client: %s\n" , buffer);
        
        if(strcmp("exit",str)==0)break;
        send(sock , buffer , strlen(buffer) , 0);

        bzero(buffer , 1024);

        recv(sock, buffer , sizeof(buffer) , 0);
        printf("server: %s\n", buffer );
    }

    close(sock);
    printf("Disconencted from server\n\n");

    return 0;
}