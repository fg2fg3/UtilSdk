#pragma once
class CBoostCS
{
public:
	CBoostCS();
	~CBoostCS();
};
/*
下面是客户端的实现
*/
//#include <boost/asio/detail/socket_types.hpp>
#include <iostream>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>

using namespace boost::asio;
using namespace boost::posix_time;


#define MEM_FN(x)       boost::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x,y)    boost::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z)  boost::bind(&self_type::x, shared_from_this(),y,z)

class talk_to_svr : public boost::enable_shared_from_this<talk_to_svr>
	, boost::noncopyable {

	void start(ip::tcp::endpoint ep);
public:
	typedef boost::system::error_code error_code;
	typedef boost::shared_ptr<talk_to_svr> ptr;

	static ptr start(ip::tcp::endpoint ep, const std::string & username);
	void stop();
	bool started();
private:
	void on_connect(const error_code & err);
	void on_read(const error_code & err, size_t bytes);

	void on_login();
	void on_ping(const std::string & msg);
	void on_clients(const std::string & msg);

	void do_ping();
	void postpone_ping();
	void do_ask_clients();

	void on_write(const error_code & err, size_t bytes);
	void do_read();
	void do_write(const std::string & msg);
	size_t read_complete(const boost::system::error_code & err, size_t bytes);

private:
	ip::tcp::socket sock_;
	enum { max_msg = 1024 };
	char read_buffer_[max_msg];
	char write_buffer_[max_msg];
	bool started_;
	std::string username_;
	deadline_timer timer_;
};

//int main(int argc, char* argv[]) {
//	// connect several clients
//	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);
//	char* names[] = { "John", "James", "Lucy", "Tracy", "Frank", "Abby", 0 };
//	for (char ** name = names; *name; ++name) {
//		talk_to_svr::start(ep, *name);
//		boost::this_thread::sleep(boost::posix_time::millisec(100));
//	}
//
//	service.run();
//}

/*
以下是服务端的实现
*/

void update_clients_changed();


/** simple connection to server:
- logs in just with username (no password)
- all connections are initiated by the client: client asks, server answers
- server disconnects any client that hasn't pinged for 5 seconds

Possible client requests:
- gets a list of all connected clients
- ping: the server answers either with "ping ok" or "ping client_list_changed"
*/
class talk_to_client : public boost::enable_shared_from_this<talk_to_client>
	, boost::noncopyable {
public:
	typedef boost::system::error_code error_code;
	typedef boost::shared_ptr<talk_to_client> ptr;

	void start();
	static ptr new_();
	void stop();
	bool started();
	ip::tcp::socket & sock();
	std::string username() const;
	void set_clients_changed();
private:
	void on_read(const error_code & err, size_t bytes);

	void on_login(const std::string & msg);
	void on_ping();
	void on_clients();

	void do_ping();
	void do_ask_clients();
	void on_check_ping();
	void post_check_ping();


	void on_write(const error_code & err, size_t bytes);
	void do_read();
	void do_write(const std::string & msg);
	size_t read_complete(const boost::system::error_code & err, size_t bytes);
private:
	ip::tcp::socket sock_;
	enum { max_msg = 1024 };
	char read_buffer_[max_msg];
	char write_buffer_[max_msg];
	bool started_;
	std::string username_;
	deadline_timer timer_;
	boost::posix_time::ptime last_ping;
	bool clients_changed_;
};


void handle_accept(talk_to_client::ptr client, const boost::system::error_code & err);

//int main(int argc, char* argv[]) {
//	talk_to_client::ptr client = talk_to_client::new_();
//	acceptor.async_accept(client->sock(), boost::bind(handle_accept, client, _1));
//	service.run();
//}


typedef boost::shared_ptr<talk_to_client> client_ptr;
typedef std::vector<client_ptr> array;