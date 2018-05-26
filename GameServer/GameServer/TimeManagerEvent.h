#pragma once


class TimeManagerEvent{

	double EventTime;
public:
	double GetEventTime() {
		return EventTime;
	}

	void SetEventTime(double _EventTime) {
		EventTime += _EventTime;
	}

	virtual void process() = 0;

	virtual ~TimeManagerEvent() {}
};