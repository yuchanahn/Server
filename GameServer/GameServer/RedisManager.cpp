#include "RedisManager.h"

#include <client.hpp>


RedisManager::RedisManager()
{
}


RedisManager::~RedisManager()
{
}

void RedisManager::Test()
{
	cpp_redis::client client;

	client.connect("localhost", 6379, [](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
		if (status == cpp_redis::client::connect_state::dropped) {
			std::cout << "client disconnected from " << host << ":" << port << std::endl;
		}
	});

	client.auth("123");

	client.set("test1", "324", [](cpp_redis::reply& reply) {
		std::cout << "set " << std::endl;
	});

	client.sync_commit();

	return;
}
