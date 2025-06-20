#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512
#define WEB_SOCKET_CLIENT_IP "localhost"
#define WEB_SOCKET_CLIENT_PORT "8000"

#include <winsock2.h>
#include <WS2tcpip.h>
#include <vector>
#include <string>
#include "WebSocketClient.h"

class TcpServer
{
    public:
        TcpServer() : TcpServer(DEFAULT_PORT, WEB_SOCKET_CLIENT_IP, WEB_SOCKET_CLIENT_PORT) {};
        TcpServer(std::string port, std::string webSocketServerIp, std::string webSocketServerPort);
        ~TcpServer();

        void serverListen();

    private:
        std::string m_port;
        WSAData m_wsaData;
        SOCKET m_listenSocket;
        std::vector<SOCKET> m_clientSockets;
        struct addrinfo *m_addrInfoResult, m_hints;
        WebSocketClient m_webSocketClient;

        void init();
        void getAddrInfo();
        void createSocket();
        void bindSocket();
        void run(SOCKET newClientSocket);
        void listening();

        //helper methods
        void displayClientDetails(const sockaddr_in& clientAddress);
    
};