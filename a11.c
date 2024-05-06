#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 8081

void reverse(char* arr){
    int len = strlen(arr);
    for(int i=0;i<len/2;i++){
        char tmp = arr[i];
        arr[i] = arr[len-i-1];
        arr[len-i-1] = tmp;
    }
}

int main(int args,char* argv[]){

        

        struct sockaddr_in address;

        socklen_t addrlen = sizeof(address);


        int server_fd = socket(AF_INET,SOCK_STREAM,0);

                    char buffer[1024] = {};

        char* hello = "Hello from Server end";

        if(server_fd < 0){
            perror("");
        }

            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons(PORT);

        if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0){
            perror("");
        }

        if(listen(server_fd,3)<0){
            perror("");
        }

         int newsocket=accept(server_fd,(struct sockaddr*)&address,&addrlen);
            if(newsocket<0){
                perror("error");
            }
      
        int i=0;
        while(i<5){
             ssize_t val = read(newsocket,buffer,1024-1);
            buffer[val] = '\0';
            reverse(buffer);
            printf("%s",buffer);
            printf("\n");
            memset(buffer,0,sizeof(buffer));
            send(newsocket,hello,strlen(hello),0);
           
            i++;
        }

        

        // send(newsocket,hello,strlen(hello),0);
        
        // printf("message sent from server");

       close(server_fd);
    //    close(newsocket);
}
