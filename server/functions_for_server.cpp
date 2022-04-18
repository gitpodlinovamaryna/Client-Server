#include "functions_for_server.h"


void startServer(int argc, char **argv)
{

    MyServer::TcpServer o_server;
    int port;
    //std::string IpAddress="";
    //if(argc < 3)
    //{
        //std::cout<<"Enter IP : ";
       // std::cin>>IpAddress;
        //if(argc < 2)
        //{
            std::cout<<"Enter port : ";
            std::cin>>port;
        //}
    //}
    ///else 
    //{
        //port = atoi(argv[1]);
      //  IpAddress = argv[2];
    //}
    o_server.createSocket();
    o_server.bindPort();
    o_server.listenToClients();
    o_server.acceptClient();
    socklen_t newClientAddrSize = sizeof(o_server.client_addr);
    o_server.m_newClient = accept(o_server.m_serverSocket, (struct sockaddr *)&o_server.client_addr, &newClientAddrSize);
    if(o_server.m_newClient < 0)
    {
        perror( "Error accepting request from client!" );
    }
    std::cout << "Connected with client!" << std::endl;
    memset(&o_server.m_msg, 0, sizeof(o_server.m_msg));
     while((o_server.number = recv(o_server.m_newClient, o_server.m_msg, sizeof(o_server.m_msg), 0))>0)
     {
     std::cout << "Receive from client: " << o_server.m_msg << std::endl;
     puts(o_server.m_msg);
    send(o_server.m_newClient, o_server.m_msg, o_server.number, 0);
    std::cout<<"Send to client"<<o_server.m_msg<<std::endl;
     }
    /*while (1)
    {
        std::string check = o_server.receiveMsg();
        if(check == "exit")
        {
            std::cout<<"Bye!!!";
            break;
        }
        o_server.sendMsg();
    }*/

}
