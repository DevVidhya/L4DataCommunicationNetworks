#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int clients[1000],n=0;


void sendtoall(int fid,char msg[])
{
    for(int i=0;i<n;i++)
    {
        if(clients[i]!=fid)
        {
            send(clients[i],msg,strlen(msg),0);
        }
    }
}

void* receive(void *client_fid)
{
    int fid = *((int *)client_fid);
    char msg[300];
    while(read(fid,msg,sizeof(msg))>0)
    {
        sendtoall(fid,msg);
        memset(msg,'\0',sizeof(msg));
    }

    //disconnection
    printf("%d disconnected",fid);
    for(int i=0;i<n;i++)
    {
        if(clients[i]==fid)
        {
            for(int j=i+1;j<n;j++)
            clients[j-1]=clients[j];
        }
    }
    n--;
}

int main(int argc,char *argv[])
{
    int fid = socket(AF_INET,SOCK_STREAM,0);
    int port = atoi(argv[1]);
    struct sockaddr_in  server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(fid,(struct sockaddr*)&server_addr,sizeof(server_addr));
    listen(fid,2);

    pthread_t recvt;
    while(1)
    {
        int client_fid=accept(fid,NULL,NULL);
        printf("%d connected\n",client_fid);
        clients[n]=client_fid;
        n++;
        pthread_create(&recvt,NULL,receive,&client_fid);
    }

    return 0;
}
