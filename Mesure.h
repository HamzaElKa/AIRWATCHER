#ifndef MESURE_H
#define MESURE_H

#include <string>
using namespace std;

class Mesure {
protected:
    string timestamp;
    string idAttribut;
    int value;

public:
    // Constructeur par défaut
    Mesure();
    Mesure(const string& t = "", string idAttr = "", int val = 0);

    string getTimestamp() const;
    string getIdAttribut() const;
    int getValue() const;
    void setTimestamp(const string& t);
    void setIdAttribut(string id);
    void setValue(int val);
};

#endif // MESURE_H