#pragma once
#include <string>
#include <map>
#include <vector>
#include <list>

struct CreateMonsterData;
struct LoginT;
struct PlayerStatT;
struct Vec3;
struct PlayerT;

class MysqlPool;

enum class eLogin
{
	idSame,passSame,idNone
};

class MysqlManager
{

	MysqlPool * mysql;


	eLogin GetLoginData(LoginT * data);
	int Getint(const char * );

public:
	MysqlManager();
	~MysqlManager();

	void MysqlTest();
	bool UserLogin(LoginT * data);
	bool CreateUserData(LoginT * data);
	void CreateID(LoginT * data);



	void SetPlayerStat(PlayerStatT * stat);
	void SetPlayerPos(PlayerT * player);
	
	PlayerStatT GetPlayerStat(int id);
	Vec3 GetPlayerPos(int id);


	int GetPlayerID_KEY(LoginT * data);
	int GetKey(int id);

	std::list<CreateMonsterData*> GetMonsterInfo();
};

