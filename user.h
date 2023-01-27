#include <string>

// TODO: Create a function for pow(g, x) mod p that doesnt overflow
class User {
    const uint64_t p;
    const uint64_t g;
    const uint64_t x;

    uint64_t secret = 0;

    // find random number in 1 .. 2^32
    uint64_t generate_x() const;
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