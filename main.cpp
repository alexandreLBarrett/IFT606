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
        n = stoi(args.at(3)) + 1;
    } catch(out_of_range&) {
        cerr << "Some arguments are missing" << endl;
        return -1;
    } catch(invalid_argument&) {
        cerr << "N is not a number" << endl;
        return -2;
    }

    vector<uint8_t> key = fromBase64(hex_key);
    vector<uint8_t> message = fromBase64(hex_message);

    if (*std::max_element(key.begin(), key.end()) >= n) {
        cerr << "Invalid n value for given key" << endl;
        return -3;
    }
    else if (*std::max_element(message.begin(), message.end()) >= n) {
        cerr << "Invalid n value for given message" << endl;
        return -4;
    }

    cout << "[KEY]: " << hex_key << ", [MESSAGE]: " << hex_message << endl;
    cout << "Gen for N = " << (int)n << ": " << endl;
    auto gen_key = generate(message.size(), key, n);
    cout << "[Extended Key]: " << toBase64(gen_key) << endl;

    try {
        // Alice encrypts
        auto cryptogram = encrypt(gen_key, message, n);
        cout << "[CRYPTOGRAM]: " << toBase64(cryptogram) << endl;

        // Send cryptogram to Eve

        // Bob decrypts
        auto decrypted_message = decrypt(gen_key, cryptogram, n);
        cout << "[DECRYPTED MESSAGE]: " << toBase64(decrypted_message) << endl;

    } catch(key_message_length_exception&) {
        cerr << "Key is not the same length as message or cryptogram!" << endl;
    }

}