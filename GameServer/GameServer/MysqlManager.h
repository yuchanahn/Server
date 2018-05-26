#pragma once
#include <string>
#include <map>
#include <vector>

struct LoginData;

enum class eLogin
{
	idSame,passSame,idNone
};

class MysqlManager
{



	eLogin GetLoginData(const LoginData * data);

public:
	MysqlManager();
	~MysqlManager();

	void MysqlTest();
	bool UserLogin(const LoginData * data);
	bool CreateUserData(const LoginData * data);
};

