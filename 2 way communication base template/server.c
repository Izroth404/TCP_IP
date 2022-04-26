#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(){

    char *ip = "127.0.0.1";
    int port = 5562;

    int c_sock , s_sock;
    struct sockaddr_in s_addr, c_addr;
    socklen_t a_size;
    char buffer[1024];
    int n;

    s_sock = socket(AF_INET, SOCK_STREAM , 0);
    if(s_sock < 0){
        perror("[-]Socket Error");
        exit(1);
    }
    printf("[+]TCP Socket Created\n");

    memset(&s_addr , '\0' , sizeof(s_addr));
    s_addr.sin_family = AF_INET;    
    s_addr.sin_port = port;
    s_addr.sin_addr.s_addr =inet_addr(ip);

    n = bind(s_sock, (struct sockaddr*)&s_addr, sizeof(s_addr));
    if(n<0){
        perror("[-]Bind Error\n");
        return 1;
    }

    printf("[+]Bind to the port number: %d\n", port);

    listen(s_sock, 5);
    printf("Listening....\n");

        a_size = sizeof(c_addr);
        c_sock = accept(s_sock , (struct sockaddr*)&c_addr , &a_size);
        printf("[+]Client Connected\n");
        
    while(1){
        bzero(buffer , 1024);
        recv(c_sock , buffer , sizeof(buffer) , 0) ;
        printf("Client: %s\n" , buffer);

        bzero(buffer, 1024);
        char c[100];
        printf("Server: ");
        gets(c);
        strcpy(buffer ,c);
        //printf("%s\n", buffer);
        if(strcmp(c,"exit")==0) break;

        send(c_sock, buffer , strlen(buffer), 0);
    }


    close(c_sock);
    printf("[+]Client Disconnected\n\n");

    return  0;

}