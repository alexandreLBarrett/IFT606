#include <bitset>
#include <vector>

void encrypt(std::vector<bool> k, std::vector<bool> m);
void decrypt(std::vector<bool> k, std::vector<bool> c);
void generate(uint32_t n, std::vector<bool> k);