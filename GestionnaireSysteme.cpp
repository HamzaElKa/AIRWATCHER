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
#include "Mesure.h"

#include <fstream>
#include <sstream>
#include <algorithm>

//getters
vector<Attribut> GestionnaireSysteme::getAttributes() {
    return attributs;
}

vector<Sensor> GestionnaireSysteme::getSensors() {
    return sensors;
}
//constructeur
GestionnaireSysteme::GestionnaireSysteme() {
    // Initialisation des attributs et capteurs
    attributs.clear();
    sensors.clear();
}
//destructeur
GestionnaireSysteme::~GestionnaireSysteme() {
    // Libération des ressources si nécessaire
    // Les vecteurs sont automatiquement libérés à la destruction de l'objet
}
double GestionnaireSysteme::convertirEnAQI(const Mesure& mesure)
{
    string attribut = mesure.getIdAttribut();
    double valeur = mesure.getValeur();

    // PM2.5
    if (attribut == "PM2.5")
    {
        if (valeur <= 12) return valeur * 50 / 12;
        else if (valeur <= 35.4) return 50 + (valeur - 12.1) * (50.0 / (35.4 - 12.1));
        else return 100 + (valeur - 35.4) * (50.0 / (55.4 - 35.4));
    }
    // PM10
    else if (attribut == "PM10")
    {
        if (valeur <= 54) return valeur * 50 / 54;
        else if (valeur <= 154) return 50 + (valeur - 54) * (50.0 / 100.0);
        else return 100 + (valeur - 154) * (50.0 / 100.0);
    }
    // O3
    else if (attribut == "O3")
    {
        if (valeur <= 0.054) return valeur * 50 / 0.054;
        else if (valeur <= 0.070) return 50 + (valeur - 0.055) * (50.0 / (0.070 - 0.055));
        else return 100 + (valeur - 0.070) * (50.0 / 0.030);
    }

    return -1.0;
}
double GestionnaireSysteme::consulterMoyenneQualite(double longitude, double latitude, double rayon,
                                                    const string& dateDebut, const string& dateFin)
{
    double sommeAQI = 0.0;
    int compteur = 0;

    for (Sensor& capteur : sensors)
    {
        double distance = sqrt(pow(capteur.getLatitude() - latitude, 2) +
                               pow(capteur.getLongitude() - longitude, 2));

        if (distance <= rayon)
        {
            list<Mesure> mesures = capteur.getMesuresDansIntervalle(dateDebut, dateFin);
            for (const Mesure& mesure : mesures)
            {
                double aqi = convertirEnAQI(mesure);
                if (aqi >= 0)
                {
                    sommeAQI += aqi;
                    compteur++;
                }
            }
        }
    }

    if (compteur == 0)
        return -1.0;

    return sommeAQI / compteur;
}

void GestionnaireSysteme::loadData() {
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
