#include "Government.h"
#include <iostream>

Government::Government(const string& id, const string& mdp, const string& f)
    : User(id, mdp), field(f) {}

string Government::getField() const {
    return field;
}

void Government::setField(const string& f) {
    field = f;
}

void Government::connexion() const {
    cout << "Connexion administrateur gouvernemental : " << idUser
         << " | Département : " << field << endl;
}
