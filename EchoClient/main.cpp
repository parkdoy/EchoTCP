//Ŭ���̾�Ʈ
#include <iostream>
#include <Winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 7
using namespace std;

#define BUFFER_SIZE 1024

int main()
{
    // ���� �ʱ�ȭ
    WSADATA wsaData = {};
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "WSAStartup() Error" << endl;
        return -1;
    }

    // �������� ������ ���� ���� ����
    SOCKET clntSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clntSocket == INVALID_SOCKET)
    {
        cout << "socket() Error" << endl;
        return -1;
    }

    // �������� ���� ��û
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
        // �޽��� �Է�
        fputs("������ �޽����� �Է��ϼ��� (q to quit) : ", stdout);
        fgets(message, BUFFER_SIZE, stdin);

        // q�� �Է����� ��� ������ ����
        if (strcmp(message, "q\n") == 0)
            break;

        // �޽��� �۽�
        send(clntSocket, message, strlen(message), 0);

        // �޽��� ����
        length = recv(clntSocket, message, BUFFER_SIZE - 1, 0);
        message[length] = 0;
        cout << "�����κ��� ���۵� �޽��� : " << message << endl;
    }

    // Ŭ���̾�Ʈ ���� ����
    closesocket(clntSocket);

    // ������ ���� ����
    WSACleanup();
}