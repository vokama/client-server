#pragma once

#include <string>

#include "../socket/socket.hpp"

/* this is an abstract base class for all IP clients */
class IpClient {
public:
	IpClient(int transpProtocol);
	virtual ~IpClient() = 0;
public:
	virtual void send(std::string str) = 0;
	virtual std::string recieve() = 0;
protected:
	Socket socket;
	const size_t msgMaxSize;
};

class UdpClient : public IpClient {
public:
	UdpClient();
	~UdpClient();
	virtual void send(std::string str);
	virtual std::string recieve();
};

class TcpClient : public IpClient {
public:
	TcpClient();
	~TcpClient();
	virtual void send(std::string str);
	virtual std::string recieve();
private:
	std::string unprocsdMsgs;
};