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
    
        // Déclarations des variables utilisées
    string dateDebut, dateFin;
    double longitude = -0.3 , latitude = 44.0, rayon = 10;
    string idSensor;
    vector<pair<Sensor, double>> classement;
    const vector<User>& users = gs.getUsers();

     
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
                         << ", Capteur : " << user.getIdSensor() <<", Points : " << user.getNbPoints()  << endl;
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
