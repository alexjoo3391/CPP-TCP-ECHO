#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <WinSock2.h>

using namespace std;

void ShowErrorMessage(string msg) {
	cout << "[오류발생]:" << msg << endl;
	exit(1);
}

int main(void) {
	WSADATA wasData;
	SOCKET clientSocket;
	SOCKADDR_IN serverAddress;

	int serverPort = 1212;
	char received[256];
	string sent;

	if (WSAStartup(MAKEWORD(2, 2), &wasData) != 0) {
		ShowErrorMessage("WSAStartup()");
	}

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (clientSocket == INVALID_SOCKET) {
		ShowErrorMessage("socket()");
	}

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	//serverAddress.sin_addr.s_addr = inet_addr("192.168.0.10");
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress.sin_port = htons(serverPort);

	if (connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		ShowErrorMessage("connect()");
	}
	cout << "[현재상태]: connect()" << endl;

	while (1) {
		cout << "[메세지 전송]: ";
		getline(cin, sent);
		if (sent == "")
			continue;

		send(clientSocket, sent.c_str(), sent.length(), 0);

		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = NULL;

		if (strcmp(received, "[exit]") == 0){
			cout << "[클라이언트 통신 종료]" << endl;
			break;
		}

		cout << "[서버 메시지]: " << received << endl;
	}

	closesocket(clientSocket);

	WSACleanup();

	system("pause");
	return 0;
}