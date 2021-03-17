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
printf("\n Error creating socket ");

struct sockaddr_in server_address;
server_address.sin_family=AF_INET;
server_address.sin_port=htons(9000);
server_address.sin_addr.s_addr=INADDR_ANY;

if(bind(fid,(struct sockaddr *)&server_address, sizeof(server_address))<0)
printf("\n Error binding ");

if(listen(fid,5)<0)
printf("\n Error listening ");

int client_fid=accept(fid,NULL,NULL);
if(client_fid<0)
printf("\n Error accepting ");

int count=0,val;
while(1)
{
read(client_fid,&val,sizeof(val));
if(count==val)
{
printf("\n Received : %d \n", val);
count++;
}
if(val==5)
count=0;
memset(&val,'\0',sizeof(val));


send(client_fid,&count,sizeof(count),0);
if(count==0)
break;
}

return 0;
}

