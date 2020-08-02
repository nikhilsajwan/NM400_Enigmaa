#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int BUFF_SIZE =1024;
void main(int argc, char **argv){
  

  int port = 5062;
  int sockfd;
  struct sockaddr_in serverAddr;
  char buffer[BUFF_SIZE];
  socklen_t addr_size;

  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  memset(&serverAddr, '\0', sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = inet_addr("192.168.1.8");

  strcpy(buffer, "Hello Server\n");
  
  sendto(sockfd, buffer, BUFF_SIZE, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
  printf("[+]Data Send: %s", buffer);
 

}




