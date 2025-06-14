#include "TcpServer.h"


TcpServer::TcpServer(std::string port):m_listenSocket{INVALID_SOCKET}, m_addrInfoResult{nullptr}, m_port{port}
{
    LOG("Konstruktor z portem")

    m_clientSockets.push_back(SOCKET(INVALID_SOCKET));
    init();
    createSocket();
    getAddrInfo();
    bindSocket();

    std::cout << "Server configured to listen on port: " << m_port << std::endl;

}


TcpServer::~TcpServer()
{
    WSACleanup();
    for (const auto& socket : m_clientSockets)
    {
        closesocket(socket);
    }
}

void TcpServer::init()
{
    int result = WSAStartup(MAKEWORD(2,2), &m_wsaData);

    result != 0 ? log("Error while initializing winsock") : log("1. Winsock initialized");
}

void TcpServer::getAddrInfo()
{
    ZeroMemory(&m_hints, sizeof (m_hints));
    m_hints.ai_family = AF_INET;
    m_hints.ai_socktype = SOCK_STREAM;
    m_hints.ai_protocol = IPPROTO_TCP;
    m_hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    auto iResult = getaddrinfo(NULL, m_port.c_str(), &m_hints, &m_addrInfoResult);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return;
    }
}


void TcpServer::createSocket()
{
    m_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    m_listenSocket == INVALID_SOCKET ? log("Socket Invalid") : log("2. Created a Socket for the Server");
}

void TcpServer::bindSocket()
{
    if(m_addrInfoResult == nullptr) return;
    if(bind(m_listenSocket, (sockaddr*)m_addrInfoResult->ai_addr, (int)m_addrInfoResult->ai_addrlen) == SOCKET_ERROR)
    {
        log("Binding failed");
        return;
    }
    log("3. Binding is successfull.");
    freeaddrinfo(m_addrInfoResult);
}

void TcpServer::serverListen()
{
    std::cout << "Server listens on port: " << m_port << std::endl;

    std::thread t(&TcpServer::listening, this);
    t.detach();
}

void TcpServer::listening()
{
    while(1)
    {
        if ( listen(m_listenSocket, SOMAXCONN ) == SOCKET_ERROR ) 
        {
            closesocket(m_listenSocket);
            WSACleanup();
            return;
        }

        sockaddr_in clientAddress;
        int clientSize = sizeof(clientAddress);

        m_clientSockets.back() = accept(m_listenSocket, (sockaddr*)&clientAddress, &clientSize);
        
        if(m_clientSockets.back() != INVALID_SOCKET)
        {
            displayClientDetails(clientAddress);
            std::thread t(&TcpServer::run, this, m_clientSockets.back());
            t.detach();
            m_clientSockets.push_back(SOCKET(INVALID_SOCKET));
        }
    }
}

void TcpServer::run(SOCKET newClientSocket)
{
    std::cout << "Polaczono z klientem" << std::endl;
    
    char recvbuf[DEFAULT_BUFLEN];
    int iResult{0}, iSendResult{0};
    int recvbuflen{DEFAULT_BUFLEN};

    do {
            iResult = recv(newClientSocket, recvbuf, recvbuflen, 0);
            if (iResult > 0) {

                std::cout<< "String: " << std::string(recvbuf, iResult) << std::endl;
                std::cout << "Liczba: " << atoi(recvbuf) << std::endl;

                iSendResult = send(newClientSocket, recvbuf, iResult, 0);
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed: %d\n", WSAGetLastError());
                    closesocket(newClientSocket);
                    return;
                }
                printf("Bytes sent: %d\n", iSendResult);
            } else if (iResult == 0)
                printf("Connection closing...\n");
            else {
                printf("recv failed: %d\n", WSAGetLastError());
                closesocket(newClientSocket);
                return;
            }

        } while (iResult > 0);
}


void TcpServer::displayClientDetails(const sockaddr_in& clientAddr)
{
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
    int clientPort = ntohs(clientAddr.sin_port);
    std::cout << "Client connected from IP: " << clientIP << " Port: " << clientPort << "\n";
}