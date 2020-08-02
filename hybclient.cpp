#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <pthread.h>

using namespace std;
int sock;
int port;
string ipAddress;
sockaddr_in hint;
int connectRes;
char buf[4096];
string userInput;

int BUFF_SIZE =1024;
int portu = 5062;//udp port on server
 int sockfd;
 sockaddr_in serverAddr;
 
  socklen_t addr_size;
 
void readyTcp(){
 //	Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        //return 1;
        
    }

    //	Create a hint structure for the server we're connecting with
    port = 5060;
    ipAddress = "192.168.1.8";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        //return 1;
    }

}

void readyUdp(){
sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  memset(&serverAddr, '\0', sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portu);
  serverAddr.sin_addr.s_addr = inet_addr("192.168.1.8");

}
void *udpc(void *ar){
char buffer[BUFF_SIZE];
int n=0;
while(true){


strcpy(buffer, "hello server");
  
  sendto(sockfd, buffer, BUFF_SIZE, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
  printf("\r [+]Data Send: %s", buffer);
  }
}
void *tcpc(void *ar){

    do {
        //		Enter lines of text
        cout << "> ";
        getline(cin, userInput);

        //		Send to server
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //		Display response
            cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
        }
    } while(true);

    //	Close the socket
    close(sock);
}

int main()
{
   readyTcp();
   readyUdp();
    //	While loop:
    pthread_t tcp;
      pthread_t udp;
    pthread_create(&tcp,NULL,tcpc,NULL);
    pthread_create(&udp,NULL,udpc,NULL);
    pthread_join(tcp, NULL);
     pthread_join(udp, NULL);



    return 0;
}
