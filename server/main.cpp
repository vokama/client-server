#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>

#include "ip-servers.hpp"

using namespace std;

static bool isMore(int i, int j)
{
	return i > j;
}

static void process_message(string message)
{
	char c;
	int i;
	vector<int> digits;
	stringstream stream(message);

	while(stream >> c) {
		i = c - '0';
		if (i >= 0 && i <= 9)
			digits.push_back(i);
	}
	if (digits.empty())
		return;

	cout << "Sum of all the digits in the message equals "
	     << accumulate(digits.begin(), digits.end(), 0) << endl;

	sort(digits.begin(), digits.end(), isMore);
	cout << "The same digits in a descending order: ";
	for (auto d: digits)
		cout << d << ' ';
	cout << endl;

	cout << "Maximum and minimum values respectively: "
	     << digits.front() << ' ' << digits.back() << endl;

}

static void serverLoop(IpServer *server)
{
	string message;

	while (true) {
		message = server->recieve();
		cout << "Message recieved:\n" << message << "\n";
		process_message(message);

		server->send(message);
		cout << "Message sent\n";

		cout << '\n';
	}
}

int main()
{
	thread udpThread(serverLoop, new UdpServer);
	thread tcpThread(serverLoop, new TcpServer);

	udpThread.join();
	tcpThread.join();

	return 0;
}