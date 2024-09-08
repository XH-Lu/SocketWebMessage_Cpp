#include "HttpServer.h"
#include "HttpClient.h"
#include<thread>
using namespace std;
HttpServer::HttpServer()
{

}

HttpServer::~HttpServer()
{

}

bool HttpServer::start(unsigned short port)
{
	isexit = false;
	server.create_socket();
	if (!server.bind_pi(port))
		return false;
	thread sth(&HttpServer::thfunc, this);
	sth.detach();
	return true;
}

void HttpServer::thfunc()
{
	while (!isexit)
	{
		TCP client = server.accept();
		if (client.sock <= 0)
			continue;
		HttpClient* cth = new HttpClient();
		cth->start(client);
	}
}

void HttpServer::stop()
{
	isexit = true;
}
