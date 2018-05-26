#include "MysqlManager.h"
#include <iostream>


#include "mysqlpool.h"
#include "./LoginData_generated.h"
#include "./EventManager.h"

using namespace std;



MysqlManager::MysqlManager()
{
}


MysqlManager::~MysqlManager()
{

}

void MysqlManager::MysqlTest()
{
	MysqlPool *mysql = MysqlPool::getMysqlPoolObject();
	mysql->setParameter("10.140.0.3", "anyc123", "123", "Login", 3306, NULL, 0, 2);
	std::map<const std::string, std::vector<const char*> > m = mysql->executeSql("select * from user");
	for (std::map<const std::string, std::vector<const char*> >::iterator it = m.begin(); it != m.end(); ++it) {
		std::cout << it->first << std::endl;
		const std::string field = it->first;
		for (size_t i = 0; i < m[field].size(); i++) {
			std::cout << "[" << m[field][i] << "]" << std::endl;
		}
	}

	//mysql->executeSql("INSERT INTO user VALUES('anyc124', '1223');");
	delete mysql;
}

bool MysqlManager::UserLogin(const LoginData * data)
{
	if (GetLoginData(data) == eLogin::passSame) {
		return true;
	}
	return false;
}

bool MysqlManager::CreateUserData(const LoginData * data)
{
	if (GetLoginData(data) == eLogin::idNone) {
		return true;
	}
	return false;
}

eLogin MysqlManager::GetLoginData(const LoginData * data)
{
	MysqlPool *mysql = MysqlPool::getMysqlPoolObject();
	mysql->setParameter("10.140.0.3", "anyc123", "123", "Login", 3306, NULL, 0, 2);
	std::map<const std::string, std::vector<const char*>> m = mysql->executeSql("select * from user");

	for (size_t i = 0; i < m["id"].size(); i++) {
		if (!strncmp(data->id()->c_str(), m["id"][i], data->id()->Length())) {
			if (!strncmp(data->pass()->c_str(), m["pass"][i], data->pass()->Length())) {
				EventManager::GetInstance()->OnEvent(Event::PlayerSignIn);
				return eLogin::passSame;
			}
			else return eLogin::idSame;
		}
	}
	return eLogin::idNone;
}