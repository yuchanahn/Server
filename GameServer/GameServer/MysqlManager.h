#pragma once
#include <string>
#include <map>
#include <vector>
#include <list>

struct CreateMonsterData;
struct LoginData;

enum class eLogin
{
	idSame,passSame,idNone
};

class MysqlManager
{



	eLogin GetLoginData(const LoginData * data);
	int GetInt(const char * );


public:
	MysqlManager();
	~MysqlManager();

	void MysqlTest();
	bool UserLogin(const LoginData * data);
	bool CreateUserData(const LoginData * data);

	std::list<CreateMonsterData*> GetMonsterInfo();
};

