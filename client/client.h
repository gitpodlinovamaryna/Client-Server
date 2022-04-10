#ifndef CLIENT_H
#define CLIENT_H


#include <iostream> 
#include <stdio.h> 
#include <string.h> 
#include <string> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netdb.h> 

namespace MyClient
{

    class TcpClient
    {
        private:
            int m_socket;
            std::string m_ipAddress;
            std::string m_responseData;
            int m_port;
            struct sockaddr_in serv_addr;

        public:
            TcpClient();
            explicit TcpClient(std::string,int);
            ~TcpClient();
            int connectToServer(std::string, int);
            int send_data(std::string data);
            std::string receive(int);
    };

}

#endif
