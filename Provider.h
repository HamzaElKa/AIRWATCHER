#ifndef PROVIDER_H
#define PROVIDER_H

#include <list>
#include "User.h"
#include "AirCleaner.h"

class Provider : public User {
protected:
    string companyName;
    list<AirCleaner*> airCleaners; // → 1 provider : plusieurs airCleaners

public:
    Provider(const string& id = "", const string& mdp = "", const string& name = "");

    string getCompanyName() const;
    void setCompanyName(const string& name);

    void addAirCleaner(AirCleaner* cleaner);
    const list<AirCleaner*>& getAirCleaners() const;

    void connexion() const override;
};

#endif // PROVIDER_H