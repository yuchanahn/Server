#include "MysqlManager.h"
#include <iostream>


#include "mysqlpool.h"
#include "./EventManager.h"
#include "Base_generated.h"
#include "oMonsterManager.h"

using namespace std;



MysqlManager::MysqlManager()
{
	mysql = MysqlPool::getMysqlPoolObject();
	mysql->setParameter("10.140.0.3", "anyc123", "123", "Main", 3306, NULL, 0, 2);
}


MysqlManager::~MysqlManager()
{

}

void MysqlManager::MysqlTest()
{
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

bool MysqlManager::UserLogin(LoginT * data)
{
	if (GetLoginData(data) == eLogin::passSame) {
		return true;
	}
	return false;
}

bool MysqlManager::CreateUserData(LoginT * data)
{
	if (GetLoginData(data) == eLogin::idNone) {
		return true;
	}
	return false;
}

std::list<CreateMonsterData*> MysqlManager::GetMonsterInfo()
{
	std::list<CreateMonsterData*> Monsters;

	std::map<const std::string, std::vector<const char*>> m = mysql->executeSql("SELECT * FROM  MonsterInfo");

	for (size_t i = 0; i < m["StartX"].size(); i++) {
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

void MysqlManager::CreateID(LoginT * data)
{
	char * str; 
	sprintf(str, "INSERT INTO LoginData (LoginData.id,LoginData.pass) VALUES('%s', '%s');", data->id.c_str(), data->pass.c_str());
	mysql->executeSql(str);
	
	printf("Create ID Success.\n");
}

int MysqlManager::GetPlayerID_KEY(LoginT * data)
{
	std::map<const std::string, std::vector<const char*>> m = mysql->executeSql("select * from LoginData");

	for (size_t i = 0; i < m["id"].size(); i++) {
		if (!strncmp(data->id.c_str(), m["id"][i], data->id.length())) {
			return stoi(m["key"][i]);
		}
	}
}


eLogin MysqlManager::GetLoginData(LoginT * data)
{
	std::map<const std::string, std::vector<const char*>> m = mysql->executeSql("select * from LoginData");

	//select count(*) from LoginData Where LoginData.id = '2323154';
	for (size_t i = 0; i < m["id"].size(); i++) {
		if (!strncmp(data->id.c_str(), m["id"][i], data->id.length())) {
			if (!strncmp(data->pass.c_str(), m["pass"][i], data->pass.length())) {
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
