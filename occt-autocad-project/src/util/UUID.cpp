#include "occt_autocad/util/UUID.h"
#include <random>
#include <sstream>
#include <iomanip>

namespace occt_autocad {
namespace util {

static std::string random_hex(size_t len) {
    static thread_local std::mt19937_64 rng((std::random_device())());
    static const char *hex = "0123456789abcdef";
    std::string s;
    s.reserve(len);
    for (size_t i = 0; i < len; ++i) s.push_back(hex[rng() & 0xF]);
    return s;
}

std::string generateUUID() {
    // 生成一个类似 UUID 的 32 位 hex 字符串（不带连字符）
    return random_hex(8) + random_hex(4) + random_hex(4) + random_hex(4) + random_hex(12);
}

} // namespace util
} // namespace occt_autocad
