#include "user.h"
#include <math.h>
#include <random>
#include <functional>

using namespace std;

uint64_t User::generate_x() const {
    uniform_int_distribution<> distr(uint32_t{1}, numeric_limits<uint32_t>::max());
    mt19937 gen{};
    return distr(gen);
}

void User::receive_message(const uint64_t message) {
    secret = (uint64_t)pow(message, x) % p;
}

uint64_t User::get_h() const {
    return (uint64_t)pow(g, x) % p;
}