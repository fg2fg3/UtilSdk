#include "epollserver.h"



epollserver::epollserver()
{
	socketfd = 0;
	memset(&servaddr, 0, sizeof(servaddr));
}


epollserver::~epollserver()
{
}

bool epollserver::start(int port, bool isblock)
{
	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
		return false;
	}
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP��ַ���ó�INADDR_ANY,��ϵͳ�Զ���ȡ������IP��ַ��
	servaddr.sin_port = htons(port);
	if (!isblock) {
		int flags = fcntl(socketfd, F_GETFL, 0);
		fcntl(socketfd, F_SETFL, flags | O_NONBLOCK);//����Ϊ������
	}

	//�������õ�ַ����ֹAddress already in use
	int on = 1;
	if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1){
		snprintf(err_msg, sizeof(err_msg), "set reuse addr error: %s(errno: %d)\n", strerror(errno), errno);
		return false;
	}

	//�����ص�ַ�󶨵����������׽�����  
	if (bind(socketfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
		snprintf(err_msg, sizeof(err_msg), "bind socket error: %s(errno: %d)\n", strerror(errno), errno);
		return false;
	}
	//��ʼ�����Ƿ��пͻ�������  
	if (listen(socketfd, 5) == -1) {
		snprintf(err_msg, sizeof(err_msg), "listen socket error: %s(errno: %d)\n", strerror(errno), errno);
		return false;
	}
	std::cout << "create socket success\n";
	return true;
}

int epollserver::get_socketfd()
{
	return socketfd;
}

bool epollserver::do_epoll()
{
	struct epoll_event events[MAXEVENTS];
	int ret;
	char buf[MAXBUFFSIZE] = { 0 };
	int buflen = 0;
	//����һ��������
	if ((epollfd = epoll_create(FDSIZE)) == -1){
		snprintf(err_msg, sizeof(err_msg), "listen socket error: %s(errno: %d)\n", strerror(errno), errno);
		return false;
	}
	//��Ӽ����������¼�
	add_event(socketfd, EPOLLIN);
	while (true) {
		//��ȡ�Ѿ�׼���õ��������¼�
		/*
		���Ҫ����read��ʱ
		1,����socket������
		2,����epoll_wait��ʱ1��
		3,ÿ�ν���epoll_wait֮ǰ�����������û��б��߳���ʱ��û��������û�.

		PS:ÿ���û���������, read֮����¸��û�last_requestʱ��, Ϊ������Ĳ���3����
		*/
		ret = epoll_wait(epollfd, events, MAXEVENTS, -1);
		handle_events(events, ret, buf, buflen);
	}
	close(epollfd);
}

void epollserver::add_event(int fd, int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	/*
	//�����ETģʽ������EPOLLET
	ev.events |= EPOLLET;
	//�����Ƿ�����
	int flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	*/
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

void epollserver::del_event(int fd, int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

void epollserver::mod_event(int fd, int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

void epollserver::handle_events(epoll_event * events, int num, char * buf, int &buflen)
{
	int i;
	int fd;
	//����ѡ�ñ���
	for (i = 0; i < num; i++) {
		fd = events[i].data.fd;
		//���������������ͺ��¼����ͽ��д���
		if ((fd == socketfd) && (events[i].events& EPOLLIN))
			handle_accept();
		else if (events[i].events & EPOLLIN)
			do_read(fd, buf, buflen);
		else if (events[i].events & EPOLLOUT)
			do_write(fd, buf, buflen);
		else
			close(fd);
	}
}

bool epollserver::handle_accept()
{
	int clifd;
	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen = sizeof(cliaddr);
	clifd = accept(socketfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
	if (clifd == -1) {
		snprintf(err_msg, sizeof(err_msg), "listen socket error: %s(errno: %d)\n", strerror(errno), errno);
		return false;
	}
	else {
		char msg[128] = { 0 };
		//��ȡ�˿ڴ���
		sprintf(msg,"accept a new client:%s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
		std::cout << msg;
		//���һ���ͻ����������¼�
		add_event(clifd, EPOLLIN);
	}
}

bool epollserver::do_read(int fd, char * buf, int &buflen)
{
	buflen = read(fd, buf, MAXBUFFSIZE);
	if (buflen == -1) {
		snprintf(err_msg, sizeof(err_msg), "read error: %s(errno: %d)\n", strerror(errno), errno);
		close(fd);
		del_event(fd, EPOLLIN);
		return false;
	}
	else if (buflen == 0) {
		close(fd);
		std::cout << "client close.\n";
		del_event(fd, EPOLLIN);
		return true;
	}
	else {
		char msg[MAXBUFFSIZE] = { 0 };
		sprintf(msg, "read message is:%s\n", buf);
		std::cout << msg;
		//�޸���������Ӧ���¼����ɶ���Ϊд
		mod_event(fd, EPOLLOUT);
	}
	return true;
}

bool epollserver::do_write(int fd, char * buf, int buflen)
{
	int nwrite;
	nwrite = write(fd, buf, buflen);
	if (nwrite == -1)
	{
		snprintf(err_msg, sizeof(err_msg), "write error: %s(errno: %d)\n", strerror(errno), errno);
		close(fd);
		del_event(fd, EPOLLOUT);
		return false;
	}
	else{ 
		char msg[MAXBUFFSIZE] = { 0 };
		sprintf(msg, "write message is:%s\n", buf);
		std::cout << msg;
		mod_event(fd, EPOLLIN);
	}
		
	memset(buf, 0, MAXBUFFSIZE);
	return true;
}

char * epollserver::get_errmsg()
{
	return err_msg;
}
