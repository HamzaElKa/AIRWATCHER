#pragma once
#include "User.h"

class Government : public User {
protected:
    string field;  // par exemple : "ministère de la santé", "agence qualité air", etc.

public:
    Government(const string& id = "", const string& mdp = "", const string& f = "");

    string getField() const;
    void setField(const string& f);

    void connexion() const override;
};
