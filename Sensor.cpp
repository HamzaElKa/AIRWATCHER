#include "Sensor.h"
time_t convertirEnTimeT(const string& dateStr)
{
    tm tm = {};
    istringstream ss(dateStr);
    ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return mktime(&tm);
}

list<Mesure> Sensor::getMesuresDansIntervalle(const string& dateDebut, const string& dateFin)
{
    list<Mesure> resultat;
    time_t debut = convertirEnTimeT(dateDebut);
    time_t fin = convertirEnTimeT(dateFin);

    for (const Mesure& m : mesures)
    {
        time_t t = convertirEnTimeT(m.getTimestamp());
        if (t >= debut && t <= fin)
        {
            resultat.push_back(m);
        }
    }

    return resultat;
}

Sensor::Sensor(string id, float lat, float lon)
    : idSensor(id), latitude(lat), longitude(lon) {}

string Sensor::getIdSensor() const { return idSensor; }
float Sensor::getLatitude() const { return latitude; }
float Sensor::getLongitude() const { return longitude; }
const list<Mesure>& Sensor::getMesures() const { return mesures; }

void Sensor::setIdSensor(string id) { idSensor = id; }
void Sensor::setLatitude(float lat) { latitude = lat; }
void Sensor::setLongitude(float lon) { longitude = lon; }

void Sensor::addMesure(const Mesure& m) {
    mesures.push_back(m);
}
