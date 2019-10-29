#pragma once
#include <sys/socket.h>  
#include <sys/epoll.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <fcntl.h>  
#include <unistd.h>  
#include <stdio.h>  
#include <string.h>
#include <errno.h>  
#include <iostream>  

#define MAXBUFFSIZE	1024
#define MAXEVENTS	500
#define FDSIZE	1000

class epollserver
{
public:
	epollserver();
	~epollserver();

private:
	int socketfd;
	struct sockaddr_in servaddr;
	int epollfd;
	char err_msg[256];
public:
	/*
	port:socket¶Ë¿Ú
	isblock:ÊÇ·ñ×èÈû
	*/
	bool start(int port, bool isblock = false);

	int get_socketfd();

	bool do_epoll();

	void add_event(int fd, int state);
	void del_event(int fd, int state);
	void mod_event(int fd, int state);

	void handle_events(struct epoll_event *events, int num, char* buf, int &buflen);

	bool handle_accept();

	bool do_read(int fd, char* buf, int &buflen);

	bool do_write(int fd, char* buf, int buflen);

	char* get_errmsg();
};
