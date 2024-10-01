#pragma once
#include<string>
class HttpResponse
{
private:
	int filesize;
	FILE* fp;
public:
	HttpResponse();
	~HttpResponse();
	bool set_request(std::string request);
	std::string get_head();
	int read(char* buf, int bufsize);
};

