#include "BoostCS.h"

io_service service;
std::vector<client_ptr> clients;

CBoostCS::CBoostCS()
{
}


CBoostCS::~CBoostCS()
{
}
class talk_to_svr : public boost::enable_shared_from_this<talk_to_svr>
	, boost::noncopyable {
	typedef talk_to_svr self_type;
	talk_to_svr(const std::string & username)
		: sock_(service), started_(true), username_(username), timer_(service) {}
	void start(ip::tcp::endpoint ep) {
		sock_.async_connect(ep, MEM_FN1(on_connect, _1));
	}
public:
	typedef boost::system::error_code error_code;
	typedef boost::shared_ptr<talk_to_svr> ptr;

	static ptr start(ip::tcp::endpoint ep, const std::string & username) {
		ptr new_(new talk_to_svr(username));
		new_->start(ep);
		return new_;
	}
	void stop() {
		if (!started_) return;
		std::cout << "stopping " << username_ << std::endl;
		started_ = false;
		sock_.close();
	}
	bool started() { return started_; }
private:
	void on_connect(const error_code & err) {
		if (!err)      do_write("login " + username_ + "\n");
		else            stop();
	}
	void on_read(const error_code & err, size_t bytes) {
		if (err) stop();
		if (!started()) return;
		// process the msg
		std::string msg(read_buffer_, bytes);
		if (msg.find("login ") == 0) on_login();
		else if (msg.find("ping") == 0) on_ping(msg);
		else if (msg.find("clients ") == 0) on_clients(msg);
		else std::cerr << "invalid msg " << msg << std::endl;
	}

	void on_login() {
		std::cout << username_ << " logged in" << std::endl;
		do_ask_clients();
	}
	void on_ping(const std::string & msg) {
		std::istringstream in(msg);
		std::string answer;
		in >> answer >> answer;
		if (answer == "client_list_changed") do_ask_clients();
		else postpone_ping();
	}
	void on_clients(const std::string & msg) {
		std::string clients = msg.substr(8);
		std::cout << username_ << ", new client list:" << clients;
		postpone_ping();
	}

	void do_ping() {
		do_write("ping\n");
	}
	void postpone_ping() {
		// note: even though the server wants a ping every 5 secs, we randomly 
		// don't ping that fast - so that the server will randomly disconnect us
		int millis = rand() % 7000;
		std::cout << username_ << " postponing ping " << millis
			<< " millis" << std::endl;
		timer_.expires_from_now(boost::posix_time::millisec(millis));
		timer_.async_wait(MEM_FN(do_ping));
	}
	void do_ask_clients() {
		do_write("ask_clients\n");
	}

	void on_write(const error_code & err, size_t bytes) {
		do_read();
	}
	void do_read() {
		async_read(sock_, buffer(read_buffer_),
			MEM_FN2(read_complete, _1, _2), MEM_FN2(on_read, _1, _2));
	}
	void do_write(const std::string & msg) {
		if (!started()) return;
		std::copy(msg.begin(), msg.end(), write_buffer_);
		sock_.async_write_some(buffer(write_buffer_, msg.size()),
			MEM_FN2(on_write, _1, _2));
	}
	size_t read_complete(const boost::system::error_code & err, size_t bytes) {
		if (err) return 0;
		bool found = std::find(read_buffer_, read_buffer_ + bytes, '\n') < read_buffer_ + bytes;
		// we read one-by-one until we get to enter, no buffering
		return found ? 0 : 1;
	}

private:
	ip::tcp::socket sock_;
	enum { max_msg = 1024 };
	char read_buffer_[max_msg];
	char write_buffer_[max_msg];
	bool started_;
	std::string username_;
	deadline_timer timer_;
};

class talk_to_client : public boost::enable_shared_from_this<talk_to_client>
	, boost::noncopyable {
	typedef talk_to_client self_type;
	talk_to_client() : sock_(service), started_(false),
		timer_(service), clients_changed_(false) {
	}
public:
	typedef boost::system::error_code error_code;
	typedef boost::shared_ptr<talk_to_client> ptr;

	void start() {
		started_ = true;
		clients.push_back(shared_from_this());
		last_ping = boost::posix_time::microsec_clock::local_time();
		// first, we wait for client to login
		do_read();
	}
	static ptr new_() {
		ptr new_(new talk_to_client);
		return new_;
	}
	void stop() {
		if (!started_) return;
		started_ = false;
		sock_.close();

		ptr self = shared_from_this();
		std::vector<client_ptr>::iterator it = std::find(clients.begin(), clients.end(), self);
		clients.erase(it);
		update_clients_changed();
	}
	bool started() const { return started_; }
	ip::tcp::socket & sock() { return sock_; }
	std::string username() const { return username_; }
	void set_clients_changed() { clients_changed_ = true; }
private:
	void on_read(const error_code & err, size_t bytes) {
		if (err) stop();
		if (!started()) return;
		// process the msg
		std::string msg(read_buffer_, bytes);
		if (msg.find("login ") == 0) on_login(msg);
		else if (msg.find("ping") == 0) on_ping();
		else if (msg.find("ask_clients") == 0) on_clients();
		else std::cerr << "invalid msg " << msg << std::endl;
	}

	void on_login(const std::string & msg) {
		std::istringstream in(msg);
		in >> username_ >> username_;
		std::cout << username_ << " logged in" << std::endl;
		do_write("login ok\n");
		update_clients_changed();
	}
	void on_ping() {
		do_write(clients_changed_ ? "ping client_list_changed\n" : "ping ok\n");
		clients_changed_ = false;
	}
	void on_clients() {
		std::string msg;
		for (std::vector<client_ptr>::const_iterator b = clients.begin(), e = clients.end(); b != e; ++b)
			msg += (*b)->username() + " ";
		do_write("clients " + msg + "\n");
	}

	void do_ping() {
		do_write("ping\n");
	}
	void do_ask_clients() {
		do_write("ask_clients\n");
	}

	void on_check_ping() {
		boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
		if ((now - last_ping).total_milliseconds() > 5000) {
			std::cout << "stopping " << username_ << " - no ping in time" << std::endl;
			stop();
		}
		last_ping = boost::posix_time::microsec_clock::local_time();
	}
	void post_check_ping() {
		timer_.expires_from_now(boost::posix_time::millisec(5000));
		timer_.async_wait(MEM_FN(on_check_ping));
	}


	void on_write(const error_code & err, size_t bytes) {
		do_read();
	}
	void do_read() {
		async_read(sock_, buffer(read_buffer_),
			MEM_FN2(read_complete, _1, _2), MEM_FN2(on_read, _1, _2));
		post_check_ping();
	}
	void do_write(const std::string & msg) {
		if (!started()) return;
		std::copy(msg.begin(), msg.end(), write_buffer_);
		sock_.async_write_some(buffer(write_buffer_, msg.size()),
			MEM_FN2(on_write, _1, _2));
	}
	size_t read_complete(const boost::system::error_code & err, size_t bytes) {
		if (err) return 0;
		bool found = std::find(read_buffer_, read_buffer_ + bytes, '\n') < read_buffer_ + bytes;
		// we read one-by-one until we get to enter, no buffering
		return found ? 0 : 1;
	}
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

void update_clients_changed() {
	for (std::vector<client_ptr>::iterator b = clients.begin(), e = clients.end(); b != e; ++b)
		(*b)->set_clients_changed();
}
ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));

void handle_accept(talk_to_client::ptr client, const boost::system::error_code & err) {
	client->start();
	talk_to_client::ptr new_client = talk_to_client::new_();
	acceptor.async_accept(new_client->sock(), boost::bind(handle_accept, new_client, _1));
}
