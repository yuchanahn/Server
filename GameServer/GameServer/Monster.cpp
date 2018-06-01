#include "Monster.h"
#include "Base_generated.h"
#include "CPoint.h"
#include "TimeManager.h"
#include "WriteManager.h"
#include "ClientSession.h"

oMonster::oMonster()
{
	SetEventTime(0.1f);
	TimeManager::GetInstance()->AddTimeEvent(this);

	Range = 3;
	MaxRange = 0.2f;
	TargetID = -1;
	ID = MonsterId++;
}

oMonster::~oMonster()
{

}

void oMonster::process()
{
	double S;
	CPoint<double> Target_pos;
	CPoint<double> my_pos(x, y);

	for (auto &pos : session::GetSession()) {
		Target_pos.x = pos.second->pos->x();
		Target_pos.y = pos.second->pos->y();

		S = GetDistance(Target_pos, my_pos);

		if (Range <= S) {
			TargetID = pos.first;
			break;
		}
	}

	if (TargetID == -1) {
		Target_pos.x = 0;
		Target_pos.y = 0;

		S = GetDistance(Target_pos, my_pos);
	}

	if (MaxRange > S) { //아니라면 이동안함, 인공지능 무브라면 랜덤좌표 수정.
		x += (Target_pos.x - x) / S;
		y += (Target_pos.y - y) / S;
	}

	flatbuffers::FlatBufferBuilder fbb;
	WriteManager::write(CreateMonster(fbb, Class::Class_Monster, new Vec3(x, 0, y), ID, TargetID), fbb);

}

int oMonster::MonsterId;