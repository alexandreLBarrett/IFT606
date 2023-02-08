#include "crypto.h"

uint64_t exponent_mod(uint64_t base, uint64_t exponent, uint64_t mod) {
    uint64_t result = 1;

    while (exponent > 0) {
        if ((exponent & 1) > 0) 
            result = (result * base) % mod;

        exponent >>= 1;
        
        base = (base * base) % mod;
    }

    return result;
}


uint64_t sign_rsa(const sk& secret_key, uint64_t message) {
    return exponent_mod(message, secret_key.d, secret_key.p * secret_key.q);
}

bool verify_rsa(const pk& public_key, uint64_t message, uint64_t signature) {
    return message == exponent_mod(signature, public_key.e, public_key.N);
}