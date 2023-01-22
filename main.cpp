#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "one_time_pad.h"
#include "exception.h"
#include "base64.h"

using namespace std;

/* ============================================
R�ponses aux sous questions de la question #1
sous la fonction main
============================================ */

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
    cout << "Gen for N = " << (int)n - 1  << ": " << endl;
    auto gen_key = generate(message.size(), key, n);
    cout << "[Extended Key]: " << toBase64(gen_key) << endl;

    try {
        // Alice encrypts
        auto cryptogram = encrypt(gen_key, message, n);
        cout << "[CRYPTOGRAM]: " << toBase64(cryptogram) << endl;

        // Send cryptogram to Eve
        auto eveCryptogram = cryptogram;

        // Bob decrypts
        auto decrypted_message = decrypt(gen_key, eveCryptogram, n);
        cout << "[DECRYPTED MESSAGE]: " << toBase64(decrypted_message) << endl;

    } catch(key_message_length_exception&) {
        cerr << "Key is not the same length as message or cryptogram!" << endl;
    }

}


/* ============================================
* 
--- Question 1.1 ---
Si Eve, n�a aucune information sur m et k avant de voir c, est-ce qu�elle
en apprend en voyant seulement c ?

> Si Eve sais que l'algorithme de cryptage est le OTP, en ayant acc�s au
cryptogramme, elle peut d�duire la longueur du message.


Si maintenant Eve apprend une telle paire (m, c), est-ce qu�elle apprend
beaucoup d�information sur k ? De combien de telles paires aurait-elle besoin
pour apprendre k ?

> Si Eve a une paire (m, c) et a acc�s au N, elle peut d�duire la clef.
Si elle n'a pas acc�s au N, elle n'obtient pas d'information par rapport
� la clef. Elle peut cependant d�duire que le N est plus grand ou inf�rieur
au nombre de lettres diff�rentes dans m ou dans c.

--- Question 1.2 ---
Associez chacun des 16 bits du message � une question vrai-faux de votre
choix. Est-il possible pour Eve de modifier c en c' tel que la r�ponse � la
premi�re question lorsque Bob d�crypte c'est le contraire de ce que Alice
avait r�pondu ? Comment ?

> Il est possible d�pendament de l'impl�mentation. Dans notre impl�mentation,
les chiffres vont de 0 � 9 et ils sont contigues. Cela signifit qu'Eve aurait
une chance sur deux. Par exemple, imaginons le message 0000000000000000 pour
un n de 64. Cela nous donne le cryptogramme : 01200034553A960. Eve, sachant
que le premier chiffre de la s�quence repr�sente soit un 0, soit un 1, elle 
peut modifier la valeur du premier caract�re en lui ajoutant, ou retirant 1.
Dans notre exemple, si Eve suppose qu'Alice � envoy� un 0 ou faux � la
premi�re question et qu'elle c' = c : ++c[0], Bob recevera alors le message
1000000000000000 lors du d�cryptage.
============================================ */