#pragma once
#include "../../../include/Zephyr/Pak/PakTypes.hpp"
#include "../../../include/Zephyr/Core/Result.hpp"
#include "IEntryCodec.hpp"

using namespace zephyr;
using namespace zephyr::pak;

namespace zephyr::pak::codec
{
	class IIndexCodec
	{
		virtual ~IIndexCodec() = default;

		virtual Result Parse(const u8* primaryBlock, i64 primaryLength, const PakFooter& footer, const IEntryCodec& entryCodec, PakIndex& out) const = 0;
		virtual Result Write(const PakIndex& in, const IEntryCodec& entryCodec, std::vector<u8>& primaryOut, std::vector<u8>& pathHashOut, std::vector<u8>& fullDirOut) const = 0;
	};
}