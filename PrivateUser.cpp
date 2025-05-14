#include "PrivateUser.h"
#include <iostream>

PrivateUser::PrivateUser(const string& id, const string& m, int pts)
    : User(id, m), nbPoints(pts), capteur(nullptr) {}

int PrivateUser::getNbPoints() const { return nbPoints; }
Sensor* PrivateUser::getSensor() const { return capteur; }

void PrivateUser::setNbPoints(int pts) { nbPoints = pts; }
void PrivateUser::setSensor(Sensor* s) { capteur = s; }

void PrivateUser::consulterProfil() const {
    cout << "Profil de l'utilisateur privé : " << idUser
         << " | Points : " << nbPoints << endl;

    if (capteur)
        cout << "Capteur associé : " << capteur->getIdSensor() << endl;
    else
        cout << "Aucun capteur associé." << endl;
}

void PrivateUser::connexion() const {
    cout << "Connexion utilisateur privé : " << idUser << endl;
}
