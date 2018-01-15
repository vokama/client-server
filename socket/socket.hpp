#pragma once

#include <sys/socket.h>

class Socket {
public:
	Socket(int domain, int type, int protocol = 0);
	Socket(int descriptor);
	Socket(const Socket &other);
	~Socket();

	Socket& operator=(const Socket &other);

	template <class addrType>
	int connect(addrType addr);
	template <class addrType>
	int bind(addrType addr);
	template <class addrType>
	int accept(addrType *addr);
	template <class addrType>
	ssize_t sendTo(const void *buf, size_t len,
		       addrType addr, int flags = 0);
	template <class addrType>
	ssize_t recieveFrom(void *buf, size_t len, addrType *addr,
			    int flags = 0);
	int listen(int backlog);
	ssize_t send(const void *buf, size_t len, int flags = 0);
	ssize_t recieve(void *buf, size_t len, int flags = 0);
private:
	int descriptor_;
	int *refsCount;
};

template <class addrType>
int Socket::connect(addrType addr)
{
	return ::connect(descriptor_,
			 reinterpret_cast<struct sockaddr*>(&addr),
			 sizeof(addr));
}

template <class addrType>
int Socket::bind(addrType addr)
{
	return ::bind(descriptor_,
		      reinterpret_cast<struct sockaddr*>(&addr),
		      sizeof(addr));
}

template <class addrType>
int Socket::accept(addrType *addr)
{
	socklen_t addrLen = sizeof(*addr);
	return ::accept(descriptor_,
			reinterpret_cast<struct sockaddr*>(addr), &addrLen);
}

template <class addrType>
ssize_t Socket::sendTo(const void *buf, size_t len, addrType addr,
		       int flags)
{
	return ::sendto(descriptor_, buf, len, flags,
			reinterpret_cast<struct sockaddr*>(&addr),
			sizeof(addr));
}

template <class addrType>
ssize_t Socket::recieveFrom(void *buf, size_t len, addrType *addr,
			    int flags)
{
	socklen_t addrLen = sizeof(*addr);

	return ::recvfrom(descriptor_, buf, len, flags,
			  reinterpret_cast<struct sockaddr*>(addr), &addrLen);
}