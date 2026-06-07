#pragma once
#include "../../../include/Zephyr/Pak/PakTypes.hpp"
#include "../../../include/Zephyr/Core/Result.hpp"
using namespace zephyr;
using namespace zephyr::pak;

namespace zephyr::pak::codec
{
	class IFooterCodec
	{
	public:
		virtual ~IFooterCodec() = default;
		virtual i64 SerializedSize() const = 0;

		virtual Result Parse(const u8* buf, i64 len, PakFooter& out) const = 0;
		virtual Result Write(const PakFooter& in, u8* buf, i64 len) const = 0;
	};
}