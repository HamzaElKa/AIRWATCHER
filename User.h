#pragma once
#include <string>
using namespace std;

class User {
protected:
    string idUser;
    string mdp;

public:
    User(const string& id = "", const string& m = "");

    string getIdUser() const;
    string getMdp() const;

    void setIdUser(const string& id);
    void setMdp(const string& m);

    virtual void connexion() const;  // virtuelle si besoin
};
