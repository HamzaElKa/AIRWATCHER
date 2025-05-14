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

        void LoadData();
        //Calcul moyenne AQI sur une zone et période donnée


    protected:
        //sensors
        vector<Sensor> sensors;
        //attributs
        vector<Attribut> attributs;

        
    };