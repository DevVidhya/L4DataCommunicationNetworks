#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

#include<string.h>

int main()
{
int server_socket=socket(AF_INET,SOCK_STREAM,0);
if(server_socket==0)
printf("Socket failure \n");

struct sockaddr_in server_address,client_address;
memset(&server_address, '\0' , sizeof(server_address));                            // sometimes doesn't work properly if memset is not used
memset(&client_address, '\0' , sizeof(client_address));
server_address.sin_family=AF_INET;
server_address.sin_port=htons(9002);
server_address.sin_addr.s_addr=INADDR_ANY;

if((bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)))<0)
printf("Error binding \n");

if(listen(server_socket,5)<0)
printf("Error listening \n");

int len=sizeof(client_address);
int client_socket=accept(server_socket, (struct sockaddr *) &client_address, &len);
if(client_socket<0)
printf("Error accepting \n");

char msg[100],temp;
recv(client_socket, msg, 1024, 0);

int i,j,l=strlen(msg);
for(i=0,j=l-1;i<j;i++,j--)
{
temp=msg[i];
msg[i]=msg[j];
msg[j]=temp;
}

send(client_socket, msg, sizeof(msg), 0);
printf("Reversed message sent \n");

//close(server_socket);

return 0;
}




