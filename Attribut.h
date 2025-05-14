#include <string>
using namespace std;

class Attribut {
protected:
    int idAttribut;
    string unit;
    string description;

public:
    Attribut(int id = 0, const string& u = "", const string& d = "");
    int getIdAttribut() const;
    string getUnit() const;
    string getDescription() const;
    void setIdAttribut(int id);
    void setUnit(const string& u);
    void setDescription(const string& d);
};
