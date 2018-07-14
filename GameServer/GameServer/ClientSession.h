#pragma once
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <list>
#include <map>

#define ASIO_STANDALONE
#define ASIO_HEADER_ONLY

#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#define ASIO_HAS_VARIADIC_TEMPLATES
#define ASIO_HAS_STD_FUNCTION
#define ASIO_HAS_STD_CHRONO

#define BOOST_ALL_NO_LIB
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "./TimeManagerEvent.h"
#include "./Player.h"

#include <asio.hpp>

class oTimer;

using asio::ip::tcp;

class session : public TimeManagerEvent, public std::enable_shared_from_this<session>, public oPlayer {
public:
	bool isLogin = false;

	session(tcp::socket socket)
		: socket_(std::move(socket)),
		timer_(socket_.get_io_service()),
		strand_(socket_.get_io_service()) 
	{}

	~session() {
	}

	static std::map<int, std::shared_ptr<session> >& GetSession();
	void start();
	static void playerLogin();
	virtual void process();
	virtual void do_writeForServer(char * str, int len);


private:

	void do_read();
	int PlayerCount();

	tcp::socket socket_; //자신의 소켓
	asio::steady_timer timer_; //타이머.
	asio::io_service::strand strand_; //스트랜드


	enum { max_length = 1024 };
	char data_[max_length];
	char * cpyData;
};

class server {
public:
	server(asio::io_service& io_service, short port)
		: acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
		socket_(io_service) {


		ServerStart();
		do_accept();
	}

private:
	void do_accept();
	
	Ping * pingManger;
	PlayerMove * PlayerMoveManager;
	NetworkSpeedTest * st;
	cPlayerStat * playerStat;
	NetEvent * playerStatSend;
	oMonsterStatManager * MonStat;
	LoginManager * login;

	void ServerStart();

	tcp::acceptor acceptor_;
	tcp::socket socket_;
};



