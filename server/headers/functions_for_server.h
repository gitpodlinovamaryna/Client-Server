#ifndef FUNCTIONS_FOR_SERVER_H
#define FUNCTIONS_FOR_SERVER_H

#include <iostream>
#include "server.h"
#include <thread>


using namespace MyServer;

void startServer(int argc, char **argv);
void messageExchange(int, TcpServer&);
#endif


