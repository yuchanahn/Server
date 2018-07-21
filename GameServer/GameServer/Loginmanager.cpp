#include "Loginmanager.h"
#include "MysqlManager.h"
#include "WriteManager.h"
#include "ReadManager.h"
#include "ClientSession.h"
#include "PlayerStat.h"
#include <iostream>



LoginManager::LoginManager()
{
	ReadManager::AddNEvent(Class::Class_LogIn, this);
	LoginData = new LoginT;
}


LoginManager::~LoginManager()
{
}


void LoginManager::EventProsess(oPlayer * d, Base * d2)
{
	((Login*)d2)->UnPackTo(LoginData);	
	MysqlManager m;

	if (LoginData->isSignin) {
		printf("isSignin.\n");
		if (m.UserLogin(LoginData)) {
			auto id = m.GetPlayerID_KEY(LoginData);

			printf("isSuccess.\n ------ id : %d\n------------\n", id);
			LoginData->isSignin = true;
			LoginData->id = std::to_string(id);

			flatbuffers::FlatBufferBuilder fbb;

			d->id = id;
			session::GetSession()[id] = ((session*)d)->shared_from_this();

			WriteManager::write<Login>(Login::Pack(fbb, LoginData), fbb, d);
		}
		else {

			printf("Not_Success.\n");
			LoginData->isSignin = false;

			flatbuffers::FlatBufferBuilder fbb;
			WriteManager::write<Login>(Login::Pack(fbb, LoginData), fbb, d);
		}

		//do_writeForServer("wait for login...");
		//LogManager::GetInstance()->Console()->info("Player is login...");
		//LogManager::GetInstance()->Log("Player 로그인 요청...");
	}
	else if(!LoginData->isSignin){
		printf("isSignUp.\n");
		if (m.CreateUserData(LoginData)) {

			printf("isSuccess.\n");
			m.CreateID(LoginData);

			auto id = m.GetPlayerID_KEY(LoginData);

			printf("i : %d\n\n",id);

			LoginData->isSignin = true;
			LoginData->id = id;

			flatbuffers::FlatBufferBuilder fbb;
			WriteManager::write<Login>(Login::Pack(fbb, LoginData), fbb, d);
		}
		else {

			printf("Not_Success.\n");
			LoginData->isSignin = false;

			flatbuffers::FlatBufferBuilder fbb;
			WriteManager::write<Login>(Login::Pack(fbb, LoginData), fbb, d);
		}

		//do_writeForServer("wait for isSignUp...");
		//LogManager::GetInstance()->Console()->info("Player isSignUp...");
		//LogManager::GetInstance()->Log("Player 회원가입 요청...");
	}
}
