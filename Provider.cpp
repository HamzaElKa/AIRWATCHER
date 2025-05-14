#include "Provider.h"
#include <iostream>

Provider::Provider(const string& id, const string& mdp, const string& name)
    : User(id, mdp), companyName(name) {}

string Provider::getCompanyName() const {
    return companyName;
}

void Provider::setCompanyName(const string& name) {
    companyName = name;
}

void Provider::addAirCleaner(AirCleaner* cleaner) {
    airCleaners.push_back(cleaner);
}

const list<AirCleaner*>& Provider::getAirCleaners() const {
    return airCleaners;
}

void Provider::connexion() const {
    cout << "Connexion fournisseur : " << idUser
         << " | Société : " << companyName << endl;
}
