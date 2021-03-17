#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void* recieve(void *fid)
{
    int new_fid = *((int *)fid);
    char recvmsg[500];
    
    while(recv(new_fid,recvmsg,sizeof(recvmsg),0)>0)
    {
        fputs(recvmsg,stdout);
        memset(recvmsg,'\0',sizeof(recvmsg));
    }
}

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        printf("less number of arguements\n");
        return 0;
    }
    char username[50];
    strcpy(username,argv[1]);
    int port = atoi(argv[2]);

    int fid = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    connect(fid,(struct sockaddr*) &server_addr,sizeof(server_addr));

    printf("%s connected, start chatting\n",username);

    //thread for recieving 
    pthread_t recvthread;
    pthread_create(&recvthread,NULL,&recieve,&fid);
    char sentmsg[250];

    //for sending the data
    while(fgets(sentmsg,250,stdin)>0)
    {
        char res[500];
        strcpy(res,username);
        strcat(res,": ");
        strcat(res,sentmsg);
        send(fid,res,sizeof(res),0);
    }

    return 0;
    
}