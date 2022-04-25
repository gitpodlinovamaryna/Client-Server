#include "../headers/functions_for_server.h"
#include <thread>

void messageExchange(int client, TcpServer & server);

void startServer(int argc, char **argv)
{

    MyServer::TcpServer o_server;
    int port;
    bool checkConnection = false;
    std::cout<<"Enter port : ";
    std::cin>>port;
    o_server.createSocket();
    o_server.bindPort();
    o_server.fillServAddr();
    o_server.listenToClients();
    int newClient = -1;
    while(true)
    {
        newClient = o_server.acceptClient();
        if(newClient < 0)
        {
            break;
        }
        else
        {
            checkConnection = true;
            o_server.setCurrentClients(o_server.getCurrentClients() + 1);
            std::thread clientThread(messageExchange, newClient, &o_server);
            clientThread.detach();
        }
        if(checkConnection == true && o_server.getCurrentClients() == 0)
        {
            break;
        }
    }
}

void messageExchange(int client, TcpServer & server)
{

}
