#include "../headers/client.h"
#include "../headers/functions_for_client.h"

using namespace std::chrono;


void TestWithClients()
{   
    std::vector<std::string> msgList{"Hello", "hallo","good morning","good day", "good evening", "good night", "have a nice day", "have a good day"};
    MyClient::TcpClient o_client;              
    o_client.setPort(3000);             
    o_client.createSocket();
    o_client.connectToServer();
    for (int i = 0; i < msgList.size(); i++)
    {
        o_client.send_msg(msgList[i]);
        o_client.receive();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    o_client.send_msg("exit");
}

void startClient(int argc, char **argv)
{
    MyClient::TcpClient o_client;                // new client
    int mode;                                    // interaction or single message mode
    std::string message;                         // message for single mode
    if(argc < 3)                                 // check mode options
    {
        mode = 2;                                // interaction mode
        std::cout<<"Enter port : ";              
        int tempPort = 0;
        std::cin>>tempPort;
        o_client.setPort(tempPort);             // Set port
    }
    else 
    { 
        mode = 1;                                // single mode
        o_client.setPort((atoi(argv[1])));  // set port
        message = argv[2];                       // set message  
    }

    switch (mode)                                // choice mode
    {
        case 1:                                  // single message mode
            o_client.createSocket();
            o_client.connectToServer();
            o_client.send_msg(message);
            o_client.receive();
            break;
        case 2:                                  //interaction mode
            o_client.createSocket();
            o_client.connectToServer();
            std::string message;
            while (o_client.send_msg() != "exit")
            {
                o_client.receive();
            }
            break;
    }
}
