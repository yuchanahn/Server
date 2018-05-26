#include "./ClientSession.h"
#include "EventManager.h"

int main(int argc, char* argv[]) {
	EventManager::GetInstance()->Add(session::playerLogin, Event::PlayerSignIn);

	try {
		asio::io_service io_service;
		server s(io_service, std::atoi("12588"));
		io_service.run();
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	

	return 0;
}
