#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<unistd.h>

#include<string.h>
#include<pthread.h>

int clients[100],n=0;

void sendtoall(int fid, char msg[])
{
for(int i=0;i<n;i++)
if(clients[i]!=fid)
send(clients[i],msg, strlen(msg),0);
}

void* receive(void *client_fid)
{
int fid= *((int *)client_fid);
char msg[100];
while(read(fid,msg,sizeof(msg))>0)
{
sendtoall(fid,msg);
memset(msg,'\0',sizeof(msg));
}
}

int main()
{
int fid=socket(AF_INET,SOCK_STREAM,0);
if(fid==0)
printf("\n Socket failure ");

struct sockaddr_in server_address;
server_address.sin_family=AF_INET;
server_address.sin_port=htons(7007);
server_address.sin_addr.s_addr=INADDR_ANY;

if(bind(fid,(struct sockaddr *)&server_address, sizeof(server_address))<0)
printf("\n Error binding ");

if(listen(fid,5)<0)
printf("\n Error listening ");

pthread_t recvt;
while(1)
{
int client_fid=accept(fid,NULL,NULL);
printf("%d connected\n",client_fid);
//printf("%d Accepting\n",client_fid);
clients[n]=client_fid;
n++; 
pthread_create(&recvt, NULL, receive, &client_fid);
}

}
