#ifndef TCP_H
#define TCP_H


#ifdef _WIN32

#ifdef XSOCKET_EXPORTS
#define XSOCKET_API __declspec(dllexport)
#else
#define XSOCKET_API __declspec(dllimport)
#endif

#else
#define XSOCKET_API
#endif



class XSOCKET_API TCP
{
public:
	int sock = 0;
	unsigned short port = 0;
	char ip[16];

	TCP();
	~TCP();
	int create_socket();
	bool bind_pi(unsigned short port);
	TCP accept();
	void close();
	int recv(char* buf, int bufsize);
	int send(const char* buf, int sendsize);
	bool connect(const char* ip, unsigned short port, int timeoutms);
	bool set_block(bool isblock);

};

#endif