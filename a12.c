#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 8081
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

        char* arr[5] = {"abc","def","ghi","jkl","mno"};
        // printf("%s",arr[0]);
        int i=0;
        while(i<5){
            send(client_fd,arr[i],strlen(arr[i]),0);
            ssize_t val = read(client_fd,buffer,1024-1);
             printf("%s\n",buffer);
            i++;
        }
        //  ssize_t val = read(client_fd,buffer,1024-1);

        //  printf("%s\n",buffer);

        close(client_fd);
}
