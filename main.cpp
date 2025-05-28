#include <iostream>
#include "GestionnaireSysteme.h"
using namespace std;

int main() {
    GestionnaireSysteme gs;
    gs.loadData();  
    // Chargement des capteurs, mesures et attributs depuis les fichiers CSV testé et réussi

    





    //SCEnARIO 1 ajouté par Hamza corrigé par Yanis et Pilou
    cout << "\n On TEST LE SCENARIO 1 : Moyenne AQI sur une zone et période donnee" << endl;
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




    // SCENARIO 2 par Yanis et Pilou
    cout << "\n On TEST LE SCENARIO 2 : Classement des capteurs par similarite" << endl;
    string idSensor = "Sensor1"; // Remplacez par un ID de capteur valide
    //j'utilise les dates de début et de fin du scénario 1
    
    cout << "\n--- On lance le classement des capteurs par similarite ---" << endl;
    vector<pair<Sensor, double>> classement = gs.classerCapteursParSimilarite(idSensor, dateDebut, dateFin);

    cout << "\n--- Resultat scenario 2 : Classement des capteurs par similarite ---" << endl;
    if (classement.empty()) {
        cout << "Aucun capteur trouvé pour l'ID donné ou aucune mesure disponible." << endl;
    } else {
        cout << "Classement des capteurs par similarite pour le capteur " << idSensor << " :" << endl;
        for (const auto& pair : classement) {
            const Sensor& sensor = pair.first;
            double similarite = pair.second;
            cout << "Capteur ID: " << sensor.getIdSensor() 
                 << ", Similarite: " << similarite << "%" << endl;
        }


        
    }

    




    return 0;
}
