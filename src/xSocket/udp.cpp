#include "udp.h"

#include<iostream>
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


UDP::UDP()
{
#ifdef _WIN64
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);

	memset(ip, 0, sizeof(ip));
#endif
}

UDP::~UDP()
{}

int UDP::create_socket()
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);  //UDPЭ��
	if (sock == -1)
	{
		cout << "create socket failed!\n" << endl;
	}
	return sock;
}

void UDP::close()
{
	if (sock <= 0)	return;
	closesocket(sock);
	if (addr)
	{
		delete addr;
	}
	addr = 0;
	sock = 0;
}

bool UDP::bind_pi(unsigned short port)
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

int UDP::recv(char* buf, int bufsize)
{
	if (sock <= 0)
		return 0;
	if (addr == 0)
	{
		addr = new sockaddr_in();
	}
	socklen_t len = sizeof(sockaddr_in);
	int re = recvfrom(sock, buf, bufsize, 0, (sockaddr*)addr, &len);
	return re;


}