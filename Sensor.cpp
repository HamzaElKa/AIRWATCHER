#include "Sensor.h"

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
