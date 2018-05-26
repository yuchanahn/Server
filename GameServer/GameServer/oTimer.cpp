#include "oTimer.h"
#include "TimeManager.h"


oTimer::oTimer()
{
}


oTimer::~oTimer()
{
}

void oTimer::Start()
{
	start = std::chrono::system_clock::now();
}

double oTimer::End()
{
	return ((std::chrono::duration<double>)(std::chrono::system_clock::now() - start)).count();
}
