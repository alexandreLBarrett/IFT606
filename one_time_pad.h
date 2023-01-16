#include <bitset>
#include <vector>

std::vector<bool> encrypt(const std::vector<bool>& k, const std::vector<bool>& m);
std::vector<bool> decrypt(const std::vector<bool>& k, const std::vector<bool>& c);
std::vector<bool> generate(uint32_t n, const std::vector<bool>& k);