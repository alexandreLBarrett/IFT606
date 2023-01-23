#include "one_time_pad.h"
#include "exception.h"
#include <algorithm>

template<class Op> 
operand oneTimeOperation(const operand& a, const operand& b, const uint8_t n, Op func) {

    operand result(a.size());

    std::transform(a.begin(), a.end(), b.begin(), result.begin(), [=] (auto i, auto j) {
        return func(i, j) % n;
    });

    return result;
}

cryptogram encrypt(const key& k, const message& m, const uint8_t n) {
    
    return oneTimeOperation(m, k, n, std::plus{});
}

message decrypt(const key& k, const cryptogram& c, const uint8_t n) {

    return oneTimeOperation(c, k, n,
        [&](uint8_t a, uint8_t b) {
        int8_t res = a - b;
        return res < 0 ? res + n : res;
    });
}

key generate(uint8_t size, const key& k, const uint8_t n) noexcept {

    key res{k};
    res.reserve(size);

    for (size_t i = 0; res.size() < size; ++i) {
        res.emplace_back((res[i] ^ i) % n);
    }

    return res;
}