#ifndef CLIENT_H
#define CLIENT_H


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

namespace MyClient
{

    class TcpClient
    {
        private:
            int m_socket;
            int m_connfd;
            std::string m_ipAddress;
            std::string m_responseData;
            int m_port;
            struct sockaddr_in serv_addr;


        public:
            TcpClient();   // Initializer
            explicit TcpClient(std::string,int, int);   // Initializer
            ~TcpClient();                               // Destructor
            int socket_set_keepalive (int);
            int connectToServer(std::string, int);
            int send_data(std::string data);
            std::string receive(int);
    };

}

#endif
