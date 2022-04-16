#include <iostream> 
#include <stdio.h> 
#include <string.h> 
#include <string> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
#include "client.h"

using namespace MyClient;


MyClient::TcpClient::TcpClient()
{
    m_socket = -1;
    m_keepalive = 0;
    m_port = htons(4100);
    m_ipAddress = "127.0.0.1";
}

 MyClient::TcpClient::TcpClient(std::string ipAddress, int port, int flag)
{
    m_ipAddress = ipAddress;
    m_port = htons(port);
    m_socket = -1;
    m_keepalive = 0;
}

MyClient::TcpClient::~TcpClient()
{
    close(m_socket);
}

void TcpClient::createSocket()
{
    if(m_socket == -1)
    {
        m_socket = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);

        if (m_socket < 0)
        {
            perror("Could not create socket");
        }
        else std::cout<<"Socket created\n";

        if (setsockopt (m_socket, SOL_SOCKET, SO_KEEPALIVE, &m_keepalive, sizeof(m_keepalive)) < 0)    
        {           
            perror("Set keepalive error:\n");   
        }  
        else std::cout<<"Set keepalive successfully\n";
        
    }
}

void MyClient::TcpClient::connectToServer()
{
    bzero((char*)&serv_addr, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(m_ipAddress.c_str());
    serv_addr.sin_port = m_port;
    
    if( connect(m_socket , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) < 0 )
    {
        perror("connect failed. Error");
    }

    else std::cout<<"Connected to Server\n";
}


void MyClient::TcpClient::send_msg(std::string msg)
{  

    send(m_socket, (char*)&msg, sizeof(msg), 0);
    std::cout<<"Send to client"<<msg<<std::endl;
    
    std::cout<<"Message send\n";

}


void MyClient::TcpClient::receive()
{
    memset(&m_msg, 0, sizeof(m_msg));
    recv(m_socket, (char*)&m_msg, sizeof(m_msg), 0);
    std::cout << "Receive from server: " << std::string(m_msg) << std::endl;
}
