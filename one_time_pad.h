#pragma once
#include <bitset>
#include <vector>

using cryptogram = std::vector<uint8_t>;
using key = std::vector<uint8_t>;
using message = std::vector<uint8_t>;
using operand = std::vector<uint8_t>;

template<class Op>
operand oneTimeOperation(const operand& a, const operand& b, const uint8_t n, Op func);
cryptogram encrypt(const key& k, const message& m, const uint8_t n);
message decrypt(const key& k, const cryptogram& c, const uint8_t n);
key generate(uint8_t size, const key& k, const uint8_t n) noexcept;
