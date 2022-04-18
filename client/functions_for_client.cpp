#include "client.h"
/*
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
*/

void startClient(int argc, char **argv)
{
    MyClient::TcpClient o_client; 
    int port;
    int mode;
    std::string message;
    std::string IpAddress="";
    if(argc < 3)
    {
        mode = 2;
        std::cout<<"Enter port : ";
        int tempPort = 0;
        std::cin>>tempPort;
        port = htons(tempPort);
           
    }
    else 
    {
        o_client.m_port = htons(atoi(argv[1]));
        message = argv[2];
        mode = 1;
    }
    switch (mode)
    {
        case 1:
            o_client.createSocket();
            o_client.connectToServer();
            o_client.send_msg(message);
            o_client.receive();
            break;
        case 2:
            o_client.createSocket();
            o_client.connectToServer();
            std::string message;
            while (message != "exit")
            {
                message = "";
                std::cout << "Enter a message or exit to close:"<<std::endl;
                getline(std::cin, message);
                //std::cin >> message;
                o_client.send_msg(message);
            }
            
    }
}