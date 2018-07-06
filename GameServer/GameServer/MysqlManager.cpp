#include "MysqlManager.h"
#include <iostream>


#include "mysqlpool.h"
#include "./LoginData_generated.h"
#include "./EventManager.h"
#include "oMonsterManager.h"

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

std::list<CreateMonsterData*> MysqlManager::GetMonsterInfo()
{
	std::list<CreateMonsterData*> Monsters;

	MysqlPool *mysql = MysqlPool::getMysqlPoolObject();
	mysql->setParameter("10.140.0.3", "anyc123", "123", "Monster", 3306, NULL, 0, 2);
	std::map<const std::string, std::vector<const char*>> m = mysql->executeSql("select * from MonsterInfo");

	for (size_t i = 0; i < m["StartX"].size(); i++) {
		/*printf("StartX - %s ,%d\n", m["StartX"][i], GetInt(m["StartX"][i]));
		printf("StartY - %s ,%d\n", m["StartY"][i], GetInt(m["StartY"][i]));
		printf("Exp - %s ,%d\n", m["Exp"][i], GetInt(m["Exp"][i]));
		printf("hp - %s ,%d\n", m["HP"][i], GetInt(m["HP"][i]));*/
		Monsters.push_back(new CreateMonsterData(
			m["Name"][i], 
			GetInt(m["StartX"][i]),
			GetInt(m["StartY"][i]), 
			GetInt(m["HP"][i]), 
			GetInt(m["Exp"][i])
		));
	}


	return Monsters;
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

int MysqlManager::GetInt(const char * data)
{
	return atoi(data);
}
