#include "client.h"

void sendInteractionMsg(MyClient::TcpClient &o_client, int &port, std::string &IpAddress )
{
    o_client.connectToServer(IpAddress , port);
    std::string message;
    do
    {
        message = "";
        std::cout << "Enter a message or empy for close:"<<std::endl;
        std::cin >> message;
        o_client.send_data(message);
    } while (message != "");
}

void startClient(int argc, char **argv)
{
    MyClient::TcpClient o_client;
    int port;
    int mode;
    std::string message;
    std::string IpAddress="";
    if(argc < 4)
    {
        mode = 2;
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
    }
    else 
    {
        port = atoi(argv[1]);
        IpAddress = argv[2];
        mode = 1;
        message = argv[3];
    }
    switch (mode)
    {
        case 1:
            o_client.connectToServer(IpAddress , port);
            o_client.send_data(message);
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