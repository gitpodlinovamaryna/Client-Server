#include "functions_for_server.h"


void startServer(int argc, char **argv)
{

    MyServer::TcpServer o_server;
    int port;
    std::string IpAddress="";
    if(argc < 3)
    {
        std::cout<<"Enter IP : ";
        std::cin>>IpAddress;
        if(argc < 2)
        {
            std::cout<<"Enter port : ";
            std::cin>>port;
        }
    }
    else 
    {
        port = atoi(argv[1]);
        IpAddress = argv[2];
    }
    o_server.createSocket();
}
