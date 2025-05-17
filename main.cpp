#include <iostream>
#include "GestionnaireSysteme.h"
using namespace std;

int main() {
    GestionnaireSysteme gs;
    gs.loadData();  

    cout << "Attributs chargés : " << gs.getAttributes().size() << endl;

    cout << "Capteurs chargés : " << gs.getSensors().size() << endl;

    if (!gs.getSensors().empty()) {
        const Sensor& firstSensor = gs.getSensors().front();
        cout << "\n--- Informations sur le premier capteur ---" << endl;
        cout << "ID Capteur : " << firstSensor.getIdSensor() << endl;
        cout << "Nombre de mesures : " << firstSensor.getMesures().size() << endl;

        int count = 0;
        for (const Mesure& m : firstSensor.getMesures()) {
            cout << "Mesure : " << m.getTimestamp() << ", "
                 << m.getIdAttribut() << ", "
                 << m.getValeur() << endl;
            if (++count >= 3) break;
        }
    }

    double longitude = 4.85;
    double latitude = 45.75;
    double rayon = 10.0;
    string dateDebut = "2019-01-01 00:00:00";
    string dateFin = "2019-01-03 00:00:00";

    double moyenneAQI = gs.consulterMoyenneQualite(longitude, latitude, rayon, dateDebut, dateFin);

    cout << "\n--- Résultat scénario 1 : Moyenne AQI ---" << endl;
    if (moyenneAQI < 0)
        cout << "Aucune donnée AQI disponible pour la zone et période données." << endl;
    else
        cout << "Moyenne AQI sur la zone (" << latitude << ", " << longitude
             << "), rayon " << rayon << " km entre " << dateDebut
             << " et " << dateFin << " : " << moyenneAQI << endl;

    return 0;
}
