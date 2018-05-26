#include "NetworkSpeedTest.h"
#include "ReadManager.h"
#include "Base_generated.h"
#include "WriteManager.h"

NetworkSpeedTest::NetworkSpeedTest()
{
	ReadManager::AddNEvent(Class::Class_test, this);
}


NetworkSpeedTest::~NetworkSpeedTest()
{
}

void NetworkSpeedTest::EventProsess(oPlayer * d, Base * d2)
{
	flatbuffers::FlatBufferBuilder fbb;
	testT t;
	((test*)d2)->UnPackTo(&t);
	//printf("ping recv : %d \n", t.num);
	WriteManager::write<test>(test::Pack(fbb,&t),fbb,d);
}
