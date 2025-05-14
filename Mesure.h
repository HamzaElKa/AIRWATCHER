#include <string>
using namespace std;

class Mesure {
protected:
    string timestamp;
    int idAttribut;
    int value;

public:
    Mesure(const string& t = "", int idAttr = 0, int val = 0);
    string getTimestamp() const;
    int getIdAttribut() const;
    int getValue() const;
    void setTimestamp(const string& t);
    void setIdAttribut(int id);
    void setValue(int val);
};
