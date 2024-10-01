#include "udp.h"
#include<iostream>
using namespace std;


int main(int argc, char* argv[])
{
	unsigned short port = 514;	//514��Ĭ�ϵ�UDP��־����˿�
	UDP syslog;
	if (!syslog.bind_pi(port))
	{
		return -1;
	}
	char buf[2000] = { 0 };
	for (;;)
	{
		int len = syslog.recv(buf, sizeof(buf));
		if (len <= 0)
		{
			continue;
		}
		buf[len] = '\0';
		cout << buf << endl;
	}

	return 0;
}