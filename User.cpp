#include "User.h"
#include <iostream>

User::User(const string& idUser, const string& idSensor)
    : idUser(idUser), idSensor(idSensor), nbPoints(0) {}

string User::getIdUser() const { return idUser; }
string User::getIdSensor() const { return idSensor; }
int User::getNbPoints() const { return nbPoints; }

void User::setIdUser(const string& id) { idUser = id; }
void User::setIdSensor(const string& id) { idSensor = id; }
void User::setNbPoints(int points) { nbPoints = points; }

