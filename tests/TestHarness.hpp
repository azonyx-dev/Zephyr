#pragma once
#include <cstdio>
#include <cstdlib>
#include <string_view>

static int g_passed = 0;
static int g_failed = 0;

#define CHECK(expr)                                                      \
    do {                                                                 \
        if (expr) {                                                      \
            ++g_passed;                                                  \
        } else {                                                         \
            ++g_failed;                                                  \
            std::fprintf(stderr, "FAIL  %s:%d  %s\n",                   \
                         __FILE__, __LINE__, #expr);                     \
        }                                                                \
    } while (0)

#define CHECK_EQ(a, b) CHECK((a) == (b))

inline int TestSummary()
{
    std::printf("%d passed, %d failed\n", g_passed, g_failed);
    return g_failed == 0 ? 0 : 1;
}
