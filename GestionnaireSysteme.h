#ifndef GESTIONNAIRESYSTEME_H
#define GESTIONNAIRESYSTEME_H

#include <iostream>
#include <ctime>
#include <vector>


#include "Sensor.h"
#include "Mesure.h"
#include "Attribut.h"

using namespace std;
class GestionnaireSysteme {
    public:
        GestionnaireSysteme();
        ~GestionnaireSysteme();

        void loadData();
        //Calcul moyenne AQI sur une zone et période donnée
        
        
        //Scénario 1 Calcul de la moyenne AQI sur une zone et période donnée
        double consulterMoyenneQualite(double lon, double lat, double rayon,
                               const string& dateDebut, const string& dateFin);

        double convertirEnAQI(const Mesure& mesure);

        //Scénario 2 Classement des capteurs par similarité, renvoie une liste tuple de capteurs triée selon un pourcentage de similarité et leur dit-pourcentage
        vector<pair<Sensor, double>> classerCapteursParSimilarite(const string& idSensor, const string& dateDebut, const string& dateFin);
        //getters
        vector<Attribut> getAttributes();
        vector<Sensor> getSensors();
        Sensor* getSensorById(const string& id); 

    protected:
        //sensors
        vector<Sensor> sensors;
        //attributs
        vector<Attribut> attributs;

        
    };


#endif // GESTIONNAIRESYSTEME_H