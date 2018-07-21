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
	
	auto m = mysql->executeSql("select * from MonsterInfo");
	
	for (size_t i = 0; i < m["StartX"].size(); i++) {
		Monsters.push_back(new CreateMonsterData(
			m["Name"][i], 
			Getint(m["StartX"][i]),
			Getint(m["StartY"][i]),
			Getint(m["HP"][i]),
			Getint(m["Exp"][i])
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

void MysqlManager::SetPlayerStat(PlayerStatT * stat)
{
	char str[500];
	sprintf(str, "UPDATE `Main`.`PlayerInfo` SET `Hp`='%d' WHERE  `UserKey`=%d LIMIT 1;", stat->HP, stat->ID);
	mysql->executeSql(str);
}

void MysqlManager::SetPlayerPos(PlayerT * player)
{
	char str[500];
	auto m = mysql->executeSql("select * from PlayerInfo");

	int key = GetKey(player->ID);

	auto pos = new Vec3(player->pos->x(), player->pos->y(), player->pos->z());

	sprintf(str, "UPDATE `Main`.`PlayerInfo` SET `X`='%lf' ,`Y`='%lf' ,`Z`='%lf' WHERE  `UserKey`=%d LIMIT 1;", pos->x(), pos->y(), pos->z(), player->ID);
	mysql->executeSql(str);
}

PlayerStatT MysqlManager::GetPlayerStat(int id)
{
	auto m = mysql->executeSql("select * from PlayerInfo");

	PlayerStatT stat;
	int key = GetKey(id);


	stat.HP = stoi(m["Hp"][key]);
	stat.HPLim = stoi(m["HpLim"][key]);
	

	return stat;
}

Vec3 MysqlManager::GetPlayerPos(int id)
{
	int key = GetKey(id);
	auto m = mysql->executeSql("select * from PlayerInfo");

	Vec3 v3(stof(m["X"][key]), stof(m["Y"][key]), stof(m["Z"][key]));

	return v3;
}

int MysqlManager::GetPlayerID_KEY(LoginT * data)
{
	auto m = mysql->executeSql("select * from LoginData");

	for (size_t i = 0; i < m["id"].size(); i++) {
		if (!strncmp(data->id.c_str(), m["id"][i], data->id.length())) {
			return stoi(m["key"][i]);
		}
	}
}


int MysqlManager::GetKey(int id)
{
	auto m = mysql->executeSql("select * from PlayerInfo");
	int key;

	for (size_t i = 0; i < m["UserKey"].size(); i++) {
		if (stoi(m["UserKey"][i]) == id) { key = i; break; }
	}
	return key;
}

int MysqlManager::Getint(const char *str)
{
	return atoi(str);
}

eLogin MysqlManager::GetLoginData(LoginT * data)
{
	auto m = mysql->executeSql("select * from LoginData");

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

