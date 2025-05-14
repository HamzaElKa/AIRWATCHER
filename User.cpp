#include "User.h"
#include <iostream>

User::User(const string& id, const string& m) : idUser(id), mdp(m) {}

string User::getIdUser() const { return idUser; }
string User::getMdp() const { return mdp; }

void User::setIdUser(const string& id) { idUser = id; }
void User::setMdp(const string& m) { mdp = m; }

void User::connexion() const {
    cout << "Connexion utilisateur générique : " << idUser << endl;
}
