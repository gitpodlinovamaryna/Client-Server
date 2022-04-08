#include <iostream>
#include "client.h"


int main(int argc , char *argv[])
{
    MyClient::TcpClient o_client;
    int port;
    std::string IpAddress="";
    std::cout<<"Enter hostname : ";
    std::cin>>IpAddress;
    std::cout<<"Enter port : ";
    std::cin>>port;
   
    o_client.connectToServer(IpAddress , port);

    o_client.send_data("Maryna");

    std::cout<<o_client.receive(1024);
    
    return 0;
}
