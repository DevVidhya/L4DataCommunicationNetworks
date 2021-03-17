#include<stdio.h>
#include<stdlib.h>
 
#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<unistd.h>

#include<string.h>

int main()
{
int fid=socket(AF_INET,SOCK_DGRAM,0);
if(fid==0)
printf("\n Socket failure ");

struct sockaddr_in server_address,client_address;
server_address.sin_family=AF_INET;
server_address.sin_port=htons(7070);
server_address.sin_addr.s_addr=INADDR_ANY;

if(bind(fid,(struct sockaddr *)&server_address, sizeof(server_address))<0)
printf("\n Error binding ");

int n,len=sizeof(client_address);
char temp,msg[100];
n=recvfrom(fid,msg,sizeof(msg),0,(struct sockaddr *) &client_address, &len);

printf("\n Received : %s ", msg);
for(int i=0,j=n-1;i<j;i++,j--)
{
temp=msg[i];
msg[i]=msg[j];
msg[j]=temp;
}

sendto(fid,msg,n,0,(struct sockaddr *) &client_address, len);
printf("\n Reverse message sent \n");
return 0;
}
