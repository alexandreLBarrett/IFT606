#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "one_time_pad.h"
#include "exception.h"
#include "base64.h"

using namespace std;

int main(int argc, char** argv) {
    vector<string> args = { argv, argv + argc };

    string hex_key;
    string hex_message;
    uint8_t n;

    try {
        hex_key = args.at(1);
        hex_message = args.at(2);
        n = stoi(args.at(3));
    } catch(out_of_range&) {
        cerr << "Some arguments are missing" << endl;
        return -1;
    } catch(invalid_argument&) {
        cerr << "N is not a number" << endl;
        return -2;
    }

    vector<uint8_t> key = fromBase64(hex_key);
    vector<uint8_t> message = fromBase64(hex_key);

    cout << "[KEY]: " << hex_key << ", [MESSAGE]: " << hex_message << endl;
    cout << "Gen for N = " << (int)n << ": " << endl;
    auto gen_key = generate(n, key);

    try {
        // Alice encrypts
        auto cryptogram = encrypt(gen_key, message);

        cout << "[CRYPTOGRAM]: " << toBase64(cryptogram) << endl;

        // Send cryptogram to Eve

        // Bob decrypts
        auto decrypted_message = decrypt(gen_key, cryptogram);

        cout << "[DECRYPTED MESSAGE]: " << toBase64(decrypted_message) << endl;

    } catch(key_message_length_exception&) {
        cerr << "Key is not the same length as message or cryptogram!" << endl;
    }
}