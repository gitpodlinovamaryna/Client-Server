#ifndef FUNCTIONS_FOR_SERVER_H
#define FUNCTIONS_FOR_SERVER_H

#include "server.h"

std::string getHostStr(const TcpServer::Client& client);
int startServer();


#endif