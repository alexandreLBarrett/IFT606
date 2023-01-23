#include "base64.h"
#include <algorithm>

std::string toBase64(const std::vector<uint8_t>& buf) { 
    std::string s(buf.size(), ' ');
    std::transform(buf.begin(), buf.end(), s.begin(), [](uint8_t val) -> char {
        if (val < 26) return 'A' + val;
        if (val < 52) return 'a' + val - 26;
        if (val < 62) return '0' + val - 52;
        if (val == 62) return '+';
        if (val == 63) return '/';
        return 0;
    });
    return s;
}

std::vector<uint8_t> fromBase64(const std::string& buf) { 
    std::vector<uint8_t> s(buf.size());
    std::transform(buf.begin(), buf.end(), s.begin(), [](char c) -> uint8_t {
        if (c >= 'A' && c <= 'Z') return (c - 'A');
        if (c >= 'a' && c <= 'z') return 26 + (c - 'a');
        if (c >= '0' && c <= '9') return 52 + (c - '0');
        if (c == '+') return 62;
        if (c == '/') return 63;
        return UINT8_MAX;
    });
    return s;
}