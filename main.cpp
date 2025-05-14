#include <iostream>
#include "GestionnaireSysteme.h"
using namespace std;


int main() {
    GestionnaireSysteme gs;
    gs.loadData();

    // Afficher le nombre d'attributs chargés
    cout << "Attributs chargés : " << gs.attributes.size() << endl;

    // Afficher le nombre de capteurs chargés
    cout << "Capteurs chargés : " << gs.sensors.size() << endl;

    // Afficher les mesures du premier capteur (si existant)
    if (!gs.sensors.empty()) {
        const auto& firstSensor = gs.sensors.front();
        cout << "Capteur : " << firstSensor.getIdSensor() << endl;
        cout << "Nombre de mesures : " << firstSensor.getMesures().size() << endl;
        // Afficher les 3 premières mesures
        int count = 0;
        for (const auto& m : firstSensor.getMesures()) {
            cout << "Mesure: " << m.getDate() << ", " << m.getAttributeId() << ", " << m.getValue() << endl;
            if (++count >= 3) break;
        }
    }

    return 0;
}