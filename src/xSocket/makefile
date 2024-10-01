OUTPUT_DIR = ../../bin
$(OUTPUT_DIR)/libsocket.so:tcp.cpp udp.cpp
	g++ $+ -o $@ -fpic -shared -I ../../include -std=c++11
