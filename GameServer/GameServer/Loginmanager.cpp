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
	const LoginData* l_data = GetLoginData(data_); // ������ȭ

	if (l_data->isSignin()) {	//�α����϶�.
		MysqlManager m;
		m.UserLogin(l_data);

		//do_writeForServer("wait for login...");
		//LogManager::GetInstance()->Console()->info("Player is login...");
		//LogManager::GetInstance()->Log("Player �α��� ��û...");
	}
	else if (!l_data->isSignin()) {	//ȸ�������϶�.
		MysqlManager m;
		m.CreateUserData(l_data);

		//do_writeForServer("wait for isSignUp...");
		//LogManager::GetInstance()->Console()->info("Player isSignUp...");
		//LogManager::GetInstance()->Log("Player ȸ������ ��û...");
	}
}
