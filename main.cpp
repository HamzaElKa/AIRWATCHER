#include <iostream>
#include "GestionnaireSysteme.h"
using namespace std;

int main() {
    GestionnaireSysteme gs;
    gs.loadData();  
    // Chargement des capteurs, mesures et attributs depuis les fichiers CSV testé et réussi

    





    //SCEnARIO 1 ajouté par Hamza
    /*cout << "\n--- SCENARIO 1 ---" << endl;    
    cout << "Attributs charges : " << gs.getAttributes().size() << endl;

    cout << "Capteurs charges : " << gs.getSensors().size() << endl;

    if (!gs.getSensors().empty()) {
        const Sensor& firstSensor = gs.getSensors().front();
        cout << "Premier capteur : " << firstSensor.getIdSensor() << endl;
        cout << "\n--- Informations sur le premier capteur ---" << endl;
        cout << "ID Capteur : " << firstSensor.getIdSensor() << endl;
        cout << "Nombre de mesures : " << firstSensor.getMesures().size() << endl;

        int count = 0;
        for (const Mesure& m : firstSensor.getMesures()) {
            cout << "Mesure : " << m.getTimestamp() << ", "
                 << m.getIdAttribut() << ", "
                 << m.getValue() << endl;
            if (++count >= 3) break;
        }
    }*/

    double longitude = 4.85;
    double latitude = 45.75;
    double rayon = 10.0;
    string dateDebut = "2019-01-01 00:00:00";
    string dateFin = "2019-01-03 00:00:00";
    cout <<"\n --- On lance la consultation de la moyenne AQI ---" << endl;
    double moyenneAQI = gs.consulterMoyenneQualite(longitude, latitude, rayon, dateDebut, dateFin);

    cout << "\n--- Resultat scenario 1 : Moyenne AQI ---" << endl;
    if (moyenneAQI < 0)
        cout << "Aucune donnée AQI disponible pour la zone et periode donnees." << endl;
    else
        cout << "Moyenne AQI sur la zone (" << latitude << ", " << longitude
             << "), rayon " << rayon << " km entre " << dateDebut
             << " et " << dateFin << " : " << moyenneAQI << endl;

    return 0;
}
