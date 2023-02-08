#pragma once
#include <inttypes.h>

uint64_t exponent_mod(uint64_t base, uint64_t exponent, uint64_t mod);

struct sk {
    uint64_t p;
    uint64_t q;
    uint64_t d;
};

struct pk {
    uint64_t N;
    uint64_t e;
};

uint64_t sign_rsa(const sk& secret_key, uint64_t message);
bool verify_rsa(const pk& public_key, uint64_t message, uint64_t signature);