#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 8080
int main(int args,char* argv[]){

        char buffer[1024] = {};

        struct sockaddr_in address;

        int client_fd = socket(AF_INET,SOCK_STREAM,0);
       
        char* hello = "Hello from client end";

        if(client_fd < 0){
            perror("");
        }

        address.sin_family = AF_INET;
        address.sin_port = htons(PORT);
    
        int status = connect(client_fd,(struct sockaddr*)&address,sizeof(address));

         send(client_fd,hello,strlen(hello),0);

         ssize_t val = read(client_fd,buffer,1024-1);

         printf("%s\n",buffer);

        close(client_fd);
}
