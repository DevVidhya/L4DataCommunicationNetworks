#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<unistd.h>

#include<string.h>

int main()
{
int fid=socket(AF_INET,SOCK_STREAM,0);
if(fid==0)
printf("\n Socket failure ");

struct sockaddr_in server_address;
server_address.sin_family=AF_INET;
server_address.sin_port=htons(9000);
server_address.sin_addr.s_addr=INADDR_ANY;

if(bind(fid,(struct sockaddr *)&server_address, sizeof(server_address))<0)
printf("\n Binding failure ");

if(listen(fid,5)<0)
printf("\n Listening failure ");

int client_fid=accept(fid,NULL,NULL);
char msg[100],temp;

read(client_fid,msg,sizeof(msg));
printf("\n Received message %s ", msg);

for(int i=0,j=strlen(msg)-1;i<j;i++,j--)
{
temp=msg[i];
msg[i]=msg[j];
msg[j]=temp;
}

send(client_fid,msg,strlen(msg),0);
printf("\n Reverse message sent is %s", msg);

return 0;
}

