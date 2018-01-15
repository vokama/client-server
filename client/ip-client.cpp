#include <cstring>
#include <arpa/inet.h>

#include "ip-clients.hpp"

IpClient::IpClient(int transpProtocol)
	: socket(AF_INET, transpProtocol), msgMaxSize(64 * 1024)
{
	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(42420);
	inet_pton(AF_INET, "127.0.0.1", &(servAddr.sin_addr));

	if (socket.connect(servAddr) == -1) {
		perror("Failed to connect");
		exit(EXIT_FAILURE);
	}
}

IpClient::~IpClient() {}