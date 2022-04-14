#include "server.h"

using namespace MyServer;

TcpServer::TcpServer()              // Initializer
{
    m_serverSocket = -1;
    m_port = htons(8080);
    m_ipAddress = "127.0.0.1";
    m_responseData = "";
    m_keepaliveOpt.idle = 60;
    m_keepaliveOpt.cnt = 5;
    m_keepaliveOpt.intvl = 3;
    
}  

TcpServer::TcpServer(std::string ipAddress, int port)
{
    m_ipAddress = ipAddress;
    m_port = port;
    m_serverSocket = -1;
    m_responseData = "";
    m_keepaliveOpt.idle = 60;
    m_keepaliveOpt.cnt = 5;
    m_keepaliveOpt.intvl = 3;
}

TcpServer::~TcpServer()             // Destructor
{
    close(m_serverSocket);
}     

int TcpServer::createSocket()
{
    if(m_serverSocket == -1)
    {
        
        m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (m_serverSocket != 0)
        {
            perror("Could not create socket");
            return -1;
        }
        
        if(set_keepalive(m_serverSocket) != 0)
        {
            perror("setsockopt()");
            return -1;
        }
        std::cout<<"Socket created\n";
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(m_ipAddress.c_str());
    serv_addr.sin_port = m_port;

    if(bind(m_serverSocket, (struct sockaddr *)& serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind failed");
        return -1;
    }

    if(listen(m_serverSocket, 1) < 0)
    {
        perror("listen error");
        return -1;
    }

    if((m_client = accept(m_serverSocket, (struct sockaddr *) NULL, NULL)) < 0)
    {
        perror("accept error");
        return -1;
    }
    std::string reply = "";
    do{
        char buffer[1024];
        read(m_client,buffer,1024);
        reply = receive(1024);
        send_data();
    }while (reply != "");
   
    return 0;
}
        
int TcpServer::set_keepalive (int sock)
{
    int alive = 1;    
    if (setsockopt (sock, SOL_SOCKET, SO_KEEPALIVE, &alive, sizeof(alive)) != 0)    
    {           
        perror("Set keepalive error:\n");   
        return -1;
    }  
         
    return 0;    
}

    
int TcpServer::send_data()
{
    std::cout<<"Sending data ...";
    
    if( send(m_serverSocket , m_responseData.c_str() , strlen( m_responseData.c_str() ) , 0) < 0)
    {
        perror("Send failed : ");
        return 1;
    }
    
    std::cout<<"Data send\n";

    return 0; 
}

std::string TcpServer::receive(int size=1024)
{
    char buffer[size];
    std::string reply;

 
    if( recv(m_serverSocket , buffer , sizeof(buffer) , 0) < 0)
    {
        puts("receive failed");
        return NULL;
    }

    reply = buffer;
    m_responseData = reply+"responce from server";
    return reply;
    
}