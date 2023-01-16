#pragma once
#include <bitset>
#include <vector>

std::vector<uint8_t> encrypt(const std::vector<uint8_t>& k, const std::vector<uint8_t>& m);
std::vector<uint8_t> decrypt(const std::vector<uint8_t>& k, const std::vector<uint8_t>& c);
std::vector<uint8_t> generate(uint8_t n, const std::vector<uint8_t>& k) noexcept;