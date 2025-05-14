#include "AirCleaner.h"
#include "Provider.h"

AirCleaner::AirCleaner(const string& id, float lat, float lon, time_t start, time_t stop)
    : idCleaner(id), latitude(lat), longitude(lon), startTimestamp(start), stopTimestamp(stop) {}

string AirCleaner::getIdCleaner() const { return idCleaner; }
float AirCleaner::getLatitude() const { return latitude; }
float AirCleaner::getLongitude() const { return longitude; }
time_t AirCleaner::getStartTimestamp() const { return startTimestamp; }
time_t AirCleaner::getStopTimestamp() const { return stopTimestamp; }

void AirCleaner::setIdCleaner(const string& id) { idCleaner = id; }
void AirCleaner::setLatitude(float lat) { latitude = lat; }
void AirCleaner::setLongitude(float lon) { longitude = lon; }
void AirCleaner::setStartTimestamp(time_t t) { startTimestamp = t; }
void AirCleaner::setStopTimestamp(time_t t) { stopTimestamp = t; }

void AirCleaner::setOwner(Provider* p) { owner = p; }
Provider* AirCleaner::getOwner() const { return owner; }
