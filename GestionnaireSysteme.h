#ifndef GESTIONNAIRESYSTEME_H
#define GESTIONNAIRESYSTEME_H
#include <unordered_map>
#include <iostream>
#include <ctime>
#include <vector>


#include "Sensor.h"
#include "Mesure.h"
#include "Attribut.h"
#include "User.h"

using namespace std;
class GestionnaireSysteme {
    public:
        GestionnaireSysteme();
        ~GestionnaireSysteme();

        //UTILITAIRES
        //Charge les capteurs, mesures et attributs depuis les fichiers CSV
        void loadData();
        //Ajout de points pour les utilisateurs
        void ajouterPointUtilisateur(const string& idSensor);
        //Conversion des mesures en AQI
        double convertirEnAQI(const Mesure& mesure);
        
        //SCENARIO 1 Calcul de la moyenne AQI sur une zone et période donnée
        double consulterMoyenneQualite(double lon, double lat, double rayon,
                               const string& dateDebut, const string& dateFin);

        static double haversine(double lat1, double lon1, double lat2, double lon2);

        //SCENARIO 2 Classement des capteurs par similarité, renvoie une liste tuple de capteurs triée selon un pourcentage de similarité et leur dit-pourcentage
        vector<pair<Sensor, double>> classerCapteursParSimilarite(const string& idSensor, const string& dateDebut, const string& dateFin);
        
        //getters
        vector<Attribut> getAttributes();
        vector<Sensor> getSensors();
        const vector<User>& getUsers() const;
        Sensor* getSensorById(const string& id); 
        User* getUserBySensorId(const string& idSensor);

    protected:
        //sensors
        vector<Sensor> sensors;
        //attributs
        vector<Attribut> attributs;
        //users
        vector<User> users;
        


    };


#endif // GESTIONNAIRESYSTEME_H