#include "tcp.h"
#include<iostream>



int main()
{
	TCP client;
	client.set_block(false);
	client.connect("192.168.56.1", 8080, 5000);  //等待连接时间5s
	client.send("hahaha", 6);
	char buf[1024] = { 0 };
	client.recv(buf, sizeof(buf));
	std::cout << buf << std::endl;
	getchar();

	return 0;
}

