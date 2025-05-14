#ifndef ATTRIBUT_H
#define ATTRIBUT_H

#include <string>
using namespace std;

class Attribut {
protected:
    string idAttribut;
    string unit;
    string description;

public:
    Attribut(string id = "", const string& u = "", const string& d = "");
    string getIdAttribut() const;
    string getUnit() const;
    string getDescription() const;
    void setIdAttribut(string id);
    void setUnit(const string& u);
    void setDescription(const string& d);
};

#endif // ATTRIBUT_H
