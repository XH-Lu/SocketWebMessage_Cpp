#include<iostream>
#include "tcp.h"


#ifdef _WIN32
#include<windows.h>
#define socklen_t int
#else
#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#define closesocket ::close
#endif
#include<string.h>
using std::cout;
using std::cin;
using std::endl;
#define NUM_CONNECT_QUE 10

TCP::TCP()
{
#ifdef _WIN64
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);
#endif
}

TCP::~TCP()
{}


int TCP::create_socket()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);  //TCP/IPЭ�飬TCP
	if (sock == -1)
	{
		cout << "create socket failed!\n" << endl;
	}
	return sock;
}

bool TCP::bind_pi(unsigned short port)
{
	if (sock <= 0)
		create_socket();
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;  //ָ��TCPЭ��
	saddr.sin_port = htons(port);  //htons�����ֽ���ת��Ϊ�����ֽ��򣬴��2��2�ֽڣ���00000000 00000010��С��2��2�ֽڣ���00000010 00000000��x86ϵͳ��windows������һ��ΪС�ˣ������ֽ���Ϊ���
	saddr.sin_addr.s_addr = htonl(0);  //ָ��IP��ַ


	if (bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0)
	{
		cout << "bind port " << port << " failed!\n";
		return false;
	}
	cout << "bind port " << port << " success!\n";
	listen(sock, NUM_CONNECT_QUE);  //����˽������״̬
	return true;
}

TCP TCP::accept()
{
	TCP tcp;
	sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	int client = ::accept(sock, (sockaddr*)&caddr, &len);
	if (client <= 0) return tcp;

	cout << "accept client " << client << endl;
	char *ip = inet_ntoa(caddr.sin_addr);
#ifdef _WIN32
	strcpy_s(tcp.ip, sizeof(tcp.ip)/sizeof(char), ip);
#else
	strcpy(tcp.ip, ip);
#endif
	tcp.port = ntohs(caddr.sin_port);
	tcp.sock = client;
	cout << "client ip is " << tcp.ip << ", port is " << tcp.port << endl;
	return tcp;
}

void TCP::close()
{
	if (sock <= 0)	return;
	closesocket(sock);
	sock = 0;
}


int TCP::recv(char* buf, int bufsize)
{
	return ::recv(sock, buf, bufsize, 0);
}

int TCP::send(const char* buf, int sendsize)
{
	int s = 0;
	while (s != sendsize)
	{
		int len = ::send(sock, buf, sendsize - s, 0);
		if (len <= 0)	break;
		s += len;
	}
	return s;
}



bool TCP::connect(const char* ip, unsigned short port, int timeoutms)
{
	if (sock <= 0)
		create_socket();
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(ip);
	set_block(false);
	fd_set set;
	if (::connect(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0)
	{
		FD_ZERO(&set);
		FD_SET(sock, &set);
		timeval tm;
		tm.tv_sec = 0;
		tm.tv_usec = timeoutms * 1000;
		if (select(sock + 1, 0, &set, 0, &tm) <= 0)
		{
			cout << "connect timeout or error!" << endl;
			cout << "connect " << ip << ":" << port << " failed!" << endl;
			return false;
		}

	}
	set_block(true);
	cout << "connect " << ip << ":" << port << " success!" << endl;
	return true;
}


bool TCP::set_block(bool isblock)
{
	if (sock <= 0)
		return false;
#ifdef _WIN32
	unsigned long ul = 0;
	if (!isblock)
		ul = 1;  //������
	ioctlsocket(sock, FIONBIO, &ul);
#else
	int flags = fcntl(sock, F_GETFL, 0);
	if (flags < 0)
		return false;
	if (isblock)
	{
		flags = flags & ~O_NONBLOCK;
	}
	else
	{
		flags = flags | O_NONBLOCK;
	}
	if (fcntl(sock, F_SETFL, flags) != 0)
		return false;
#endif
	return true;
}