#pragma once
#include "tcp.h"
#include "HttpResponse.h"
class HttpClient
{
private:
	TCP client;
	HttpResponse res;
public:
	HttpClient();
	~HttpClient();
	bool start(TCP client);
	void thfunc();
};

