#include <iostream>
#include "GestionnaireSysteme.h"
using namespace std;


int main() {
    GestionnaireSysteme gs;
    gs.loadData();

    // Afficher le nombre d'attributs chargés
    cout << "Attributs chargés : " << gs.getAttributes().size() << endl;

    // Afficher le nombre de capteurs chargés
    cout << "Capteurs chargés : " << gs.getSensors().size() << endl;

    // Afficher les mesures du premier capteur (si existant)
    if (!gs.getSensors().empty()) {
        const auto& firstSensor = gs.getSensors().front();
        cout << "Capteur : " << firstSensor.getIdSensor() << endl;
        cout << "Nombre de mesures : " << firstSensor.getMesures().size() << endl;
        // Afficher les 3 premières mesures
        int count = 0;
        for (const auto& m : firstSensor.getMesures()) {
            cout << "Mesure: " << m.getTimestamp() << ", " << m.getIdAttribut() << ", " << m.getValue() << endl;
            if (++count >= 3) break;
        }
    }



    return 0;
}