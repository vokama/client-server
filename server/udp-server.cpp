#include "ip-servers.hpp"

using namespace std;

UdpServer::UdpServer()
	: IpServer(SOCK_DGRAM) {}

string UdpServer::recieve()
{
	char buf[msgMaxSize];
	ssize_t recieved;

	recieved = socket.recieveFrom(buf, msgMaxSize, &clientAddr);
	if (recieved == -1) {
		perror("Can't recieve datagram");
		exit(1);
	}

	return string(buf, recieved);
}

void UdpServer::send(std::string str)
{
	if (str.size() > msgMaxSize) {
		fprintf(stderr,
			"Datagram size exceeds %zu bytes\n", msgMaxSize);
		exit(EXIT_FAILURE);
	}

	if (socket.sendTo(str.c_str(), str.size(), clientAddr) == -1) {
		perror("Can't send datagram");
		exit(EXIT_FAILURE);
	}
}

UdpServer::~UdpServer() {}