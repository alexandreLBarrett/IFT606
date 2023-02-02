#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

#include "user.h"

using namespace std;

void scenario_base(uint64_t p, uint64_t g) {
    cout << "-- SCENARIO DE BASE --\n\n";

    User alice{ p, g };
    User bob{ p, g };
    User eve{ p, g };

    auto requete_alice = alice.get_h();
    eve.receive_message(requete_alice);
    cout << "Eve intercepte le requete!!\n";
    cout << "Secret: Eve = " << eve.get_secret() << "\n";
    bob.receive_message(requete_alice);
    cout << "Secret: Bob = " << bob.get_secret() << "\n";

    if (eve.get_secret() == bob.get_secret()) cout << "Eve connait le secret de Bob :(\n";
    else                                      cout << "Eve ne connait pas le secret de Bob :)\n";

    auto reponse_bob = bob.get_h();
    eve.receive_message(reponse_bob);
    cout << "Eve intercepte la réponse!!\n";
    cout << "Secret: Eve = " << eve.get_secret() << "\n";
    alice.receive_message(reponse_bob);
    cout << "Secret: Alice = " << alice.get_secret() << "\n";

    if (eve.get_secret() == alice.get_secret()) cout << "Eve connait le secret de Alice :(\n";
    else                                        cout << "Eve ne connait pas le secret de Alice :)\n";

    if (bob.get_secret() == alice.get_secret()) cout << "Alice et bob partagent le meme secret!" << "\n";
    else                                        cout << "L'échange de clé a échouée" << "\n";

    cout << "\n";
}


void scenario_man_in_the_middle(uint64_t p, uint64_t g) {
    cout << "-- SCENARIO MAN IN THE MIDDLE --\n\n";

    User alice{ p, g };
    User bob{ p, g };

    User eve1{ p, g };

    auto requete_alice = alice.get_h();
    cout << "Eve intercepte le requete!!\n";

    eve1.receive_message(requete_alice);
    cout << "Secret: Eve = " << eve1.get_secret() << "\n";

    alice.receive_message(eve1.get_h());
    cout << "Secret: alice = " << alice.get_secret() << "\n";

    if (eve1.get_secret() == alice.get_secret()) cout << "Eve parle a Alice :(\n";
    else                                         cout << "Eve ne connait pas le secret de Alice :)\n";

    User eve2{ p, g };

    auto requete_eve = eve2.get_h();
    cout << "Eve envoie son message à Bob\n";

    bob.receive_message(requete_eve);
    cout << "Secret: Bob = " << bob.get_secret() << "\n";

    eve2.receive_message(bob.get_h());
    cout << "Secret: Eve = " << eve2.get_secret() << "\n";

    if (eve2.get_secret() == bob.get_secret()) cout << "Eve parle à Bob :(\n";
    else                                       cout << "Eve ne connait pas le secret de Bob :)\n";

    cout << "\n";
}


int main(int argc, char** argv) {
    vector<string> args = { argv, argv + argc };

    uint64_t p, g;
    try {
        p = stoull(args.at(1));
        g = stoull(args.at(2));
    } catch(out_of_range&) {
        cerr << "Il faut au moins 2 paramètres (p et g)" << endl;
        return -1;
    } catch(invalid_argument&) {
        cerr << "P et G doivent être des nombres entiers" << endl;
        return -1;
    }

    srand(time(NULL));

    scenario_base(p, g);
    scenario_man_in_the_middle(p, g);
}