#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <list>
#include "Mesure.h"

using namespace std;

class Sensor {
protected:
    string idSensor;
    float latitude;
    float longitude;
    list<Mesure> mesures;

public:
    Sensor(string id = 0, float lat = 0.0f, float lon = 0.0f);
    string getIdSensor() const;
    float getLatitude() const;
    float getLongitude() const;
    const list<Mesure>& getMesures() const;
    void setIdSensor(string id);
    void setLatitude(float lat);
    void setLongitude(float lon);
    void addMesure(const Mesure& m);
    std::list<Mesure> getMesuresDansIntervalle(const std::string& dateDebut, const std::string& dateFin);
};

#endif // SENSOR_H