//#ifdef _WIN32
//#include<windows.h>
//#define socklen_t int
//#else
//#include<sys/types.h>
//#include<sys/socket.h>
//#include <arpa/inet.h>
//#include<unistd.h>
//#define closesocket ::close
//#endif


//#include<thread>
//#include<string.h>
//#include<regex>
//#include "tcp.h"
#include<iostream>
#include "HttpServer.h"
#include<signal.h>

using namespace std;
//
//class TCPThread
//{
//
//private:
//	TCP client;
//public:
//	TCPThread()
//	{}
//	TCPThread(TCP c) : client(c)
//	{}
//	void close()
//	{
//		client.close();
//		delete this;
//	}
//	/*html
//	void work()
//	{
//		char buf[10000] = { 0 };
//		for (;;)
//		{
//			int recv_len = client.recv(buf, sizeof(buf) - 1);
//			if (recv_len <= 0)
//			{
//				close();
//				return;
//			}
//			buf[recv_len] = '\0';
//			printf("========recv========\n%s====================\n", buf);
//			string src = buf;
//			string pattern = "^([A-Z]+) (.+) HTTP/1";
//			regex r(pattern);
//			smatch mas;
//			regex_search(src, mas, r);
//			if (mas.size() == 0)
//			{
//				printf("%s failed!\n", pattern.c_str());
//				close();
//				return;
//			}
//			string type = mas[1];
//			string path = mas[2];
//			if (type != "GET")
//			{
//				close();
//				return;
//			}
//			string filename = path;
//			if (path == "/")
//			{
//				filename = "/index.html";
//			}
//#ifdef _WIN32
//			string filepath = "../src/HttpServer/html";
//#else
//			string filepath = "html";
//#endif
//			filepath += filename;
//
//			FILE* fp = fopen(filepath.c_str(), "rb");
//
//			if (!fp)
//			{
//				close();
//				return;
//			}
//
//			fseek(fp, 0, SEEK_END);
//			int filesize = ftell(fp);
//			fseek(fp, 0, 0);
//			printf("file size is %d\n", filesize);
//
//			std::string rmsg = "";
//			rmsg = "HTTP/1.1 200 OK\r\n";
//			rmsg += "Server: HttpServer\r\n";
//			rmsg += "Content-Type: text/html\r\n";
//			rmsg += "Content-Length: ";
//			char bsize[128] = { 0 };
//			sprintf(bsize, "%d", filesize);
//			rmsg += bsize;
//			rmsg += "\r\n";
//			rmsg += "\r\n";
//			client.send(rmsg.c_str(), rmsg.size());
//
//			for (;;)
//			{
//				int len = fread(buf, 1, sizeof(buf), fp);
//				if (len <= 0)
//					break;
//				int re = client.send(buf, len);
//				if (re <= 0)
//					break;
//			}
//		}
//		close();
//	}*/
//	/*html & php
//	void work()
//	{
//		char buf[10000] = { 0 };
//		for (;;)
//		{
//			int recv_len = client.recv(buf, sizeof(buf) - 1);
//			if (recv_len <= 0)
//			{
//				close();
//				return;
//			}
//			buf[recv_len] = '\0';
//			printf("========recv========\n%s====================\n", buf);
//			string src = buf;
//			string pattern = "^([A-Z]+) /([a-zA-Z0-9]*([.].*))? HTTP/1";
//			regex r(pattern);
//			smatch mas;
//			regex_search(src, mas, r);
//			if (mas.size() == 0)
//			{
//				printf("%s failed!\n", pattern.c_str());
//				close();
//				return;
//			}
//			string type = mas[1];
//			string path = "/";
//			path += mas[2];
//			string filetype = mas[3];
//			if (filetype.size() > 0)
//				filetype = filetype.substr(1, filetype.size() - 1);
//			printf("type:[%s]\npath:[%s]\nfiletype:[%s]\n", type.c_str(), path.c_str(), filetype.c_str());
//
//			if (type != "GET")
//			{
//				printf("Not Get!\n");
//				close();
//				return;
//			}
//			string filename = path;
//			if (path == "/")
//			{
//				filename = "/index.html";
//			}
//#ifdef _WIN32
//			string filepath = "../src/HttpServer/html";
//#else
//			string filepath = "html";
//#endif
//			filepath += filename;
//
//#ifdef _WIN32
//
//#else
//			if (filetype == "php")
//			{
//				string cmd = "php-cgi ";
//				cmd += filepath;
//				cmd += ">";
//				filepath += ".html";
//				cmd += filepath;
//				printf("%s\n", cmd.c_str());
//				system(cmd.c_str());
//			}
//#endif
//
//			FILE* fp = fopen(filepath.c_str(), "rb");
//
//			if (!fp)
//			{
//				printf("open file %s failed!\n", filepath.c_str());
//				close();
//				return;
//			}
//
//			fseek(fp, 0, SEEK_END);
//			int filesize = ftell(fp);
//			fseek(fp, 0, 0);
//			printf("file size is %d\n", filesize);
//#ifdef _WIN32
//
//#else
//			if (filetype == "php")
//			{
//				char c;
//				const char *r = "\r";
//				int headsize = 0;
//				while (fread(&c, 1, 1, fp) > 0)
//				{
//					headsize++;
//					if (c == *r)
//					{
//						fseek(fp, 3, SEEK_CUR);
//						headsize += 3;
//						break;
//					}
//				}
//				filesize -= headsize;
//			}
//#endif
//
//
//			std::string rmsg = "";
//			rmsg = "HTTP/1.1 200 OK\r\n";
//			rmsg += "Server: HttpServer\r\n";
//			rmsg += "Content-Type: text/html\r\n";
//			rmsg += "Content-Length: ";
//			char bsize[128] = { 0 };
//			sprintf(bsize, "%d", filesize);
//			rmsg += bsize;
//			rmsg += "\r\n";
//			rmsg += "\r\n";
//			client.send(rmsg.c_str(), rmsg.size());
//
//			for (;;)
//			{
//				int len = fread(buf, 1, sizeof(buf), fp);
//				if (len <= 0)
//					break;
//				int re = client.send(buf, len);
//				if (re <= 0)
//					break;
//			}
//		}
//		close();
//	}
//	*/
//	/* html php ? */
//void work()
//{
//	char buf[10000] = { 0 };
//	for (;;)
//	{
//		int recv_len = client.recv(buf, sizeof(buf) - 1);
//		if (recv_len <= 0)
//		{
//			close();
//			return;
//		}
//		buf[recv_len] = '\0';
//		printf("========recv========\n%s====================\n", buf);
//		string src = buf;
//		string pattern = "^([A-Z]+) /([a-zA-Z0-9]*([.][a-zA-Z]*)?)[?]?(.*) HTTP/1";
//		regex r(pattern);
//		smatch mas;
//		regex_search(src, mas, r);
//		if (mas.size() == 0)
//		{
//			printf("%s failed!\n", pattern.c_str());
//			close();
//			return;
//		}
//		string type = mas[1];
//		string path = "/";
//		path += mas[2];
//		string filetype = mas[3];
//		string query = mas[4];
//		if (filetype.size() > 0)
//			filetype = filetype.substr(1, filetype.size() - 1);
//		printf("type:[%s]\npath:[%s]\nfiletype:[%s]\nquery:[%s]\n",
//			type.c_str(),
//			path.c_str(),
//			filetype.c_str(),
//			query.c_str());
//
//		if (type != "GET")
//		{
//			printf("Not Get!\n");
//			close();
//			return;
//		}
//		string filename = path;
//		if (path == "/")
//		{
//			filename = "/index.html";
//		}
//#ifdef _WIN32
//		string filepath = "../src/HttpServer/html";
//#else
//		string filepath = "html";
//#endif
//		filepath += filename;
//
//#ifdef _WIN32
//
//#else
//		if (filetype == "php")
//		{
//			string cmd = "php-cgi ";
//			cmd += filepath;
//			cmd += " ";
//			for (int i = 0; i < query.size(); ++i)
//			{
//				if (query[i] == '&')
//					query[i] = ' ';
//			}
//			cmd += query;
//
//			cmd += ">";
//			filepath += ".html";
//			cmd += filepath;
//
//			printf("%s\n", cmd.c_str());
//			system(cmd.c_str());
//		}
//#endif
//
//		FILE* fp = fopen(filepath.c_str(), "rb");
//
//		if (!fp)
//		{
//			printf("open file %s failed!\n", filepath.c_str());
//			close();
//			return;
//		}
//
//		fseek(fp, 0, SEEK_END);
//		int filesize = ftell(fp);
//		fseek(fp, 0, 0);
//		printf("file size is %d\n", filesize);
//#ifdef _WIN32
//
//#else
//		if (filetype == "php")
//		{
//			char c;
//			const char* r = "\r";
//			int headsize = 0;
//			while (fread(&c, 1, 1, fp) > 0)
//			{
//				headsize++;
//				if (c == *r)
//				{
//					fseek(fp, 3, SEEK_CUR);
//					headsize += 3;
//					break;
//				}
//			}
//			filesize -= headsize;
//		}
//#endif
//
//
//		std::string rmsg = "";
//		rmsg = "HTTP/1.1 200 OK\r\n";
//		rmsg += "Server: HttpServer\r\n";
//		rmsg += "Content-Type: text/html\r\n";
//		rmsg += "Content-Length: ";
//		char bsize[128] = { 0 };
//		sprintf(bsize, "%d", filesize);
//		rmsg += bsize;
//		rmsg += "\r\n";
//		rmsg += "\r\n";
//		client.send(rmsg.c_str(), rmsg.size());
//
//		for (;;)
//		{
//			int len = fread(buf, 1, sizeof(buf), fp);
//			if (len <= 0)
//				break;
//			int re = client.send(buf, len);
//			if (re <= 0)
//				break;
//		}
//	}
//	close();
//}
//
//};


int main(int argc, char *argv[])
{
#ifdef _WIN32
#else
	signal(SIGPIPE, SIG_IGN);
#endif
	unsigned short port;
	cout << "input port:" << endl;
	cin >> port;
	if (argc > 1)
	{
		port = atoi(argv[1]);
	}
	HttpServer server;
	server.start(port);

	//TCP server;
	//server.bind_pi(port);
	//char buf[1024] = { 0 };
	//while (1)
	//{	
	//	TCP client = server.accept();
	//	TCPThread* tcp_th = new TCPThread(client);
	//	std::thread th(&TCPThread::work, tcp_th);
	//	th.detach();
	//}
	//server.close();

	getchar();
	getchar();
	return 0;
}