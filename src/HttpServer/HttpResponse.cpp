#include "HttpResponse.h"
#include<string>
#include<regex>
using namespace std;



HttpResponse::HttpResponse()
{

}

HttpResponse::~HttpResponse()
{

}

bool HttpResponse::set_request(std::string request)
{
	string src = request;
	string pattern = "^([A-Z]+) /([a-zA-Z0-9]*([.][a-zA-Z]*)?)[?]?(.*) HTTP/1";
	regex r(pattern);
	smatch mas;
	regex_search(src, mas, r);
	if (mas.size() == 0)
	{
		printf("%s failed!\n", pattern.c_str());
		return false;
	}
	string type = mas[1];
	string path = "/";
	path += mas[2];
	string filetype = mas[3];
	string query = mas[4];
	if (filetype.size() > 0)
		filetype = filetype.substr(1, filetype.size() - 1);
	printf("========info========\n");
	printf("type:[%s]\npath:[%s]\nfiletype:[%s]\nquery:[%s]\n",
		type.c_str(),
		path.c_str(),
		filetype.c_str(),
		query.c_str());
	printf("====================\n");
	if (type != "GET")
	{
		printf("Not Get!\n");
		return false;
	}
	string filename = path;
	if (path == "/")
	{
		filename = "/index.html";
	}
#ifdef _WIN32
	string filepath = "../src/HttpServer/html";
#else
	string filepath = "html";
#endif
	filepath += filename;

#ifdef _WIN32

#else
	if (filetype == "php")
	{
		string cmd = "php-cgi ";
		cmd += filepath;
		cmd += " ";
		for (int i = 0; i < query.size(); ++i)
		{
			if (query[i] == '&')
				query[i] = ' ';
		}
		cmd += query;

		cmd += ">";
		filepath += ".html";
		cmd += filepath;

		printf("%s\n", cmd.c_str());
		system(cmd.c_str());
	}

#endif

	fp = fopen(filepath.c_str(), "rb");

	if (!fp)
	{
		printf("open file %s failed!\n", filepath.c_str());
		return false;
	}

	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	fseek(fp, 0, 0);
	printf("file size is %d\n", filesize);
#ifdef _WIN32

#else
	if (filetype == "php")
	{
		char c;
		const char* r = "\r";
		int headsize = 0;
		while (fread(&c, 1, 1, fp) > 0)
		{
			headsize++;
			if (c == *r)
			{
				fseek(fp, 3, SEEK_CUR);
				headsize += 3;
				break;
			}
		}
		filesize -= headsize;
	}
#endif

	return true;
}

std::string HttpResponse::get_head()
{

	std::string rmsg = "";
	rmsg = "HTTP/1.1 200 OK\r\n";
	rmsg += "Server: HttpServer\r\n";
	rmsg += "Content-Type: text/html\r\n";
	rmsg += "Content-Length: ";
	char bsize[128] = { 0 };
	sprintf(bsize, "%d", filesize);
	rmsg += bsize;
	rmsg += "\r\n";
	rmsg += "\r\n";
	return rmsg;
}

int HttpResponse::read(char* buf, int bufsize)
{
	return fread(buf, 1, bufsize, fp);
}