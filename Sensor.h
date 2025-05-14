#include <string>
#include <list>
#include "Mesure.h"

using namespace std;

class Sensor {
protected:
    int idSensor;
    float latitude;
    float longitude;
    list<Mesure> mesures;

public:
    Sensor(int id = 0, float lat = 0.0f, float lon = 0.0f);
    int getIdSensor() const;
    float getLatitude() const;
    float getLongitude() const;
    const list<Mesure>& getMesures() const;
    void setIdSensor(int id);
    void setLatitude(float lat);
    void setLongitude(float lon);
    void addMesure(const Mesure& m);
};
