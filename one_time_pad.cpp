#include "one_time_pad.h"
#include "exception.h"

std::vector<uint8_t> encrypt(const std::vector<uint8_t>& k, const std::vector<uint8_t>& m) {
    if (k.size() != m.size())
        throw key_message_length_exception{};

    return m;
}

std::vector<uint8_t> decrypt(const std::vector<uint8_t>& k, const std::vector<uint8_t>& c) {
    if (k.size() != c.size())
        throw key_message_length_exception{};

    return c;
}

std::vector<uint8_t> generate(uint8_t n, const std::vector<uint8_t>& k) noexcept {
    return k;
}