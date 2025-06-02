#include <iostream>
#include <sstream>
#include <cassert>
#include <cmath>
#include "GestionnaireSysteme.h"
#include "Sensor.h"
#include "Mesure.h"
#include "User.h"
#include "PrivateUser.h"

using namespace std;

int main() {
    GestionnaireSysteme gs;
    gs.loadData();  

    cout << "=== TESTS UNITAIRES SUR LES DONNEES CHARGEES ===" << endl;

    // Test 1 : Distance entre Sensor0 et Sensor1
    Sensor* s1 = gs.getSensorById("Sensor0");
    Sensor* s2 = gs.getSensorById("Sensor1");
    if (s1 && s2) {
        float dx = s1->getLongitude() - s2->getLongitude();
        float dy = s1->getLatitude() - s2->getLatitude();
        float dist = sqrt(dx * dx + dy * dy);
        cout << "[TEST DISTANCE] Distance entre Sensor0 et Sensor1 : " << dist << endl;
    } else {
        cout << "[ERREUR] Capteurs Sensor0 ou Sensor1 non trouvés." << endl;
    }

    // Test 2 : Mesures de Sensor0 dans un intervalle
    string dateDebut = "2019-01-01 00:00:00";
    string dateFin = "2019-01-02 00:00:00";
    if (s1) {
        list<Mesure> listeMesures = s1->getMesuresDansIntervalle(dateDebut, dateFin);
        vector<Mesure> mesures(listeMesures.begin(), listeMesures.end());
        cout << "[TEST MESURES] Sensor0 entre " << dateDebut << " et " << dateFin << ": " << mesures.size() << " mesure(s)." << endl;
        for (const auto& m : mesures) {
            cout << " - Attribut: " << m.getIdAttribut() << ", Valeur: " << m.getValue() << endl;
        }
    }

    // Test 3 : Moyenne AQI sur une zone
    double longitude = 3.2;
    double latitude = 45.2;
    double rayon = 30.0;
    double moyenneAQI = gs.consulterMoyenneQualite(longitude, latitude, rayon, dateDebut, dateFin);
    if (moyenneAQI < 0)
        cout << "[TEST AQI] Aucune donnée AQI pour la zone spécifiée." << endl;
    else
        cout << "[TEST AQI] Moyenne AQI : " << moyenneAQI << endl;

    // Test 4 : Classement par similarité
    string idSensor = "Sensor0";
    vector<pair<Sensor, double>> classement = gs.classerCapteursParSimilarite(idSensor, dateDebut, dateFin);
    if (classement.empty()) {
        cout << "[TEST SIMILARITE] Aucun classement disponible." << endl;
    } else {
        cout << "[TEST SIMILARITE] Classement pour Sensor0 :" << endl;
        for (const auto& pair : classement) {
            cout << " - " << pair.first.getIdSensor() << " : " << pair.second << endl;
        }
    }

    // Test 5 : Utilisateurs et capteurs associés
    const vector<User>& users = gs.getUsers();
    if (!users.empty()) {
        cout << "[TEST UTILISATEURS] Liste des utilisateurs :" << endl;
        for (const auto& u : users) {
            cout << " - ID: " << u.getIdUser() << ", Capteur: " << u.getIdSensor() << endl;
        }
    } else {
        cout << "[TEST UTILISATEURS] Aucun utilisateur chargé." << endl;
    }

    cout << "\n=== FIN DES TESTS ===" << endl;

    // --- SCENARIO 1 ---
    cout << "\n On TEST LE SCENARIO 1 : Moyenne AQI sur une zone et periode donnee" << endl;
    dateDebut = "2019-01-01 00:00:00";
    dateFin = "2019-01-03 00:00:00";
    cout << "\n --- On lance la consultation de la moyenne AQI ---" << endl;
    moyenneAQI = gs.consulterMoyenneQualite(longitude, latitude, rayon, dateDebut, dateFin);
    cout << "\n--- Resultat scenario 1 : Moyenne AQI ---" << endl;
    if (moyenneAQI < 0)
        cout << "Aucune donnee AQI disponible pour la zone et periode donnees." << endl;
    else
        cout << "Moyenne AQI sur la zone (" << latitude << ", " << longitude
             << "), rayon " << rayon << " km entre " << dateDebut
             << " et " << dateFin << " : " << moyenneAQI << endl;

    // --- SCENARIO 2 ---
    cout << "\n On TEST LE SCENARIO 2 : Classement des capteurs par similarite" << endl;
    idSensor = "Sensor1";
    cout << "\n--- On lance le classement des capteurs par similarite ---" << endl;
    cout << "Capteur ID: " << idSensor 
         << ", Date de debut: " << dateDebut 
         << ", Date de fin: " << dateFin << endl;
    classement = gs.classerCapteursParSimilarite(idSensor, dateDebut, dateFin);
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

    // Interface utilisateur
    while (true) {
        cout << "\n<=====    Interface utilisateur     =====>" << endl;
        cout << "\nBienvenue dans le gestionnaire de capteurs AQI AIRWATCHER!" << endl;
        cout << "Deux scenarios sont disponibles:" << endl;
        cout << "1. Consulter la moyenne AQI sur une zone et periode donnee." << endl;
        cout << "2. Classer les capteurs par similarite." << endl;
        cout << "3. Voir les points des utilisateurs." << endl;
        cout << "4. Quitter le programme." << endl;
        cout << "Veuillez choisir un scenario (1, 2, 3 ou 4) : ";
        int choix;
        cin >> choix;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrée invalide. Veuillez entrer un nombre." << endl;
            continue;
        }   
        cin.ignore();

        if (choix == 1) {
            cout << "Entrez la longitude, latitude, rayon (en km), date de debut et date de fin (format YYYY-MM-DD HH:MM:SS) : ";
            cout << "\n<exemple : [5.3 46.6 30.0 2019-02-01 00:00:00 2019-03-03 00:00:00] >\n" << endl;
            string ligne;
            getline(cin, ligne);
            std::istringstream iss(ligne);
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
            std::istringstream iss(ligne);
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

            classement = gs.classerCapteursParSimilarite(idSensor, dateDebut, dateFin);
            if (classement.empty()) {
                cout << "\nAucun capteur trouve pour l'ID donne ou aucune mesure disponible." << endl;
            } else {
                cout << "\nClassement des capteurs par similarite :" << endl;
                for (const auto& pair : classement) {
                    const Sensor& sensor = pair.first;
                    double similarite = pair.second;
                    cout << "Capteur ID: " << sensor.getIdSensor() 
                         << ", Similarite: " << similarite << "%" << endl;
                }
            }
        }

        else if (choix == 3) {
            if (users.empty()) {
                cout << "\nAucun utilisateur trouve." << endl;
            } else {
                cout << "\nListe des utilisateurs et leurs points :" << endl;
                for (const User& user : users) {
                    cout << "Utilisateur ID : " << user.getIdUser()  
                         << ", Capteur : " << user.getIdSensor() << endl;
                }
            }
        }

        else if (choix == 4) {
            break; 
        } else {
            cout << "Choix invalide. Veuillez reessayer." << endl;
        }
    }

    cout << "\n--- Fin du programme ---" << endl;
    return 0;
}
