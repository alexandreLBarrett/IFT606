#include <string>

class User {
    const uint64_t p;
    const uint64_t g;
    const uint32_t x;

    uint64_t secret = 0;

    // find random number in 1 .. 2^32
    uint32_t generate_x() const;
    uint64_t exponent_mod(uint64_t base, uint64_t exponent, uint64_t mod) const;
public:
    User(const uint64_t p, const uint64_t g)
        : p{p}, g{g}, x{generate_x()}
    {}

    // calculates (g^y)^x
    void receive_message(const uint64_t message);

    // calculates g^x
    uint64_t get_h() const;

    uint64_t get_secret() const { return secret; };
};