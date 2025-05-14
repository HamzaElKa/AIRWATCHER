#include "User.h"
#include "Sensor.h"

class PrivateUser : public User {
protected:
    int nbPoints;
    Sensor* capteur;

public:
    PrivateUser(const string& id = "", const string& mdp = "", int pts = 0);

    int getNbPoints() const;
    Sensor* getSensor() const;

    void setNbPoints(int pts);
    void setSensor(Sensor* s);

    void consulterProfil() const;
    void connexion() const override; // redéfinition de la méthode connexion
};
