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
    m_port = 0;
    m_ipAddress = "127.0.0.1";
    m_responseData = "";
}

 MyClient::TcpClient::TcpClient(std::string ipAddress, int port):m_ipAddress(ipAddress),m_port(port)
{
    m_socket = -1;
    m_responseData = "";
}

int MyClient::TcpClient::connectToServer(std::string address , int port)
{
   
    if(m_socket == -1)
    {
        
        m_socket = socket(AF_INET , SOCK_STREAM , 0);
        if (m_socket == -1)
        {
            perror("Could not create socket");
        }

        std::cout<<"Socket created\n";
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(m_ipAddress.c_str());
    serv_addr.sin_port = m_port;
    
    if( connect(m_socket , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) < 0 )
    {
        perror("connect failed. Error");
        return 0;
    }

    std::cout<<"Connected to Server\n";
    return 1;
}


int MyClient::TcpClient::send_data(std::string data)
{
    std::cout<<"Sending data...";
    std::cout<<data;
    std::cout<<"\n";
    
   
    if( send(m_socket , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        perror("Send failed : ");
        return 0;
    }
    
    std::cout<<"Data send\n";

    return 1;
}


std::string MyClient::TcpClient::receive(int size=512)
{
    char buffer[size];
    std::string reply;

 
    if( recv(m_socket , buffer , sizeof(buffer) , 0) < 0)
    {
        puts("receive failed");
        return NULL;
    }

    reply = buffer;
    m_responseData = reply;
    
    return reply;
}

