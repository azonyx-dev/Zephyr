#pragma once
#include <cstdint>
#include <string>

namespace zephyr
{
	enum class Status : int32_t
	{
		Ok = 0,
		Eof,
		BadMagic,
		UnsupportedVersion,
		BadFormat,
		DecryptFailed,
		DecompressFailed,
		HashMismatch,
		IoError,
	};

	struct Result
	{
		Status status = Status::Ok;
		std::string message;

		bool ok() const { return status == Status::Ok; }
		explicit operator bool() const { return ok(); }

		static Result Ok() { return { Status::Ok, {} }; }
		static Result Error(Status s, std::string m = {}) { return { s, std::move(m)}; }
	};
}