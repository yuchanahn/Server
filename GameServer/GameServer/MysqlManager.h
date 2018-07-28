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



public:
	MysqlManager();
	~MysqlManager();

	bool IsIdPassSame(LoginT * data , int * Id);
	bool IsIdNone(LoginT * data);
	int CreateID(LoginT * data);
	


	void SetPlayerStat(PlayerStatT * stat);
	void SetPlayerPos(PlayerT * player);
	
	PlayerStatT GetPlayerStat(int id);
	Vec3 * GetPlayerPos(int id);


	int isPlayerIDandPass(char * id, char * pass);

	int GetDataCount_LogIn(char * str);


	eLogin GetLoginData(LoginT * data, int * ID);

	std::list<CreateMonsterData*> GetMonsterInfo();
};

