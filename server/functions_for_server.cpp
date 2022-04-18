#include "functions_for_server.h"


void startServer(int argc, char **argv)
{

    MyServer::TcpServer o_server;
    int port;
    std::cout<<"Enter port : ";
    std::cin>>port;
    o_server.createSocket();
    o_server.bindPort();
    o_server.fillServAddr();
    o_server.listenToClients();
    o_server.acceptClient();
    o_server.messageExchange();
}
