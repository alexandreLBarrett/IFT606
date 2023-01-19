#include "one_time_pad.h"
#include "exception.h"
#include <algorithm>

template<class Op> 
std::vector<uint8_t> oneTimeOperation(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b, const uint8_t n, Op func) {

    std::vector<uint8_t> result(a.size());

    std::transform(a.begin(), a.end(), b.begin(), result.begin(), [=] (auto i, auto j) {
        return func(i, j) % n;
    });

    return result;
}

std::vector<uint8_t> encrypt(const std::vector<uint8_t>& k, const std::vector<uint8_t>& m, const uint8_t n) {

    return oneTimeOperation(m, k, n, std::plus{});
}

std::vector<uint8_t> decrypt(const std::vector<uint8_t>& k, const std::vector<uint8_t>& c, const uint8_t n) {

    return oneTimeOperation(c, k, n,
        [&](uint8_t a, uint8_t b) {
        int8_t res = a - b;
        return res < 0 ? res + n : res;
    });
}

std::vector<uint8_t> generate(uint8_t size, const std::vector<uint8_t>& k, const uint8_t n) noexcept {

    std::vector<uint8_t> res{k};
    res.reserve(size);

    for (size_t i = 0; res.size() < size; ++i) {
        res.emplace_back((res[i] ^ i) % n);
    }

    return res;
}