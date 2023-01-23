#pragma once
#include <bitset>
#include <vector>

using cryptogram = std::vector<uint8_t>;
using key = std::vector<uint8_t>;
using message = std::vector<uint8_t>;

cryptogram encrypt(const key& k, const message& m);
message decrypt(const key& k, const cryptogram& c);
key generate(uint8_t n, const key& k) noexcept;