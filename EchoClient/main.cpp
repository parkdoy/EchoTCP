//클라이언트
#include <iostream>
#include <Winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 7
using namespace std;

#define BUFFER_SIZE 1024

int main()
{
    // 윈속 초기화
    WSADATA wsaData = {};
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "WSAStartup() Error" << endl;
        return -1;
    }

    // 서버로의 접속을 위한 소켓 생성
    SOCKET clntSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clntSocket == INVALID_SOCKET)
    {
        cout << "socket() Error" << endl;
        return -1;
    }

    // 서버로의 연결 요청
    SOCKADDR_IN sockAddr = {};
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &sockAddr.sin_addr);
    if (connect(clntSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
    {
        cout << "connect() Error" << endl;
        return -1;
    }

    char message[BUFFER_SIZE] = {};
    int length = 0;

    while (true)
    {
        // 메시지 입력
        fputs("전송할 메시지를 입력하세요 (q to quit) : ", stdout);
        fgets(message, BUFFER_SIZE, stdin);

        // q를 입력했을 경우 루프문 종료
        if (strcmp(message, "q\n") == 0)
            break;

        // 메시지 송신
        send(clntSocket, message, strlen(message), 0);

        // 메시지 수신
        length = recv(clntSocket, message, BUFFER_SIZE - 1, 0);
        message[length] = 0;
        cout << "서버로부터 전송된 메시지 : " << message << endl;
    }

    // 클라이언트 연결 종료
    closesocket(clntSocket);

    // 윈도우 소켓 해제
    WSACleanup();
}