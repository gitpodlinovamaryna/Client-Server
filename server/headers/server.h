#ifndef SERVER_H
#define SERVER_H

#include <iostream> 
#include <cstdio> 
#include <cstring> 
#include <string> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h> 
#include <netdb.h> 
#include <netinet/in.h>	   
#include <netinet/tcp.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <thread>
#include <mutex>
#include <shared_mutex>

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
        int number;
        char m_msg[1024];
        std::string m_ipAddress;
        struct sockaddr_in serv_addr;
        struct sockaddr_in client_addr;
        struct keepaliveOpt m_keepaliveOpt;
            

    public:

        TcpServer();
        TcpServer(int);                 // Constructor
        TcpServer(std::string,int);     // Constructor with param
        ~TcpServer();                   // Destructor
        void init();                    // Initializer
        void fillServAddr();             
        void createSocket();            // Create new socket
        void bindPort();                // Bind to port
        void listenToClients();         // Listen clients
        void acceptClient();            // Set connection with client
        void sendMsg();                 // Send message to client
        std::string receiveMsg();       // Receive message from client
        void messageExchange();         // Regulates the order in which messages are exchanged between the client and the server
};
    
}
#endif