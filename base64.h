#pragma once
#include <numeric>
#include <string>
#include <vector>

std::string toBase64(const std::vector<uint8_t>& buf);
std::vector<uint8_t> fromBase64(const std::string& buf);