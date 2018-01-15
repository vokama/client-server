#include "ip-clients.hpp"

using namespace std;

UdpClient::UdpClient()
	: IpClient(SOCK_DGRAM) {}

void UdpClient::send(string str)
{
	if (str.size() > msgMaxSize) {
		fprintf(stderr,
			"Datagram size exceeds %zu bytes\n", msgMaxSize);
		exit(EXIT_FAILURE);
	}

	if (socket.send(str.c_str(), str.size()) == -1) {
		perror("Can't send datagram");
		exit(EXIT_FAILURE);
	}
}

string UdpClient::recieve()
{
	char buf[msgMaxSize];
	ssize_t recieved;

	recieved = socket.recieve(buf, msgMaxSize);
	if (recieved == -1) {
		perror("Can't recieve datagram");
		exit(EXIT_FAILURE);
	}

	return string(buf, recieved);
}

UdpClient::~UdpClient() {}