#include <iostream>
#include <cstring>
#include "ip-clients.hpp"

using namespace std;

static void clientLoop(IpClient *client)
{
	string input, output;

	while (true) {
		getline(cin, input);
		client->send(input);
		cout << "Message sent\n";

		output = client->recieve();
		cout << "Message recieved:\n" << output << "\n";

		cout << '\n';
	}
}

int main(int argc, char *argv[])
{
	IpClient *client;

	if (argc == 1) {
		cout << "Specify the connection type with either --tcp or --udp"
			" option\n";
		return 0;
	}
	if (strcmp(argv[1], "--tcp") == 0) {
		client = new TcpClient;
		cout << "Connection established\n";
	} else if (strcmp(argv[1], "--udp") == 0) {
		client = new UdpClient;
	} else {
		cout << "Wrong parameter\n";
		return 0;
	}

	clientLoop(client);

	delete(client);
}