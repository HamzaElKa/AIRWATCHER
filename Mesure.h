#include <string>
using namespace std;

class Mesure {
protected:
    string timestamp;
    string idAttribut;
    int value;

public:
    Mesure(const string& t = "", string idAttr = 0, int val = 0);
    string getTimestamp() const;
    string getIdAttribut() const;
    int getValue() const;
    void setTimestamp(const string& t);
    void setIdAttribut(string id);
    void setValue(int val);
};
