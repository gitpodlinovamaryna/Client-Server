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
        int m_newClient;
        int m_port;
        int m_buffesSize;
        int m_maxClients;
        char m_msg[1024];
        std::string m_ipAddress;
        std::string m_responseData;
        std::string m_receiveData;
        struct sockaddr_in serv_addr;
        keepaliveOpt m_keepaliveOpt;
            
    public:

        TcpServer();
        TcpServer(int);                 // Constructor
        TcpServer(std::string,int);     // Constructor with param
        ~TcpServer();                   // Destructor
        void init();                
        void createSocket();            // Create new socket
        void bindPort();                //Bind to port
        void listenToClients();         //Listen clients
        void acceptClient();
        void sendMsg();                 //Send message to client
        std::string receiveMsg();       //Receive message from client
        void handle();

};
    
}
#endif