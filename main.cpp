#include <iostream>
#include <sstream>
#include "GestionnaireSysteme.h"
using namespace std;

int main() {
    GestionnaireSysteme gs;
    gs.loadData();  
    // Chargement des capteurs, mesures et attributs depuis les fichiers CSV teste et reussi

    



    //--- TESTS ---//

    //SCEnARIO 1 ajoute par Hamza corrige par Yanis et Pilou
    cout << "\n On TEST LE SCENARIO 1 : Moyenne AQI sur une zone et periode donnee" << endl;
    
    double longitude =5.3;
    double latitude = 46.6;
    double rayon = 30.0;
    string dateDebut = "2019-02-01 00:00:00";
    string dateFin = "2019-03-03 00:00:00";
    cout <<"\n --- On lance la consultation de la moyenne AQI ---" << endl;
    double moyenneAQI = gs.consulterMoyenneQualite(longitude, latitude, rayon, dateDebut, dateFin);

    cout << "\n--- Resultat scenario 1 : Moyenne AQI ---" << endl;
    if (moyenneAQI < 0)
        cout << "Aucune donnee AQI disponible pour la zone et periode donnees." << endl;
    else
        cout << "Moyenne AQI sur la zone (" << latitude << ", " << longitude
             << "), rayon " << rayon << " km entre " << dateDebut
             << " et " << dateFin << " : " << moyenneAQI << endl;




    // SCENARIO 2 par Yanis et Pilou
    cout << "\n On TEST LE SCENARIO 2 : Classement des capteurs par similarite" << endl;
    string idSensor = "Sensor1"; // Remplacez par un ID de capteur valide
    //j'utilise les dates de debut et de fin du scenario 1
    
    cout << "\n--- On lance le classement des capteurs par similarite ---" << endl;
    vector<pair<Sensor, double>> classement = gs.classerCapteursParSimilarite(idSensor, dateDebut, dateFin);

    cout << "\n--- Resultat scenario 2 : Classement des capteurs par similarite ---" << endl;
    if (classement.empty()) {
        cout << "Aucun capteur trouve pour l'ID donne ou aucune mesure disponible." << endl;
    } else {
        cout << "Classement des capteurs par similarite pour le capteur " << idSensor << " :" << endl;
        for (const auto& pair : classement) {
            const Sensor& sensor = pair.first;
            double similarite = pair.second;
            cout << "Capteur ID: " << sensor.getIdSensor() 
                 << ", Similarite: " << similarite << "%" << endl;
        }


        
    }
    // ---Fin des TESTS---

    //Creation de l'interface utilisateur
    while (true) {
        cout << "\n----- Interface utilisateur -----" << endl;
        cout << "Bienvenue dans le gestionnaire de capteurs AQI AIRWATCHER!" << endl;
        cout << "----- 2 scenarios sont disponibles -----" << endl;
        cout << "1. Consulter la moyenne AQI sur une zone et periode donnee." << endl;
        cout << "2. Classer les capteurs par similarite." << endl;
        cout << "3. Quitter le programme." << endl;
        cout << "Veuillez choisir un scenario (1, 2 ou 3) : ";
        int choix;
        cin >> choix;
        cin.ignore(); // Pour ignorer le retour à la ligne après l'entrée de l'utilisateur

double longitude =5.3;
    double latitude = 46.6;
    double rayon = 30.0;
    string dateDebut = "2019-02-01 00:00:00";
    string dateFin = "2019-03-03 00:00:00";

        if (choix == 1) {
            cout << "Entrez la longitude, latitude, rayon (en km), date de debut et date de fin (format YYYY-MM-DD HH:MM:SS) : ";
            cout << "\n<exemple : [5.3 46.6 30.0 2019-02-01 00:00:00 2019-03-03 00:00:00] >\n" << endl;
            string ligne;
            getline(cin, ligne);
            istringstream iss(ligne);
            iss >> longitude >> latitude >> rayon;
            iss >> ws;
            getline(iss, dateDebut, ' ');
            string heureDebut;
            iss >> heureDebut;
            dateDebut += " " + heureDebut;
            getline(iss, dateFin, ' ');
            string heureFin;
            iss >> heureFin;
            dateFin += " " + heureFin;

            double moyenne = gs.consulterMoyenneQualite(longitude, latitude, rayon, dateDebut, dateFin);
            if (moyenne < 0)
                cout << "Aucune donnee AQI disponible pour la zone et periode donnees." << endl;
            else
                cout << "Moyenne AQI : " << moyenne << endl;
        }
        
        else if (choix == 2) {
            cout << "Entrez l'ID du capteur, date de debut et date de fin (format YYYY-MM-DD HH:MM:SS) : ";
            cout << "\n<exemple : [Sensor1 2019-01-01 00:00:00 2019-01-03 00:00:00] >\n" << endl;
            string ligne;
            getline(cin, ligne);
            istringstream iss(ligne);
            iss >> idSensor;
            iss >> ws;
            getline(iss, dateDebut, ' ');
            string heureDebut;
            iss >> heureDebut;
            dateDebut += " " + heureDebut;
            getline(iss, dateFin, ' ');
            string heureFin;
            iss >> heureFin;
            dateFin += " " + heureFin;

            vector<pair<Sensor, double>> classement = gs.classerCapteursParSimilarite(idSensor, dateDebut, dateFin);
            if (classement.empty()) {
                cout << "Aucun capteur trouve pour l'ID donne ou aucune mesure disponible." << endl;
            } else {
                cout << "Classement des capteurs par similarite :" << endl;
                for (const auto& pair : classement) {
                    const Sensor& sensor = pair.first;
                    double similarite = pair.second;
                    cout << "Capteur ID: " << sensor.getIdSensor() 
                        << ", Similarite: " << similarite << "%" << endl;
                }
            }
        }

        else if (choix == 3) {
            break; // Quitter le programme
        } 
        else {
            cout << "Choix invalide. Veuillez reessayer." << endl;

        }
    }
    //liberation des ressources
    gs.~GestionnaireSysteme();
    cout << "\n--- Fin du programme ---" << endl;


    
    return 0;
}
