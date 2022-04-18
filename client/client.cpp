#include <iostream> 
#include <stdio.h> 
#include <string.h> 
#include <string> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
#include <sys/types.h>
#include "client.h"

using namespace MyClient;


MyClient::TcpClient::TcpClient()
{
    m_socket = -1;
    m_keepalive = 0;
    m_port = htons(3000);
    m_ipAddress = "127.0.0.1";
}

 MyClient::TcpClient::TcpClient(int port)
{
    m_ipAddress = "127.0.0.1";
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
        m_socket = socket(AF_INET , SOCK_STREAM , 0);

        if (m_socket < 0)
        {
            perror("\nCould not create socket: ");
        }
        else std::cout<<"\nSocket created\n";

        if (setsockopt (m_socket, SOL_SOCKET, SO_KEEPALIVE, &m_keepalive, sizeof(m_keepalive)) < 0)    
        {           
            perror("\nSet keepalive error:\n");   
        }  
        else std::cout<<"\nSet keepalive successfully!!!";
    }
}

void MyClient::TcpClient::connectToServer()
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(m_ipAddress.c_str());
    serv_addr.sin_port = m_port;
    
    if( connect(m_socket , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) < 0 )
    {
        perror("\nconnect failed. Error: ");
    }

    else std::cout<<"\nConnected to Server successfully!!!\n";
}


void MyClient::TcpClient::send_msg(std::string msg)
{  
    if((send(m_socket, (char*)&msg, sizeof(msg), 0)) < 0)
    {
        perror("\nSend failed Error: ");
    }
    std::cout<<"\nSend to server: "<<msg<<std::endl;
}


void MyClient::TcpClient::receive()
{
    memset(&m_msg, 0, sizeof(m_msg));
    recv(m_socket, (char*)&m_msg, sizeof(m_msg), 0);
    std::cout << "Receive from server: " << std::string(m_msg) << std::endl;
}
