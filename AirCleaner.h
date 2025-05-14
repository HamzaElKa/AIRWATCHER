#pragma once
#include <string>
#include <ctime>
class Provider;  // déclaration anticipée

using namespace std;

class AirCleaner {
protected:
    string idCleaner;
    float latitude;
    float longitude;
    time_t startTimestamp;
    time_t stopTimestamp;
    Provider* owner = nullptr; // ← optionnel

public:
    AirCleaner(const string& id = "", float lat = 0, float lon = 0, time_t start = 0, time_t stop = 0);

    string getIdCleaner() const;
    float getLatitude() const;
    float getLongitude() const;
    time_t getStartTimestamp() const;
    time_t getStopTimestamp() const;

    void setIdCleaner(const string& id);
    void setLatitude(float lat);
    void setLongitude(float lon);
    void setStartTimestamp(time_t t);
    void setStopTimestamp(time_t t);

    void setOwner(Provider* p);
    Provider* getOwner() const;
};
