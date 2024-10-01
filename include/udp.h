#ifndef UDP_H
#define UDP_H


#ifdef _WIN32

#ifdef XSOCKET_EXPORTS
#define XSOCKET_API __declspec(dllexport)
#else
#define XSOCKET_API __declspec(dllimport)
#endif

#else
#define XSOCKET_API
#endif


class XSOCKET_API UDP
{
private:
	void* addr = 0;
protected:
	int sock = 0;
public:
	UDP();
	~UDP();
	int create_socket();
	void close();
	bool bind_pi(unsigned short port);
	char ip[16];
	unsigned short port;
	int recv(char* buf, int bufsize);


};


#endif
