#include "ClientSession.h"

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

#include "./Logmanager.h"
#include "./MysqlManager.h"
#include "./RedisManager.h"
#include "./EventManager.h"
#include "./TimeManager.h"
#include "./Loginmanager.h"
#include "./ReadManager.h"
#include "./PlayerMove.h"
#include "./Base_generated.h"
#include "./NetworkStartManager.h"
#include "ClientSession.h"
#include "NetworkSpeedTest.h"
#include "Ping.h"
#include "PlayerStat.h"
#include "StatSendManager.h"
#include "Monster.h"
#include "oMonsterManager.h"
#include "oMonsterStatManager.h"


using asio::ip::tcp;



std::map<int, std::shared_ptr<session>>& session::GetSession()
{
	static std::map<int, std::shared_ptr<session> > sessions;
	return sessions;
}

void session::start()
{
	try {
		//SetEventTime(3);
		//TimeManager::GetInstance()->AddTimeEvent(this);
		
		id = -1;
		//GetSession()[newID] = shared_from_this();
		NetworkStartManager::NetStart(this);
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
	do_read();
}

void session::playerLogin()
{
	//printf("Success Login\n");
}

void session::process()
{
	//printf("Time Out!\n");
}

void session::do_writeForServer(char * str, int len)
{
	auto self(shared_from_this());

	memset(data_, 0, 1024);
	memcpy(data_, str, len);

	asio::async_write(self->socket_, asio::buffer(data_, len)
		, [this, self](std::error_code ec, std::size_t length) {
		if (!ec) {
			//전송완료.
		}
		else {
			//예외.
		}
	});
}

void session::do_read()
{
	auto self(shared_from_this());
	//strand_.get_io_service().post(strand_.wrap([this, self] {
	socket_.async_read_some(asio::buffer(data_, max_length)
		, [this, self](std::error_code ec, std::size_t length) {
		if (!ec) {

			//TimeManager::GetInstance()->TimeReset(this);

							//로그인후 처리.	
			cpyData = new char[length];

			memset(cpyData, 0, length);
			memcpy(cpyData, data_, length);

			strand_.get_io_service().post(strand_.wrap([this, self] {
				char * currentData = cpyData;
				ReadManager::Read(currentData, this);
				delete currentData;
			}));
			memset(data_, 0, length);

			do_read();
			//do_read();
		}
		else {
			//strand_.get_io_service().post(strand_.wrap([this, self] {
			TimeManager::GetInstance()->Pop_TimeEvent(this);
			GetSession().erase(self->id);
			printf("socket OUT!\n");
			//}));
		}
	});
	//}));
}


void server::do_accept()
{

	//클라이언트 접속 대기
	acceptor_.async_accept(socket_,
		[this](std::error_code ec) {
		if (!ec) {
			asio::ip::tcp::no_delay option(true);
			socket_.set_option(option);
			//클라이언트 색션생성과 시작.
			std::make_shared<session>(std::move(socket_))->start();
		}
		//재귀호출이 아님.
		do_accept();
	});
}

void server::ServerStart()
{
	pingManger = new Ping;
	PlayerMoveManager = new PlayerMove;
	st = new NetworkSpeedTest;
	playerStat = new cPlayerStat;
	playerStatSend = new StatSendManager;
	MonStat = new oMonsterStatManager;
	login = new LoginManager;


	oMonsterManager::Start();
}




