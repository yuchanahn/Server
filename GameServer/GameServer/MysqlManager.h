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

public:
	MysqlManager();
	~MysqlManager();

	bool UserLogin(LoginT * data);
	bool CreateUserData(LoginT * data);
	void CreateID(LoginT * data);



	void SetPlayerStat(PlayerStatT * stat);
	void SetPlayerPos(PlayerT * player);
	
	PlayerStatT GetPlayerStat(int id);
	Vec3 GetPlayerPos(int id);


	bool isPlayerID(char * id);
	bool isPlayerPass(char * pass);

	int GetDataCount_LogIn(char * str);


	int GetPlayerID_KEY(LoginT * data);

	std::list<CreateMonsterData*> GetMonsterInfo();
};

