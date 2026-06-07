#include "TestHarness.hpp"
#include <Zephyr/Core/ByteReader.hpp>
#include <cstdint>
#include <cstring>
#include <string>

using zephyr::core::ByteReader;

static void Test_ReadU8()
{
    const uint8_t data[] = { 0x00, 0x7F, 0xFF };
    ByteReader r(data, sizeof(data));

    CHECK_EQ(r.ReadU8(), 0x00u);
    CHECK_EQ(r.ReadU8(), 0x7Fu);
    CHECK_EQ(r.ReadU8(), 0xFFu);
    CHECK(r.Ok());
    CHECK_EQ(r.Remaining(), 0u);
}

static void Test_ReadU8_Overflow()
{
    const uint8_t data[] = { 0x01 };
    ByteReader r(data, sizeof(data));
    r.ReadU8();
    r.ReadU8();
    CHECK(!r.Ok());
}

static void Test_ReadU32_LittleEndian()
{
    const uint8_t data[] = { 0x78, 0x56, 0x34, 0x12 };
    ByteReader r(data, sizeof(data));
    CHECK_EQ(r.ReadU32(), 0x12345678u);
    CHECK(r.Ok());
    CHECK_EQ(r.Tell(), 4u);
}

static void Test_ReadU64_LittleEndian()
{
    const uint8_t data[] = { 0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01 };
    ByteReader r(data, sizeof(data));
    CHECK_EQ(r.ReadU64(), 0x0123456789ABCDEFull);
    CHECK(r.Ok());
}

static void Test_ReadI32_Negative()
{
    const uint8_t data[] = { 0xFF, 0xFF, 0xFF, 0xFF };
    ByteReader r(data, sizeof(data));
    CHECK_EQ(r.ReadI32(), -1);
    CHECK(r.Ok());
}

static void Test_ReadI64_Negative()
{
    const uint8_t data[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    ByteReader r(data, sizeof(data));
    CHECK_EQ(r.ReadI64(), -1LL);
    CHECK(r.Ok());
}

static void Test_ReadBytes()
{
    const uint8_t data[] = { 0xDE, 0xAD, 0xBE, 0xEF };
    ByteReader r(data, sizeof(data));

    uint8_t out[4] = {};
    r.ReadBytes(out, 4);
    CHECK(r.Ok());
    CHECK(std::memcmp(out, data, 4) == 0);
}

static void Test_Seek_And_Tell()
{
    const uint8_t data[] = { 0x01, 0x02, 0x03, 0x04 };
    ByteReader r(data, sizeof(data));
    r.Seek(2);
    CHECK_EQ(r.Tell(), 2u);
    CHECK_EQ(r.ReadU8(), 0x03u);
    CHECK(r.Ok());
}

static void Test_Seek_OOB()
{
    const uint8_t data[] = { 0x01 };
    ByteReader r(data, sizeof(data));
    r.Seek(999);
    CHECK(!r.Ok());
}

static void Test_ReadFString_ASCII()
{
    const char str[] = "hello\0";
    const int32_t len = 6;

    uint8_t data[4 + 6];
    std::memcpy(data, &len, 4);
    std::memcpy(data + 4, str, 6);

    ByteReader r(data, sizeof(data));
    std::string s = r.ReadFString();
    CHECK(r.Ok());
    CHECK_EQ(s, "hello");
}

static void Test_ReadFString_Empty()
{
    const int32_t len = 0;
    uint8_t data[4];
    std::memcpy(data, &len, 4);

    ByteReader r(data, sizeof(data));
    std::string s = r.ReadFString();
    CHECK(r.Ok());
    CHECK(s.empty());
}

static void Test_Remaining()
{
    const uint8_t data[] = { 0x01, 0x02, 0x03 };
    ByteReader r(data, sizeof(data));
    CHECK_EQ(r.Remaining(), 3u);
    r.ReadU8();
    CHECK_EQ(r.Remaining(), 2u);
}

int main()
{
    Test_ReadU8();
    Test_ReadU8_Overflow();
    Test_ReadU32_LittleEndian();
    Test_ReadU64_LittleEndian();
    Test_ReadI32_Negative();
    Test_ReadI64_Negative();
    Test_ReadBytes();
    Test_Seek_And_Tell();
    Test_Seek_OOB();
    Test_ReadFString_ASCII();
    Test_ReadFString_Empty();
    Test_Remaining();

    return TestSummary();
}
