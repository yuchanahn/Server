#include "Loginmanager.h"
#include "LoginData_generated.h"
#include "MysqlManager.h"
#include <iostream>



LoginManager::LoginManager()
{
}


LoginManager::~LoginManager()
{
}

void LoginManager::loginTo(char data_[1024])
{
	const LoginData* l_data = GetLoginData(data_); // 역직렬화

	if (l_data->isSignin()) {	//로그인일때.
		MysqlManager m;
		m.UserLogin(l_data);

		//do_writeForServer("wait for login...");
		//LogManager::GetInstance()->Console()->info("Player is login...");
		//LogManager::GetInstance()->Log("Player 로그인 요청...");
	}
	else if (!l_data->isSignin()) {	//회원가입일때.
		MysqlManager m;
		m.CreateUserData(l_data);

		//do_writeForServer("wait for isSignUp...");
		//LogManager::GetInstance()->Console()->info("Player isSignUp...");
		//LogManager::GetInstance()->Log("Player 회원가입 요청...");
	}
}
