#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

#include <winsock2.h>
#include <WS2tcpip.h>
#include <vector>
#include <string>


class TcpServer
{
    public:
        TcpServer() : TcpServer(DEFAULT_PORT) {};
        TcpServer(std::string port);
        ~TcpServer();

        void serverListen();

    private:
        std::string m_port;
        WSAData m_wsaData;
        SOCKET m_listenSocket;
        std::vector<SOCKET> m_clientSockets;
        struct addrinfo *m_addrInfoResult, m_hints;

        void init();
        void getAddrInfo();
        void createSocket();
        void bindSocket();
        void run(SOCKET newClientSocket);
        void listening();

        //helper methods
        void displayClientDetails(const sockaddr_in& clientAddress);
    
};