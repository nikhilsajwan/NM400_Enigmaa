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
#include <time.h>
#include <pthread.h>

using namespace std;
int k=0;
int sock;
int port;
string ipAddress;
sockaddr_in hint;
int connectRes;
 clock_t start, end1, end2,tcp;
  double tt1,tt2;//time taken
//char buf[4096];
string userInput;
char buf8[12];
char buf16[32];
char buf32[72];
char buf64[155];
char buf128[327];
int bs1 =12;
int bs2 =32;
int bs3 =72;
int bs4 =155;
int bs5 =327;
int mode=5;
//char* er ='er';

int BUFF_SIZE =12;
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

char* udpbuff(){

switch(mode){
case 1:
memset(buf8, 'x', 12);
memset(buf8, '1', 1);
return buf8;
break;
case 2:
memset(buf16, 'x', 32);
memset(buf16, '2', 1);
return buf16;
break;
case 3:
memset(buf32, 'x', 72);
memset(buf32, '3', 1);
return buf32;
break;
case 4:
memset(buf64, 'x', 155);
memset(buf64, '4', 1);
return buf64;
break;
case 5:
memset(buf128, 'x', 327);
memset(buf128, '5', 1);
return buf128;
break;
default:
printf("error");
///return e;
}




}
char* tcpbuff(){

switch(mode){


case 1:
memset(buf16, 'x', 32);
memset(buf16, '2', 1);
return buf16;
break;
case 2:
memset(buf32, 'x', 72);
memset(buf32, '3', 1);
return buf32;
break;
case 3:
memset(buf64, 'x', 155);
memset(buf64, '4', 1);
return buf64;
break;
case 4:
memset(buf128, 'x', 327);
memset(buf128, '5', 1);
return buf128;
case 5:
memset(buf128, 'x', 327);
memset(buf128, '5', 1);
return buf128;
break;
default:
printf("error");
///return e;

}




}




void *udpc(void *ar){
//char buffer[BUFF_SIZE];
int n=0;
while(true){


   	

usleep(20000);
//char * buffer=udpbuff();

//strcpy(buffer, "hello server");
 char *buf;
		switch(mode){
case 1:
memset(buf8, 'x', 12);
memset(buf8, '1', 1);
buf= buf8;
break;
case 2:
memset(buf16, 'x', 32);
memset(buf16, '2', 1);
buf=buf16;
break;
case 3:
memset(buf32, 'x', 72);
memset(buf32, '3', 1);
buf= buf32;
break;
case 4:
memset(buf64, 'x', 155);
memset(buf64, '4', 1);
buf= buf64;
break;
case 5:
memset(buf128, 'x', 327);
memset(buf128, '5', 1);
buf=buf128;
break;
default:
printf("error");
///return e;
}


  
  sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
  k++;
  if (k>25){
  printf("\r [+]Data Send: %s mode %d", buf, mode);
  k=0;
  }
  }
}
void *tcpc(void *ar){

    do { usleep(500000);
        //		Enter lines of text
       // cout << "> ";
        //getline(cin, userInput);
		//char *buf=tcpbuff();
	
        //		Send to server
        
char * buffer;
		switch(mode){
case 1:
memset(buf8, 'x', 12);
memset(buf8, '1', 1);
buffer= buf8;
break;
case 2:
memset(buf16, 'x', 32);
memset(buf16, '2', 1);
buffer=buf16;
break;
case 3:
memset(buf32, 'x', 72);
memset(buf32, '3', 1);
buffer= buf32;
break;
case 4:
memset(buf64, 'x', 155);
memset(buf64, '4', 1);
buffer= buf64;
break;
case 5:
memset(buf128, 'x', 327);
memset(buf128, '5', 1);
buffer=buf128;
break;
default:
printf("error");
///return e;
}



         start = clock();
        
        int sendRes = send(sock, buffer, sizeof(buffer) , 0);
       
        if (sendRes == -1)
        {
        end2=clock();
   tt2= (((double) (end2 - start))*1000000) / CLOCKS_PER_SEC;
   if (tt2>200)
   {if (mode>1)
   {
   mode--;
   }
   start = clock();
   
   }
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }
	 end1=clock();
        //		Wait for response
        
        int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
        if (bytesReceived == -1)
        {
        end2=clock();
   tt2= (((double) (end2 - start))*1000000) / CLOCKS_PER_SEC;
   if (tt2>200)
   {if (mode>1)
   {
   mode--;
   }
   start = clock();
   
   }
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
        end2=clock();
        tt1=(((double) (end1 - start)) *1000000)/ CLOCKS_PER_SEC;
       tt2= (((double) (end2 - start))*1000000) / CLOCKS_PER_SEC;
            //		Display response
            cout << "SERVER> " << string(buffer, bytesReceived) << "time taken ack"<<tt1<<"time taken response"<<tt2<< "\r\n";
            if(tt2<70.0)
            {
            if (mode<5)
            {mode++;
            }
            
            }
            else if (tt2>110)
            {
            if (mode>1)
            {
            mode--;
            
}
            }

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
