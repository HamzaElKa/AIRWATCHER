#pragma once
#include <string>
using namespace std;

class User {
protected:
    string idUser;
    string idSensor;
    int nbPoints;

public:
    User(const string& idUser = "", const string& idSensor = "");

    string getIdUser() const;
    string getIdSensor() const;
    int getNbPoints() const;

    void setIdUser(const string& id);
    void setIdSensor(const string& id);
    void setNbPoints(int points);

};