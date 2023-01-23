#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "one_time_pad.h"
#include "exception.h"
#include "base64.h"

using namespace std;

/* ============================================
Réponses aux sous questions de la question #1
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
    ==================
    |   Question 1   |
    ==================

--- Question 1.1 ---
Si Eve, n’a aucune information sur m et k avant de voir c, est-ce qu’elle
en apprend en voyant seulement c ?

> Si Eve sais que l'algorithme de cryptage est le OTP, en ayant accès au
cryptogramme, elle peut déduire la longueur du message.


Si maintenant Eve apprend une telle paire (m, c), est-ce qu’elle apprend
beaucoup d’information sur k ? De combien de telles paires aurait-elle besoin
pour apprendre k ?

> Si Eve a une paire (m, c) et a accès au N, elle peut déduire la clef.
Si elle n'a pas accès au N, elle n'obtient pas d'information par rapport
à la clef. Elle peut cependant déduire que le N est plus grand ou inférieur
au nombre de lettres différentes dans m ou dans c.

--- Question 1.2 ---
Associez chacun des 16 bits du message à une question vrai-faux de votre
choix. Est-il possible pour Eve de modifier c en c' tel que la réponse à la
première question lorsque Bob décrypte c'est le contraire de ce que Alice
avait répondu ? Comment ?

> Il est possible dépendament de l'implémentation. Dans notre implémentation,
les chiffres vont de 0 à 9 et ils sont contigues. Cela signifit qu'Eve aurait
une chance sur deux. Par exemple, imaginons le message 0000000000000000 pour
un n de 64. Cela nous donne le cryptogramme : 01200034553A960. Eve, sachant
que le premier chiffre de la séquence représente soit un 0, soit un 1, elle 
peut modifier la valeur du premier caractère en lui ajoutant, ou retirant 1.
Dans notre exemple, si Eve suppose qu'Alice à envoyé un 0 ou faux à la
première question et qu'elle c' = c : ++c[0], Bob recevera alors le message
1000000000000000 lors du décryptage.


    ==================
    |   Question 2   |
    ==================

--- Question 2.1 ---
Vous pouvez supposer qu’Alice et Bob partagent une clé privée k qui est
secrète, intègre et authentifié. Si vous désirer faire des suppositions sur k,
prière de les noter ici. Donner le pseudo-code d’un protocole qui permet à
Alice d’envoyer le message m à Bob avec les propriétés suivantes:
- Robuste
- Confidentialité
- Intègre
- Authentifié

> Protocole MAC :

Alice et Bob s'entendent tous deux pour utiliser l'algorithme de Hashage Sha1.
Alice et Bob on accès à une fonction d'encryption et de décryption "Encrypt" et "Decrypt".
Alice et Bob partagent une clef "clef".

La transmission de message s'effectue comme suit :

message = getStringFromUser()
hash = Sha1( concat ( message, clef ) )
cryptogramme = Encrypt( message )

messageATransmettre = concat ( cryptogramme, '.', hash )

La réception s'effectue comme suit :

cryptogramme, hash = messageATransmettre.split( '.' )
message = Decrypt( cryptogramme )
hash' = Sha1( concat ( message, clef ) )

if( hash' != hash )
    dropProtocol()
else
    print( message )

*Note : Dans le protocole, les fonctions GenMAC, MAC et VerifMAC sont entremêlées.


Argumentation : 

> Robustesse : Si le message est modifié de quelconque manière, le cryptogramme,
ou le hash, hash et hash' du côté de Bob seront différent et le protocole sera
abandonné. Si ce n'est pas le cas, alors, le message sera décrypté et révelé à
Bob. 

> Confidentialité : Comme les messages envoyés sont encryptés, seulement Alice
et Bob peuvent voir le contenu des messages.

> Intégrité : Puisqu'on parle d'encryption et de décryption, les messages envoyés
sont intègres si Alice et Bob n'abandonnent pas le protocole.

> Bob peut s'assurer que le message reçu provient bien d'Alice à cause de leur clef.
Comme Alice et Bob partagent la même clef et que cette clef est privée et secrète, en
comparant hash et hash' avec leur clef, Bob est certain que le message vient d'Alice.
Cela prend pour acquis qu'Alice et Bob sont les seuls à partager leur clef.

============================================ */
