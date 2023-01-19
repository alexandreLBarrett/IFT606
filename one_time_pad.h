#pragma once
#include <bitset>
#include <vector>

template<class Op>
std::vector<uint8_t> oneTimeOperation(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b, const uint8_t n, Op func);
std::vector<uint8_t> encrypt(const std::vector<uint8_t>& k, const std::vector<uint8_t>& m, const uint8_t n);
std::vector<uint8_t> decrypt(const std::vector<uint8_t>& k, const std::vector<uint8_t>& c, const uint8_t n);
std::vector<uint8_t> generate(uint8_t size, const std::vector<uint8_t>& k, const uint8_t n) noexcept;