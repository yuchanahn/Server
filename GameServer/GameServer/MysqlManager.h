#pragma once
#include <string>
#include <map>
#include <vector>
#include <list>

struct CreateMonsterData;
struct LoginT;

class MysqlPool;

enum class eLogin
{
	idSame,passSame,idNone
};

class MysqlManager
{

	MysqlPool * mysql;


	eLogin GetLoginData(LoginT * data);
	int GetInt(const char * );

public:
	MysqlManager();
	~MysqlManager();

	void MysqlTest();
	bool UserLogin(LoginT * data);
	bool CreateUserData(LoginT * data);
	void CreateID(LoginT * data);


	int GetPlayerID_KEY(LoginT * data);


	std::list<CreateMonsterData*> GetMonsterInfo();
};

