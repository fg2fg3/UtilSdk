#pragma once
#pragma execution_character_set("utf-8")

#include <iostream>  
#include "epollserver.h"
using namespace std;

int main(int argc, char **argv)
{
	epollserver myepoll;
	if(!myepoll.start(5000,false)){
		cout << myepoll.get_errmsg();
	}
	myepoll.do_epoll();
	return 0;
}
