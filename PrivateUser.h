#include <string>
#include "User.h"
#include "Sensor.h"

class PrivateUser : public User {
protected:
    int nbPoints;
    Sensor* capteur;

public:
    PrivateUser(const std::string& id, const std::string& mdp, int pts);
    int getNbPoints() const;
    Sensor* getSensor() const;
    void setNbPoints(int pts);
    void setSensor(Sensor* s);
    void consulterProfil() const;
    void connexion() const;
};
