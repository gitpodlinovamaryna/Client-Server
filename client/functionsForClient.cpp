#include <iostream>
#include "client.h"

void sendInteractionMsg(MyClient::TcpClient &o_client, int &port, std::string &IpAddress )
{
    std::string message = "";
    do
    {
        o_client.connectToServer(IpAddress , port);
        std::cout << "Enter a message or close:"<<std::endl;
        std::cin >> message;
        o_client.send_data(message);
    } while (message != "");
}

void startClient()
{
    MyClient::TcpClient o_client;
    int port,mode = 0;
    std::string IpAddress="";
    std::cout<<"Enter hostname : ";
    std::cin>>IpAddress;
    std::cout<<"Enter port : ";
    std::cin>>port;
    while(mode != 1 || mode != 2 || mode != 3)
    {
        std::cout<<"\nChoice mode: \n1-single message 2-interaction\n 3-close\n";
        std::cin>>mode;
        switch (mode)
        {
            case 1:
                o_client.connectToServer(IpAddress , port);
                o_client.send_data("Maryna");
                std::cout<<o_client.receive(1024);
                break;
            case 2:
                sendInteractionMsg(o_client, port, IpAddress);
                break;
            case 3:
                std::cout<<"See you soon!";
                break;
            default:
                std::cout<<"mode is not an option";
                break;
        }
    }
}