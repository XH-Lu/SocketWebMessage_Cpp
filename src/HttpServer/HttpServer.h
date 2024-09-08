#pragma once
#include "tcp.h"
class HttpServer
{
private:
	bool isexit;
	TCP server;

public:
	HttpServer();
	~HttpServer();
	bool start(unsigned short port);
	void thfunc();
	void stop();
};

