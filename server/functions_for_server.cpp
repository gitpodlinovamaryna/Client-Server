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
    o_server.serv_addr.sin_family = AF_INET;
    o_server.serv_addr.sin_addr.s_addr = inet_addr(o_server.m_ipAddress.c_str());
    o_server.serv_addr.sin_port = o_server.m_port;
    o_server.listenToClients();
    o_server.acceptClient();
    memset(&o_server.m_msg, 0, sizeof(o_server.m_msg));
    while((o_server.number = recv(o_server.m_newClient, o_server.m_msg, sizeof(o_server.m_msg), 0))>0)
    {
        std::cout << "Receive from client: " << o_server.m_msg << std::endl;
       // puts(o_server.m_msg);
        send(o_server.m_newClient, o_server.m_msg, o_server.number, 0);
        std::cout<<"Send to client: "<<o_server.m_msg <<std::endl;
    }
}
