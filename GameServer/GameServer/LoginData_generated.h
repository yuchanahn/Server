// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_LOGINDATA_H_
#define FLATBUFFERS_GENERATED_LOGINDATA_H_

#include <flatbuffers.h>

struct LoginData;

struct LoginData FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
	enum {
		VT_ISSIGNIN = 4,
		VT_ID = 6,
		VT_PASS = 8,
		VT_ISSUCCESS = 10
	};
	bool isSignin() const {
		return GetField<uint8_t>(VT_ISSIGNIN, 0) != 0;
	}
	const flatbuffers::String *id() const {
		return GetPointer<const flatbuffers::String *>(VT_ID);
	}
	const flatbuffers::String *pass() const {
		return GetPointer<const flatbuffers::String *>(VT_PASS);
	}
	bool isSuccess() const {
		return GetField<uint8_t>(VT_ISSUCCESS, 0) != 0;
	}
	bool Verify(flatbuffers::Verifier &verifier) const {
		return VerifyTableStart(verifier) &&
			VerifyField<uint8_t>(verifier, VT_ISSIGNIN) &&
			VerifyOffset(verifier, VT_ID) &&
			verifier.Verify(id()) &&
			VerifyOffset(verifier, VT_PASS) &&
			verifier.Verify(pass()) &&
			VerifyField<uint8_t>(verifier, VT_ISSUCCESS) &&
			verifier.EndTable();
	}
};

struct LoginDataBuilder {
	flatbuffers::FlatBufferBuilder &fbb_;
	flatbuffers::uoffset_t start_;
	void add_isSignin(bool isSignin) {
		fbb_.AddElement<uint8_t>(LoginData::VT_ISSIGNIN, static_cast<uint8_t>(isSignin), 0);
	}
	void add_id(flatbuffers::Offset<flatbuffers::String> id) {
		fbb_.AddOffset(LoginData::VT_ID, id);
	}
	void add_pass(flatbuffers::Offset<flatbuffers::String> pass) {
		fbb_.AddOffset(LoginData::VT_PASS, pass);
	}
	void add_isSuccess(bool isSuccess) {
		fbb_.AddElement<uint8_t>(LoginData::VT_ISSUCCESS, static_cast<uint8_t>(isSuccess), 0);
	}
	explicit LoginDataBuilder(flatbuffers::FlatBufferBuilder &_fbb)
		: fbb_(_fbb) {
		start_ = fbb_.StartTable();
	}
	LoginDataBuilder &operator=(const LoginDataBuilder &);
	flatbuffers::Offset<LoginData> Finish() {
		const auto end = fbb_.EndTable(start_);
		auto o = flatbuffers::Offset<LoginData>(end);
		return o;
	}
};

inline flatbuffers::Offset<LoginData> CreateLoginData(
	flatbuffers::FlatBufferBuilder &_fbb,
	bool isSignin = false,
	flatbuffers::Offset<flatbuffers::String> id = 0,
	flatbuffers::Offset<flatbuffers::String> pass = 0,
	bool isSuccess = false) {
	LoginDataBuilder builder_(_fbb);
	builder_.add_pass(pass);
	builder_.add_id(id);
	builder_.add_isSuccess(isSuccess);
	builder_.add_isSignin(isSignin);
	return builder_.Finish();
}

inline flatbuffers::Offset<LoginData> CreateLoginDataDirect(
	flatbuffers::FlatBufferBuilder &_fbb,
	bool isSignin = false,
	const char *id = nullptr,
	const char *pass = nullptr,
	bool isSuccess = false) {
	return CreateLoginData(
		_fbb,
		isSignin,
		id ? _fbb.CreateString(id) : 0,
		pass ? _fbb.CreateString(pass) : 0,
		isSuccess);
}

inline const LoginData *GetLoginData(const void *buf) {
	return flatbuffers::GetRoot<LoginData>(buf);
}

inline bool VerifyLoginDataBuffer(
	flatbuffers::Verifier &verifier) {
	return verifier.VerifyBuffer<LoginData>(nullptr);
}

inline void FinishLoginDataBuffer(
	flatbuffers::FlatBufferBuilder &fbb,
	flatbuffers::Offset<LoginData> root) {
	fbb.Finish(root);
}

#endif  // FLATBUFFERS_GENERATED_LOGINDATA_H_
