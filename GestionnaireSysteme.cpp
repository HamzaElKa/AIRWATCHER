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

vector<User> GestionnaireSysteme::getUsers() {
    return users;
}

Sensor* GestionnaireSysteme::getSensorById(const string& id) {
    for (Sensor& capteur : sensors)
    {
        if (capteur.getIdSensor() == id)
        {
            return &capteur; // Retourne le capteur trouve
        }
    }
    return nullptr;
}

User* GestionnaireSysteme::getUserBySensorId(const string& idSensor) {
    for (User& user : users) {
        if (user.getIdSensor() == idSensor)
            return &user;
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
    // Liberation des ressources si necessaire
    // Les vecteurs sont automatiquement libérés à la destruction de l'objet
}




double GestionnaireSysteme::convertirEnAQI(const Mesure& mesure)
{
    const std::string& attribut = mesure.getIdAttribut(); // Récupère le nom de l'attribut (polluant) de la mesure (ex: "O3", "SO2", etc.)
    double valeur = mesure.getValue(); // Récupère la valeur numérique de la mesure (ex: concentration relevée)

    //Seuils obtenus via wikipedia
    if (attribut == "O3") // Ozone µg/m3
    {
        valeur = valeur * 240/100; // Conversion de % a µg/m3
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
        valeur = valeur * 500/100; // Conversion de % a µg/m3
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
        valeur = valeur * 400/100; // Conversion de % a µg/m3
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
        valeur = valeur * 80/100; // Conversion de % a µg/m3
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

    return -1.0; // Attribut non reconnu (n'est pas censé arriver)
}

//Ajout des points pour les utilisateurs
void GestionnaireSysteme::ajouterPointUtilisateur(const string& idSensor) {
    User* user = getUserBySensorId(idSensor); // Récupère l'utilisateur associé au capteur
        if (user) { // Si l'utilisateur existe
            user->setNbPoints(user->getNbPoints() + 1); // Incrémente le nombre de points de l'utilisateur
            cout << "\nUn capteur prive a été utilisé !" << endl;
            cout<< "Capteur " << idSensor << " appartient à l'utilisateur " << user->getIdUser() << endl;
            cout << "Un point lui a été ajouté"<< endl;
        }
}

// Classement des capteurs par similarité
vector<pair<Sensor, double>> GestionnaireSysteme::classerCapteursParSimilarite(const string& idSensor, const string& dateDebut, const string& dateFin)
{
    vector<pair<Sensor, double>> resultats;
    Sensor* capteurReference = getSensorById(idSensor); // Récupère le capteur de référence par son ID

    if (!capteurReference)
        return resultats; // Capteur non trouve

    // Obtenir les mesures du capteur de reference
    list<Mesure> mesuresRef = capteurReference->getMesuresDansIntervalle(dateDebut, dateFin);
    if (mesuresRef.empty())
    {
        cout << "Aucune mesure trouvee pour le capteur de reference " << idSensor << " dans l'intervalle donne." << endl;
        return resultats; // Pas de mesures pour le capteur de reference
    }
    for (Sensor& capteur : sensors)
    {
        
        // Ajout d'un point a l'utilisateur proprietaire du capteur
        ajouterPointUtilisateur(capteur.getIdSensor());

        if (capteur.getIdSensor() == idSensor)
            continue; // Ignorer le capteur de reference
        
        list<Mesure> mesuresComparaison = capteur.getMesuresDansIntervalle(dateDebut, dateFin);
        double similarite = 0.0;
        // Calculer la similarite (somme des differences absolues des valeurs des mesure/nb de mesures)
        
        for (const Mesure& mRef : mesuresRef)
        {
            for (const Mesure& mComp : mesuresComparaison)
            {
                if (mRef.getIdAttribut() == mComp.getIdAttribut())
                {
                    similarite += fabs(mRef.getValue() - mComp.getValue()); // Difference absolue entre les valeurs des mesures
                }
            }
        }
        if (!mesuresComparaison.empty())                
            similarite /= mesuresComparaison.size(); // Moyenne des differences absolues

        resultats.emplace_back(capteur, similarite); // Ajoute le capteur et sa similarite dans le vecteur de resultats
    }

    // Trier par similarite decroissante
    sort(resultats.begin(), resultats.end(),
         [](const pair<Sensor, double>& a, const pair<Sensor, double>& b) {
             return a.second > b.second;
         });

    return resultats;
}




#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846 
#endif
// Fonction pour calculer la distance entre deux points géographiques en utilisant la formule de Haversine
static double haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0; // Rayon moyen de la Terre en km
    double dLat = (lat2 - lat1) * M_PI / 180.0; // Conversion des degrés en radians
    double dLon = (lon2 - lon1) * M_PI / 180.0; 
    double a = sin(dLat/2) * sin(dLat/2) + 
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLon/2) * sin(dLon/2); 
    double c = 2 * atan2(sqrt(a), sqrt(1-a)); // Calcul de l'angle central
    return R * c; // Distance en km
}

