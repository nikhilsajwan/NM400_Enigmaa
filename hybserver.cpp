 #include <iostream>
 #include<stdio.h>
 #include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 
#include <time.h>
 
using namespace std;

//char buffer[1024];
int listening=-1;
int port =5062;
int sockfd;
socklen_t addr_size;
 //char buf[4096];
 int clientSocket;
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


 sockaddr_in si_me, si_other;

  
      sockaddr_in hint;
    
    
    
    sockaddr_in client;
    socklen_t clientSize ;
 
  
  
  
    // Create a socket tcp
  void creater()
  
  {   clientSize= sizeof(client);
   // Create a socket udp
 	 sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  
   memset(&si_me, '\0', sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(port);
  si_me.sin_addr.s_addr = inet_addr("0.0.0.0");
  
  hint.sin_family = AF_INET;
    hint.sin_port = htons(5060);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
  
  listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        
    }
 	
 	 
 	 }
  // bind udp
  void binder(){
  	
bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me));
    // Bind the ip address and port to a socket tcp

    bind(listening, (sockaddr*)&hint, sizeof(hint));
 addr_size = sizeof(si_other);
 }
 
 void listener(){
    // Tell sock the socket is for listening
    listen(listening, SOMAXCONN);}
 
    // Wait for a connection
    void waittcp(){
    
    
 
    clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }
 
    // Close listening socket
   // close(listening);
 }
 char* tcpbuff(){

memset(buf128, 0, 327);
memset(buf128, '5', 1);
return buf128;







}
char* udpbuff(){


memset(buf128, 0, 327);
memset(buf128, '5', 1);
return buf128;

}


    // While loop: accept and echo message back to client
   void *tcps(void *vargp){
    while (true)
    { //waittcp();
       
       //char *buf = tcpbuff();
       memset(buf128, 0, 327);
       
       
 
        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf128, 327, 0);
        if (bytesReceived == -1)
        {
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }
 
        if (bytesReceived == 0)
        {
            cout << "Client disconnected " << endl;
            break;
        }
 
        cout << string(buf128, 0, bytesReceived) << endl;
 
        // Echo message back to client
        send(clientSocket, buf128, bytesReceived, 0);
    }
    // Close the socket
    close(clientSocket);
   
   }
   void *udps(void *vargp){
   while(true)
    {
    //char * buffer = udpbuff();
    memset(buf128, 0, 327);
    
         recvfrom(sockfd, buf128, 327, 0, (struct sockaddr*)& si_other, &addr_size);
  printf("\r [+]Data Received: %s", buf128);
  
 }
   
   
   }
 
int main()
{   creater();
	binder();
	listener();
	waittcp();
	pthread_t tcpt;
	pthread_t udpt;
	pthread_create(&udpt, NULL, udps, NULL); 
	pthread_create(&tcpt, NULL, tcps, NULL); 
	
   	
  	 pthread_join(udpt, NULL); 
  	 pthread_join(tcpt, NULL); 
	
 
    
 
    return 0;
}
