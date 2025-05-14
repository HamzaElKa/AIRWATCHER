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
        //CalculMoyenneAQI(float lat, float lon, float ray, time_t start, time_t end);
        vector<Attribut> getAttributes();
        vector<Sensor> getSensors();


    protected:
        //sensors
        vector<Sensor> sensors;
        //attributs
        vector<Attribut> attributs;

        
    };


#endif // GESTIONNAIRESYSTEME_H