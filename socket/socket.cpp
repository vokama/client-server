#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#include "socket.hpp"

Socket::Socket(int domain, int type, int protocol)
{
	descriptor_ = socket(domain, type, protocol);
	if (descriptor_ == -1) {
		perror("Failed to open socket");
		exit(EXIT_FAILURE);
	}

	refsCount = new int(1);
}

Socket::Socket(int descriptor)
	: descriptor_(descriptor)
{
	refsCount = new int(1);
}

Socket::Socket(const Socket &other)
{
	this->descriptor_ = other.descriptor_;
	refsCount = other.refsCount;

	(*refsCount)++;
}

ssize_t Socket::send(const void *buf, size_t len, int flags)
{
	return ::send(descriptor_, buf, len, flags);
}

ssize_t Socket::recieve(void *buf, size_t len, int flags)
{
	return ::recv(descriptor_, buf, len, flags);
}

int Socket::listen(int backlog)
{
	return ::listen(descriptor_, 5);
}

Socket& Socket::operator=(const Socket &other)
{
	if (this == &other)
		return *this;

	(*refsCount)--;
	if (!*refsCount) {
		close(descriptor_);
		delete refsCount;
	}

	descriptor_ = other.descriptor_;
	refsCount = other.refsCount;
	(*refsCount)++;
	return *this;
}

Socket::~Socket()
{
	(*refsCount)--;
	if (!*refsCount) {
		close(descriptor_);
		delete refsCount;
	}
}