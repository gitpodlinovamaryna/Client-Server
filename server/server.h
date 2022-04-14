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
            int m_client;
            int m_port;
            std::string m_ipAddress;
            std::string m_responseData;
            struct sockaddr_in serv_addr;
            keepaliveOpt m_keepaliveOpt;

    public:

        TcpServer();  // Initializer
        TcpServer(std::string,int); 
        ~TcpServer();           // Destructor
        int createSocket();
        int set_keepalive (int sock);
        int send_data();
        std::string receive(int);

};
    
}
#endif