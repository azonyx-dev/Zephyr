#pragma once
#include "Codec/IEntryCodec.hpp"
#include "Codec/IFooterCodec.hpp"
#include "Codec/IIndexCodec.hpp"
#include <memory>

namespace zephyr::pak
{
	enum class EPakVer : i32
	{
		Initial = 1, 
		NoTimestamps, 
		CompressionEncryption, 
		IndexEncryption,
		RelativeChunkOffsets, 
		DeleteRecords, 
		EncryptionKeyGuid,
		FNameBasedCompressionMethod, 
		FrozenIndex, 
		PathHashIndex,
		Fnv64BugFix = 11,
	};

	struct PakVersionProfile
	{
		std::unique_ptr<codec::IFooterCodec> footer;
		std::unique_ptr<codec::IEntryCodec> entry;
		std::unique_ptr<codec::IIndexCodec> index;
		bool useFnv64Fixed = false;
	};
}