#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <array>

namespace zephyr::pak
{
	using u8 = uint8_t;
	using u32 = uint32_t;
	using u64 = uint64_t;

	using i32 = int32_t;
	using i64 = int64_t;

	struct FGuid
	{
		u32 A = 0, B = 0, C = 0, D = 0;

		bool IsValid() const { return (A | B | C | D) != 0; }
	};

	struct FSHAHash 
	{ 
		std::array<u8, 20> bytes{}; 
	};

	struct CompressedBlock 
	{
		i64 start = 0;
		i64 end = 0;
	};

	struct PakFooter
	{
		FGuid keyGuid;
		bool encryptedIndex = false;
		i32 version = 0;
		i64 indexOffet = 0;
		i64 indexSize = 0;
		FSHAHash indexHash;
		std::vector<std::string> compressionMethods;
	};

	struct PakEntry
	{
		i64 offset = 0;
		i64 compressedSize = 0;
		i64 uncompressedSize = 0;
		u32 compressionMethodIndex = 0;
		FSHAHash hash;
		bool encrypted = false;
		bool deleted = false;
		u32 compressionBlockSize = 0;
		std::vector<CompressedBlock> blocks;
	};

	struct IndexSection 
	{
		bool present = false;
		i64 offset = 0;
		i64 size = 0;
		FSHAHash hash;
	};

	struct PakIndex {
		std::string mountPoint;
		i32 numEntries = 0;
		u64 pathHashSeed = 0;
		IndexSection pathHash;
		IndexSection fullDirectory;

		std::vector<std::string> paths;
		std::vector<PakEntry> entries;
	};


}