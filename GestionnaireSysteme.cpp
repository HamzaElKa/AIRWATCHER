/*
A programmer
Classement des capteurs similaires
    GetMesures(idCapteur,DateDebut,DateFin) (en utilisant celle des capteurs puis en filtrant)
    CalculerSimilarite(mesures1,mesures2)
    TrierCapteursParSimilarite(capteurs, mesures)
Calcul de la moyenne de l'AQI sur une zone et période donnée
    ChercherCapteursVoisins(Long,Lat)
Recuperer données du dossier data
    LoadData()
*/
#include "GestionnaireSysteme.h"


#include <fstream>
#include <sstream>
#include <algorithm>


void GestionnaireSysteme::LoadData() {
    // Charger les données des capteurs et des mesures a partir des csv dans le dossier data
    ifstream attrFile("data/attributes.csv");
    string line;
    getline(attrFile, line); // Ignore header line
    while (getline(attrFile, line)) {
        stringstream ss(line);
        string id, unit, description;
        getline(ss, id, ',');
        getline(ss, unit, ',');
        getline(ss, description, ',');
        if (!id.empty())
            attributs.emplace_back(id, unit, description);
    }
    attrFile.close();
    // Charger les capteurs
    ifstream sensorsFile("data/sensors.csv");
    while (getline(sensorsFile, line)) {
        stringstream ss(line);
        string id, latStr, lonStr;
        getline(ss, id, ';');
        getline(ss, latStr, ';');
        getline(ss, lonStr, ';');
        if (!id.empty())
            sensors.emplace_back(id, stof(latStr), stof(lonStr));
    }
    sensorsFile.close();

    // Charger les mesures
    ifstream measFile("data/measurements.csv");
    while (getline(measFile, line)) {
        stringstream ss(line);
        string date, sensorId, attrId, valueStr;
        getline(ss, date, ';');
        getline(ss, sensorId, ';');
        getline(ss, attrId, ';');
        getline(ss, valueStr, ';');
        if (sensorId.empty() || attrId.empty() || valueStr.empty()) continue;
        float value = stof(valueStr);

        // Trouver le capteur correspondant
        auto it = find_if(sensors.begin(), sensors.end(),
            [&](const Sensor& s) { return s.getIdSensor() == sensorId; });
        if (it != sensors.end()) {
            it->addMesure(Mesure(date, attrId, value));
        }
    }
    measFile.close();
}
