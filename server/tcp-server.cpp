#include "ip-servers.hpp"

using namespace std;

TcpServer::TcpServer()
	: IpServer(SOCK_STREAM)
{
	if (socket.listen(5) == -1) {
		perror("Socket can't listen");
		exit(EXIT_FAILURE);
	}

	int commDescriptor = socket.accept(&clientAddr);
	if (commDescriptor == -1) {
		perror("Can't accept client");
		exit(EXIT_FAILURE);
	}
	socket = Socket(commDescriptor);
}

string TcpServer::recieve()
{
	char buf[msgMaxSize];
	string msg;
	ssize_t recieved;
	size_t newlinePos;

	while ((newlinePos = newMsgs.find('\n')) == string::npos) {
		recieved = socket.recieve(buf, msgMaxSize);
		if (recieved == -1) {
			perror("Can't recieve message");
			exit(EXIT_FAILURE);
		}
		newMsgs += string(buf, recieved);
	}
	msg = newMsgs.substr(0, newlinePos);
	newMsgs = newMsgs.substr(newlinePos + 1);
	return msg;
}

void TcpServer::send(string str)
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

TcpServer::~TcpServer() {}