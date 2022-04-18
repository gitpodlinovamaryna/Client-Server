#include "server.h"

using namespace MyServer;

TcpServer::TcpServer()             
{
    m_port = htons(3000);
    m_ipAddress = "127.0.0.1";
    init();
}  

TcpServer::TcpServer(int port)   
{   
    m_ipAddress =  "127.0.0.1";
    m_port = htons(port);
    init();
}  

TcpServer::TcpServer(std::string ipAddress, int port)
{
    m_ipAddress = ipAddress;
    m_port = htons(port);
    init();
}

TcpServer::~TcpServer()             // Destructor
{
    close(m_serverSocket);
    close(m_newClient);
}     

void TcpServer::init()
{
    m_serverSocket = -1;
    m_newClient = -1;
    m_keepaliveOpt.idle = 60;
    m_keepaliveOpt.cnt = 5;
    m_keepaliveOpt.intvl = 3;
    m_buffesSize = 1024;
    m_maxClients = 3;
}

void TcpServer::createSocket()
{
    if(m_serverSocket == -1)
    {
        m_serverSocket = (socket(AF_INET, SOCK_STREAM, 0));
        if (m_serverSocket < 0)
        {
            perror("Could not create socket");
        }

        std::cout<<"Socket created\n";

        int alive = 1;    
        if (setsockopt (m_serverSocket, SOL_SOCKET, SO_KEEPALIVE, &alive, sizeof(alive)) < 0)    
        {           
            perror("Set keepalive error:\n");   
        }  

        std::cout<<"Set keepalive successfully\n";
        
    }
}


void TcpServer::bindPort()
{
    bzero((char*)&m_serverSocket, sizeof(m_serverSocket)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(m_ipAddress.c_str());
    serv_addr.sin_port = m_port;

    //if
    (bind(m_serverSocket, (struct sockaddr *)& serv_addr, sizeof(serv_addr)));// < 0)
   // {
      //  perror("bind failed");
    //}
    //std::cout << "Waiting for a client to connect..." << std::endl;
}             

void TcpServer::listenToClients()
{
    if(listen(m_serverSocket, m_maxClients) < 0)
    {
        perror("listen error");
    }
   
}      

void TcpServer::acceptClient()
{
   
    socklen_t newClientAddrSize = sizeof(client_addr);
    m_newClient = accept(m_serverSocket, (struct sockaddr *)&client_addr, &newClientAddrSize);
    if(m_newClient < 0)
    {
        perror( "Error accepting request from client!" );
    }
   // std::cout << "Connected with client!" << std::endl;
}

void TcpServer::sendMsg()
{
    puts(m_msg);
    send(m_newClient, m_msg, number, 0);
    std::cout<<"Send to client"<<m_msg<<std::endl;
}              

std::string TcpServer::receiveMsg()
{
     memset(&m_msg, 0, sizeof(m_msg));
     
     number = recv(m_newClient, m_msg, sizeof(m_msg), 0);
     std::cout << "Receive from client: " << m_msg << std::endl;
     std::string check = std::string(m_msg);
     
     return check;

}           