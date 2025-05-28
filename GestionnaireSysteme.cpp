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
#include <cmath>
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

    if (attribut == "O3") // Ozone µg/m3
    {
        valeur = valeur * 240/100; // Conversion de % à µg/m3
        if (valeur <= 29) return 1;
        else if (valeur <= 54) return 2;
        else if (valeur <= 79) return 3;
        else if (valeur <= 104) return 4;
        else if (valeur <= 129) return 5;
        else if (valeur <= 149) return 6;
        else if (valeur <= 179) return 7;
        else if (valeur <= 209) return 8;
        else if (valeur <= 239) return 9;
        else return 10;
    }
    else if (attribut == "SO2") // Dioxyde de soufre µg/m3
    {
        valeur = valeur * 500/100; // Conversion de % à µg/m3
        if (valeur <= 39) return 1;
        else if (valeur <= 79) return 2;
        else if (valeur <= 119) return 3;
        else if (valeur <= 159) return 4;
        else if (valeur <= 199) return 5;
        else if (valeur <= 249) return 6;
        else if (valeur <= 299) return 7;
        else if (valeur <= 399) return 8;
        else if (valeur <= 499) return 9;
        else return 10;
    }
    else if (attribut == "NO2") // Dioxyde d'azote µg/m3
    {
        valeur = valeur * 400/100; // Conversion de % à µg/m3
        if (valeur <= 29) return 1;
        else if (valeur <= 54) return 2;
        else if (valeur <= 84) return 3;
        else if (valeur <= 109) return 4;
        else if (valeur <= 134) return 5;
        else if (valeur <= 164) return 6;
        else if (valeur <= 199) return 7;
        else if (valeur <= 274) return 8;
        else if (valeur <= 399) return 9;
        else return 10;
    }
    else if (attribut == "PM10") // Particules fines µg/m3
    {
        valeur = valeur * 80/100; // Conversion de % à µg/m3
        if (valeur <= 6) return 1;
        else if (valeur <= 13) return 2;
        else if (valeur <= 20) return 3;
        else if (valeur <= 27) return 4;
        else if (valeur <= 34) return 5;
        else if (valeur <= 41) return 6;
        else if (valeur <= 49) return 7;
        else if (valeur <= 64) return 8;
        else if (valeur <= 79) return 9;
        else return 10;
    }

    return -1.0; // Attribut non reconnu
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
    
#include <cmath>

static double haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0; // Rayon moyen de la Terre en km
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    double a = sin(dLat/2) * sin(dLat/2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return R * c;
}


double GestionnaireSysteme::consulterMoyenneQualite(double longitude, double latitude, double rayon, const string& dateDebut, const string& dateFin)
{
    double sommeAQI = 0.0;
    int compteur = 0;

    for (Sensor& capteur : sensors)
    {
        double distance = haversine(latitude, longitude, capteur.getLatitude(), capteur.getLongitude());

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