// Fonction pour consulter la moyenne de la qualité de l'air (AQI) dans une zone donnée
double GestionnaireSysteme::consulterMoyenneQualite(double longitude, double latitude, double rayon, const string& dateDebut, const string& dateFin)
{
    double sommeAQI = 0.0; 
    int compteur = 0; // Compteur de mesures AQI valides

    for (Sensor& capteur : sensors)
    {
        double distance = haversine(latitude, longitude, capteur.getLatitude(), capteur.getLongitude());

        if (distance <= rayon) // Si le capteur est dans le rayon spécifié
        {
            // Ajout d'un point a l'utilisateur proprietaire du capteur
            ajouterPointUtilisateur(capteur.getIdSensor());
            // Recuperation des mesures dans l'intervalle de dates
            list<Mesure> mesures = capteur.getMesuresDansIntervalle(dateDebut, dateFin);
            for (const Mesure& mesure : mesures)
            {
                double aqi = convertirEnAQI(mesure); // Conversion de la mesure en AQI
                if (aqi >= 0) // Si la conversion a réussi (AQI valide et attribut reconnu)
                {
                    sommeAQI += aqi; // Ajout de l'AQI à la somme totale
                    compteur++; // Incrémentation du compteur de mesures AQI valides
                }
            }
        }
    }

    if (compteur == 0) // Si aucun AQI valide n'a été trouvé
        return -1.0; // Indique qu'aucune mesure AQI n'a été trouvée dans la zone

    return sommeAQI / compteur; // Retourne la moyenne des AQI
}

 // Fonction pour charger les données des capteurs, mesures et utilisateurs à partir des fichiers CSV
void GestionnaireSysteme::loadData() {
    // Charger les donnees des capteurs et des mesures a partir des csv dans le dossier data
    ifstream attrFile("data/attributes.csv");
    string line;
    getline(attrFile, line); // Ignorer la ligne header (c'est le seul fichier qui en a un)
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
        auto it = find_if(sensors.begin(), sensors.end(), // Utilisation de find_if pour trouver le capteur par son ID
            [&](const Sensor& s) { return s.getIdSensor() == sensorId; }); 
        if (it != sensors.end()) { // Si le capteur a été trouvé
            it->addMesure(Mesure(date, attrId, value)); // Ajout de la mesure au capteur
        }
    }
    measFile.close();

    // Charger les utilisateurs avec leurs capteurs
    ifstream usersFile("data/users.csv");
    while (getline(usersFile, line)) {
        stringstream ss(line);
        string idUser, idSensor;
        getline(ss, idUser, ';');
        getline(ss, idSensor, ';');
        if (!idUser.empty() && !idSensor.empty()) {
            // Retire les espaces ou retours a la ligne en fin de champ
            idSensor.erase(remove_if(idSensor.begin(), idSensor.end(), ::isspace), idSensor.end()); 
            users.emplace_back(idUser, idSensor); // Ajout de l'utilisateur avec son capteur
        }
    }
    usersFile.close();    
}

