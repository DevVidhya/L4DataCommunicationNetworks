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
server_address.sin_port=htons(9999);
server_address.sin_addr.s_addr=INADDR_ANY;

if(bind(fid,(struct sockaddr *)&server_address, sizeof(server_address))<0)
printf("\n Binding failure ");

if(listen(fid,5)<0)
printf("\n Listening failure ");

int client_fid=accept(fid,NULL,NULL),count=0,val;

while(1)
{
read(client_fid,&val,sizeof(val));
if(val==count)
{
count++;
printf("\n Received message %d \n", val);
}
memset(&val,'\0',sizeof(val));

send(client_fid,&count,sizeof(count),0);
}

return 0;
}

