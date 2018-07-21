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


bool MysqlManager::UserLogin(LoginT * data)
{
	printf("---UserLogin----\n");
	if (GetLoginData(data) == eLogin::passSame) {
		return true;
		printf("UserLogin end \n");
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
			atoi(m["StartX"][i]),
			atoi(m["StartY"][i]),
			atoi(m["HP"][i]),
			atoi(m["Exp"][i])
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


	auto pos = new Vec3(player->pos->x(), player->pos->y(), player->pos->z());

	sprintf(str, "UPDATE `Main`.`PlayerInfo` SET `X`='%lf' ,`Y`='%lf' ,`Z`='%lf' WHERE  `UserKey`=%d LIMIT 1;", pos->x(), pos->y(), pos->z(), player->ID);
	mysql->executeSql(str);
}

PlayerStatT MysqlManager::GetPlayerStat(int id)
{
	auto m = mysql->executeSql("select * from PlayerInfo");

	PlayerStatT stat;


	stat.HP = stoi(m["Hp"][id]);
	stat.HPLim = stoi(m["HpLim"][id]);
	

	return stat;
}

Vec3 MysqlManager::GetPlayerPos(int id)
{
	auto m = mysql->executeSql("select * from PlayerInfo");

	Vec3 v3(stof(m["X"][id]), stof(m["Y"][id]), stof(m["Z"][id]));

	return v3;
}

bool MysqlManager::isPlayerID(char * id)
{
	char str[500];
	sprintf(str, "select count(*) from LoginData Where LoginData.id = '%s';", id);
	return GetDataCount_LogIn(str);	
	
}

bool MysqlManager::isPlayerPass(char * pass)
{
	char str[500];
	sprintf(str, "select count(*) from LoginData Where LoginData.pass = '%s';", pass);
	return GetDataCount_LogIn(str);
}

int MysqlManager::GetDataCount_LogIn(char * str)
{
	auto m2 = mysql->executeSql("select * from LoginData");
	printf("data : %s\n-------------\n", m2["key"][0]);

	auto m = mysql->executeSql_str(str);
	return stoi(m);
}

int MysqlManager::GetPlayerID_KEY(LoginT * data)
{
	printf("---------- GetPlayerID_KEY start ---------\n");
	char str[500];
	//sprintf(str, "select LoginData.key from LoginData Where LoginData.id = '%s';", data->id.c_str());
	auto m = mysql->executeSql("select * from LoginData");
	printf("data : %s\n-------------\n", m["key"][0]);


	return 0;
}



eLogin MysqlManager::GetLoginData(LoginT * data)
{
	if (isPlayerID((char*)data->id.c_str())) {
		if (isPlayerPass((char*)data->pass.c_str())) {
			return eLogin::passSame;
		}
		return eLogin::idSame;
	}

	return eLogin::idNone;
}

