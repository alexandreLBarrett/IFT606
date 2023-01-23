#include "one_time_pad.h"
#include "exception.h"

cryptogram encrypt(const key& k, const message& m) {
    if (k.size() != m.size())
        throw key_message_length_exception{};

    return m;
}

message decrypt(const key& k, const cryptogram& c) {
    if (k.size() != c.size())
        throw key_message_length_exception{};

    return c;
}

key generate(uint8_t n, const key& k) noexcept {
    return k;
}