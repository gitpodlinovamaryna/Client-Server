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
    //std::string IpAddress="";
    //if(argc < 4)
    //{
       // mode = 2;
       // if(argc < 3)
       // {
          //  std::cout<<"Enter IP : ";
          //  std::cin>>IpAddress;
          //  if(argc < 2)
          //  {
                std::cout<<"Enter port : ";
                std::cin>>port;
          //  }
       // }
   // }
   // else 
   // {
   //     port = atoi(argv[1]);
   //     IpAddress = argv[2];
        mode = 1;
    //    message = argv[3];
   // }
   message = "Hello single message!";
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