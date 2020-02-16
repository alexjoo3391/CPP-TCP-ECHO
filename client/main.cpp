#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <WinSock2.h>

using namespace std;

void ShowErrorMessage(string msg) {
	cout << "[�����߻�]:" << msg << endl;
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
	cout << "[�������]: connect()" << endl;

	while (1) {
		cout << "[�޼��� ����]: ";
		getline(cin, sent);
		if (sent == "")
			continue;

		send(clientSocket, sent.c_str(), sent.length(), 0);

		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = NULL;

		if (strcmp(received, "[exit]") == 0){
			cout << "[Ŭ���̾�Ʈ ��� ����]" << endl;
			break;
		}

		cout << "[���� �޽���]: " << received << endl;
	}

	closesocket(clientSocket);

	WSACleanup();

	system("pause");
	return 0;
}