#include <TcpServer.h>
#include <iostream>
#include <string>

int main()
{
    TcpServer server("8000"), server2;

    server.serverListen();
    server2.serverListen();

    std::string command;
    while(command != "exit")
    {
        std::cin >> command;
    }
    
    return 0;
}
