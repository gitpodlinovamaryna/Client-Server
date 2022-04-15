#ifndef SERVER_H
#define SERVER_H

#include <iostream> 
#include <cstdio> 
#include <cstring> 
#include <string> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
#include <netinet/in.h>	   
#include <netinet/tcp.h> 
#include <unistd.h>

namespace MyServer
{

struct keepaliveOpt
        {
            int idle;
            int cnt;
            int intvl;
        };


class TcpServer
{
    private:
        
        int m_serverSocket;
        int m_port;
        int m_buffesSize;
        int m_maxClients;
        std::string m_ipAddress;
        std::string m_responseData;
        std::string m_receiveData;
        struct sockaddr_in serv_addr;
        keepaliveOpt m_keepaliveOpt;
            
    public:

        TcpServer();                    // Constructor
        TcpServer(std::string,int);     // Constructor with param
        ~TcpServer();                   // Destructor
        void createSocket();            // Create new socket
        int  setKeepalive (int sock);    //Set Keepalive options
        void bindPort(int);             //Bind to port
        void listenToClients(int);      //Listen clients
        void sendMsg();                 //Send message to client
        void receiveMsg(int);           //Receive message from client
        void handle();

};
    
}
#endif