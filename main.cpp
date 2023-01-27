#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

#include "user.h"

using namespace std;

int main(int argc, char** argv) {
    vector<string> args = { argv, argv + argc };

    uint64_t p, g;
    try {
        p = stoull(args.at(1));
        g = stoull(args.at(2));
    } catch(out_of_range&) {
        cerr << "Missing parameters you need at least 2 (p and g)" << endl;
        return -1;
    } catch(invalid_argument&) {
        cerr << "P and G must be integers" << endl;
        return -1;
    }

    User alice{ p, g };
    User bob{ p, g };
    User eve{ p, g };

    bob.receive_message(alice.get_h());
    alice.receive_message(bob.get_h());

    cout << "secrets: Bob = " << bob.get_secret() << ", Alice = " << alice.get_secret() << "\n";
}