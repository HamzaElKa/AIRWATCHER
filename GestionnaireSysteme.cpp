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
#include <cmath>

//getters
vector<Attribut> GestionnaireSysteme::getAttributes() {
    return attributs;
}

vector<Sensor> GestionnaireSysteme::getSensors() {
    return sensors;
}
Sensor* GestionnaireSysteme::getSensorById(const string& id) {
    for (Sensor& capteur : sensors)
    {
        if (capteur.getIdSensor() == id)
        {
            return &capteur; // Retourne le capteur trouvé
        }
    }
    return nullptr;
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
    const std::string& attribut = mesure.getIdAttribut();
    double valeur = mesure.getValue();

    if (attribut == "PM10")
    {
        if (valeur <= 54.0) return valeur * 50.0 / 54.0;
        else if (valeur <= 154.0) return 50.0 + (valeur - 54.0) * (50.0 / 100.0);
        else return 100.0 + (valeur - 154.0) * (50.0 / 100.0);
    }
    else if (attribut == "O3")
    {
        if (valeur <= 0.054) return valeur * 50.0 / 0.054;
        else if (valeur <= 0.070) return 50.0 + (valeur - 0.055) * (50.0 / (0.070 - 0.055));
        else return 100.0 + (valeur - 0.070) * (50.0 / 0.030);
    }

    return -1.0;
}

vector<pair<Sensor, double>> GestionnaireSysteme::classerCapteursParSimilarite(const string& idSensor, const string& dateDebut, const string& dateFin)
{
    vector<pair<Sensor, double>> resultats;
    Sensor* capteurReference = getSensorById(idSensor);
    if (!capteurReference)
        return resultats; // Capteur non trouvé

    // Obtenir les mesures du capteur de référence
    list<Mesure> mesuresRef = capteurReference->getMesuresDansIntervalle(dateDebut, dateFin);

    for (Sensor& capteur : sensors)
    {
        if (capteur.getIdSensor() == idSensor)
            continue; // Ignorer le capteur de référence

        list<Mesure> mesuresComparaison = capteur.getMesuresDansIntervalle(dateDebut, dateFin);
        double similarite = 0.0;

        // Calculer la similarité
        for (const Mesure& mRef : mesuresRef)
        {
            for (const Mesure& mComp : mesuresComparaison)
            {
                if (mRef.getIdAttribut() == mComp.getIdAttribut())
                {
                    similarite += fabs(mRef.getValue() - mComp.getValue());
                }
            }
        }
        if (!mesuresComparaison.empty())
            similarite /= mesuresComparaison.size();

        resultats.emplace_back(capteur, similarite);
    }

    // Trier par similarité décroissante
    sort(resultats.begin(), resultats.end(),
         [](const pair<Sensor, double>& a, const pair<Sensor, double>& b) {
             return a.second > b.second;
         });

    return resultats;
}
    

double GestionnaireSysteme::consulterMoyenneQualite(double longitude, double latitude, double rayon, const string& dateDebut, const string& dateFin)
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
        getline(ss, id, ';');
        getline(ss, unit, ';');
        getline(ss, description, ';');
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
