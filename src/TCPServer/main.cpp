#ifdef _WIN32
#include<windows.h>
#define socklen_t int
#else
#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>
#define closesocket ::close
#endif

#include<iostream>
#include<thread>
#include<string.h>
#include "tcp.h"

using std::cout;
using std::cin;
using std::endl;

class TCPThread
{

private:
	TCP client;
public:
	TCPThread()
	{}
	TCPThread(TCP c) : client(c)
	{}
	void work()
	{
		char buf[1024] = { 0 };
		while (1)
		{
			int recv_len = client.recv(buf, sizeof(buf) - 1);
			if (recv_len <= 0)	break;
			if (strstr(buf, "quit") != NULL)
			{
				int send_len = client.send("Quit success\n", strlen("Quit success\n") + 1);
				cout << "Quit success" << endl;
				break;
			}
			int send_len = client.send("Server receive\n", strlen("Server receive\n") + 1);
			cout << "Recv " << buf << endl;
		}
		client.close();
		delete this;
	}

};

#include<sys/epoll.h>
int main(int argc, char *argv[])
{
	unsigned short port;
	cout << "input port:" << endl;
	cin >> port;
	if (argc > 1)
	{
		port = atoi(argv[1]);
	}
	TCP server;
	server.bind_pi(port);

	int epfd = epoll_create(256);
	epoll_event ev;
	ev.data.fd = server.sock;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd, EPOLL_CTL_ADD, server.sock, &ev);
	epoll_event event[20];

	char buf[1024] = { 0 };
	const char* msg = "HTTP/1.1 200 OK\r\nContene_Length:1\r\n\r\nXH_Lu";
	int size_msg = strlen(msg);
	server.set_block(false);

	while (1)
	{
		int count = epoll_wait(epfd, event, 20, 500);
		if (count <= 0)
			continue;
		for (int i = 0; i < count; ++i)
		{
			if (event[i].data.fd == server.sock)
			{
				for (;;)
				{
					TCP client = server.accept();
					if (client.sock <= 0)
						break;
					ev.data.fd = client.sock;
					ev.events = EPOLLIN | EPOLLET;
					epoll_ctl(epfd, EPOLL_CTL_ADD, client.sock, &ev);
				}
			}
			else
			{
				TCP client;
				client.sock = event[i].data.fd;
				client.recv(buf, 1024);
				client.send(msg, size_msg);
				epoll_ctl(epfd, EPOLL_CTL_DEL, client.sock, &ev);
				client.close();
			}
		}
		
		//TCP client = server.accept();
		//TCPThread* tcp_th = new TCPThread(client);
		//std::thread th(&TCPThread::work, tcp_th);
		//th.detach();
	}
	server.close();


	return 0;
}