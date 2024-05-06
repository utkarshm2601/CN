#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 8081

int top = -1, stack [100];

void push (int n){
   top++;
   stack [top] = n;
}

int pop ( ){
   int res ;
   res = stack [top];
   top--;
   return res;
}

int eval (char ch, int op1, int op2){
   switch (ch){
      case '+' : return (op1+op2);
      case '-' : return (op1-op2);
      case '*' : return (op1*op2);
      case '/' : return (op1/op2);
   }
   return 0;
}

int i,op1,op2,res,x;
 

 double calculate(char* a){
    
    for(i=0; a[i]!='\0'; i++){
      char ch = a[i];
      if (ch>='0' && ch<='9')
         push(ch-'0');
      else{
         op2 = pop ( );
         op1 = pop ( );
         res = eval (ch, op1, op2);
         push (res);
      }
   }
    x = pop ();
    return x;
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
        while(i<2){
            ssize_t val = read(newsocket,buffer,1024-1);
            buffer[val] = '\0';
            int result = calculate(buffer);
            printf("%d",result);
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
