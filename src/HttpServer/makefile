OUTPUT_DIR = ../../bin
$(OUTPUT_DIR)/http_server:main.cpp HttpClient.cpp HttpResponse.cpp HttpServer.cpp
	g++ $+ -o $@ -I ../../include -std=c++11 -lpthread -lsocket -L../../bin