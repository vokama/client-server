#pragma once

#include <string>
#include <arpa/inet.h>

#include "../socket/socket.hpp"

/* this is an abstract base class for all IP servers */
class IpServer {
protected:
	IpServer(int transpProtocol);
	virtual ~IpServer() = 0;
public:
	virtual void send(std::string str) = 0;
	virtual std::string recieve() = 0;
protected:
	Socket socket;
	sockaddr_in clientAddr;
	size_t msgMaxSize;
};

class UdpServer : public IpServer {
public:
	UdpServer();
	~UdpServer();
	virtual void send(std::string str);
	virtual std::string recieve();
};

class TcpServer : public IpServer {
public:
	TcpServer();
	~TcpServer();
	virtual void send(std::string str);
	virtual std::string recieve();
private:
	std::string newMsgs;

};