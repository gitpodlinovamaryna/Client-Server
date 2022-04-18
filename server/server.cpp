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

void TcpServer::fillServAddr()
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(m_ipAddress.c_str());
    serv_addr.sin_port = m_port;
}


// Create new socket TCP
void TcpServer::createSocket()
{
    if(m_serverSocket == -1)
    {
        m_serverSocket = (socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
        if (m_serverSocket < 0)
        {
            perror("Could not create socket");
        }

        std::cout<<"Socket created\n";


        // Set keepalive options
        if (setsockopt (m_serverSocket, SOL_SOCKET, SO_KEEPALIVE, &m_keepaliveOpt.idle, sizeof(m_keepaliveOpt.idle)) < 0)    
        {           
            perror("Set keepalive error:\n");   
        }  
        else std::cout<<"Set keepalive successfully\n";


        //Set keepalive interval
        if (setsockopt(m_serverSocket, IPPROTO_TCP, TCP_KEEPINTVL, &m_keepaliveOpt.intvl, sizeof(m_keepaliveOpt.intvl)) < 0)
        {
            perror("Set keepalive interval error:\n");  
        }

        else std::cout<<"Set keepalive interval successfully\n";


        //Set keepalive count
        if (setsockopt(m_serverSocket, IPPROTO_TCP, TCP_KEEPCNT, &m_keepaliveOpt.cnt, sizeof(m_keepaliveOpt.cnt)) < 0)
        {
            perror("Set keepalive count error:\n");  
        }
        else std::cout<<"Set keepalive count successfully\n";
    }
}


// Bind to port
void TcpServer::bindPort()
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(m_ipAddress.c_str());
    serv_addr.sin_port = m_port;

    
    if((bind(m_serverSocket, (struct sockaddr *)& serv_addr, sizeof(serv_addr))) < 0)
    {
          perror("bind failed");
    }
    std::cout << "Bind successfully!!!" << std::endl;
}             


// Listen clients
void TcpServer::listenToClients()
{
    if(listen(m_serverSocket, m_maxClients) < 0)
    {
        perror("listen error");
    }
   std::cout << "Waiting for a client to connect..." << std::endl;
}      


//Set connection with client
void TcpServer::acceptClient()
{
    socklen_t newClientAddrSize = sizeof(client_addr);
    m_newClient = accept(m_serverSocket, (struct sockaddr *)&client_addr, &newClientAddrSize);
    if(m_newClient < 0)
    {
        perror( "Error accepting request from client!" );
    }
    std::cout << "Connected with client!" << std::endl;
}


 // Send message to client
void TcpServer::sendMsg()
{
    puts(m_msg);
    if((send(m_newClient, m_msg, number, 0)) < 0)
    {
         perror( "Error send msg to the client!" );
    }
    
    std::cout<<"Send to client"<<m_msg<<std::endl;
}              


// Receive message from client
std::string TcpServer::receiveMsg()
{
     memset(&m_msg, 0, sizeof(m_msg));
     
     number = recv(m_newClient, m_msg, sizeof(m_msg), 0);
     std::cout << "Receive from client: " << m_msg << std::endl;
     std::string check = std::string(m_msg);
     return check;
}          


// Regulates the order in which messages are exchanged between the client and the server
void TcpServer::messageExchange()
{
    memset(&m_msg, 0, sizeof(m_msg));
    while((number = recv(m_newClient, m_msg, sizeof(m_msg), 0))>0)
    {
        std::cout << "Receive from client: " << m_msg << std::endl;
        send(m_newClient, m_msg, number, 0);
        std::cout<<"Send to client: "<<m_msg <<std::endl;
    }
}