#include <cstdio>
#include <arpa/inet.h>
#include <cstring>

#include "ip-servers.hpp"

IpServer::IpServer(int transpProtocol)
	: socket(AF_INET, transpProtocol), msgMaxSize(64 * 1024)
{
	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htons(INADDR_ANY);
	servAddr.sin_port = htons(42420);

	if (socket.bind(servAddr) == -1) {
		perror("Failed to bind socket");
		exit(EXIT_FAILURE);
	}

	memset(&clientAddr, 0, sizeof(clientAddr));
}

IpServer::~IpServer() {}