#include "HttpClient.h"
#include<thread>
using namespace std;


HttpClient::HttpClient()
{

}

HttpClient::~HttpClient()
{

}

bool HttpClient::start(TCP client)
{
	this->client = client;
	thread cth(&HttpClient::thfunc, this);
	cth.detach();
	return true;
}

void HttpClient::thfunc()
{
	char buf[10240] = { 0 };
	for (;;)
	{	
		int len = client.recv(buf, sizeof(buf) - 1);
		if (len <= 0)
			break;
		buf[len] = '\0';
		printf("========request========\n%s=======================\n", buf);
		if (!res.set_request(buf))
			break;
		string head = res.get_head();
		if (client.send(head.c_str(), head.size()) <= 0)
			break;
		int size = sizeof(buf);
		bool error = false;
		for(;;)
		{
			int len = res.read(buf, size);
			if (len < 0)
			{
				error = true;
				break;
			}
			if (len == 0)	break;
			if (client.send(buf, len) <= 0)
			{
				error = true;
				break;
			}
		}
	}

	client.close();
	delete this;
}