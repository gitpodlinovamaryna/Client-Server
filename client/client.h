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
            int m_port;
            int m_keepalive;
            int m_buffesSize;
            char m_msg[1024];
            std::string m_ipAddress;
            struct sockaddr_in serv_addr;
            


        public:
            TcpClient();                       // Initializer
            TcpClient(std::string,int, int);   // Initializer
            ~TcpClient();                      // Destructor
            void createSocket();                    
            void connectToServer();
            void send_msg(std::string msg);
            void receive();
    };

}

#endif
