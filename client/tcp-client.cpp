#include "ip-clients.hpp"

using namespace std;

TcpClient::TcpClient()
	: IpClient(SOCK_STREAM) {}

void TcpClient::send(std::string str)
{
	str += '\n';
	if (str.size() > msgMaxSize) {
		fprintf(stderr,
			"Message size exceeds %zu bytes\n", msgMaxSize);
		exit(EXIT_FAILURE);
	}

	if (socket.send(str.c_str(), str.size()) == -1) {
		perror("Can't send message");
		exit(EXIT_FAILURE);
	}
}

std::string TcpClient::recieve()
{
	char buf[msgMaxSize];
	string msg;
	ssize_t recieved;
	size_t newlinePos;

	while ((newlinePos = unprocsdMsgs.find('\n')) == string::npos) {
		recieved = socket.recieve(buf, msgMaxSize);
		if (recieved == -1) {
			perror("Can't recieve message");
			exit(EXIT_FAILURE);
		}
		unprocsdMsgs += string(buf, recieved);
	}
	msg = unprocsdMsgs.substr(0, newlinePos);
	unprocsdMsgs = unprocsdMsgs.substr(newlinePos + 1);
	return msg;
}

TcpClient::~TcpClient() {}