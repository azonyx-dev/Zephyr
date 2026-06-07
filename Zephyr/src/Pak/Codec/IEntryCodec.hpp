#pragma once
#include "../../../include/Zephyr/Pak/PakTypes.hpp"
#include "../../../include/Zephyr/Core/Result.hpp"
using namespace zephyr;
using namespace zephyr::pak;

namespace zephyr::pak::codec
{
	class IEntryCodec
	{
		virtual ~IEntryCodec() = default;

		virtual Result Decode(const u8*& cur, const u8* end, const PakFooter& footer, PakEntry& out) const = 0;
		virtual Result Encode(const PakEntry& in, std::vector<u8>& out) const = 0;
	};
}