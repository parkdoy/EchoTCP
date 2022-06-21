//서버

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<stdlib.h>
#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")
#define PORT 7


int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	//printf("%d", ServerSocket);

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN));
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_port = (htons(PORT));//host to network short
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	/*엔디안 os가 읽는 방식이 -> 인지 <- 인지 모바일과 PC가 통신 하는 방식이 서로 다름. 네트워크 기준(빅 엔디안)을 기준으로 통신이 가능함*/

	bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));
	listen(ServerSocket, 0);


	while (true)
	{
		SOCKADDR_IN ClientSockAddr;
		memset(&ClientSockAddr, 0, sizeof(SOCKADDR_IN));
		int ClientAddrLength = sizeof(ClientSockAddr);
		SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientAddrLength);

		char Message[1024] = { 0, };
		int RecvLength = recv(ClientSocket, Message, sizeof(Message) - 1, 0);
		send(ClientSocket, Message, RecvLength, 0); //순서차이? 클라이언트 수락->메세지 받기->메세지 보내기

		closesocket(ClientSocket);
	}

	closesocket(ServerSocket);

	WSACleanup();

}