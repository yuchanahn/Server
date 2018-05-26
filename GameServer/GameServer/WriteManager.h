#pragma once
#include <iostream>
#include "Base_generated.h"
#include "ClientSession.h"

class WriteManager
{
public:
	WriteManager();
	~WriteManager();

	template <typename T>
	static void write(flatbuffers::Offset<T> orc, flatbuffers::FlatBufferBuilder &fbb);


	template <typename T>
	static void write_not_me(flatbuffers::Offset<T> orc, flatbuffers::FlatBufferBuilder &fbb, oPlayer * m_id);

	template <typename T>
	static void write(flatbuffers::Offset<T> orc, flatbuffers::FlatBufferBuilder & , oPlayer * m_id);
};

template <typename T>
void WriteManager::write(flatbuffers::Offset<T> orc, flatbuffers::FlatBufferBuilder &fbb, oPlayer * m_id)
{
	fbb.Finish(orc);
	int len = fbb.GetSize();
	m_id->do_writeForServer((char*)fbb.GetBufferPointer(), len);
}

template <typename T>
void WriteManager::write(flatbuffers::Offset<T> orc, flatbuffers::FlatBufferBuilder &fbb)
{
	fbb.Finish(orc);
	int len = fbb.GetSize();

	for (auto &i : session::GetSession()) {
		i.second->do_writeForServer((char*)fbb.GetBufferPointer(), len);
	}
}

template <typename T>
void WriteManager::write_not_me(flatbuffers::Offset<T> orc, flatbuffers::FlatBufferBuilder &fbb, oPlayer * m_id)
{
	fbb.Finish(orc);
	int len = fbb.GetSize();

	for (auto i : session::GetSession()) {
		if (i.first != m_id->id)
			i.second->do_writeForServer((char*)fbb.GetBufferPointer(), len);
	}
}