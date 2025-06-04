#include <iostream>
#include <chrono>
#include <functional>
#include <cmath>
#include <type_traits>
#include <string>
#include "GestionnaireSysteme.h"
#include "Sensor.h"
#include "Mesure.h"
#include "User.h"

using namespace std;

template<typename Func, typename Expected, typename... Args>
bool testFonction(const string& nomTest, Func fonction, Expected attendu, Args... args) {
    using namespace chrono;
    auto debut = high_resolution_clock::now();
    auto resultat = fonction(args...);
    auto fin = high_resolution_clock::now();

    auto duree = duration_cast<microseconds>(fin - debut).count();

    bool succes;
    if constexpr (std::is_floating_point_v<Expected>) {
        succes = std::abs(resultat - attendu) < 1e-3;
    } else if constexpr (std::is_same_v<Expected, std::string>) {
        succes = (resultat == attendu);
    } else {
        succes = static_cast<long long>(resultat) == static_cast<long long>(attendu);
    }

    cout << "=== " << nomTest << " ===" << endl;
    cout << "Résultat attendu : " << attendu << endl;
    cout << "Résultat obtenu  : " << resultat << endl;
    cout << "Durée : " << duree << " µs" << endl;
    cout << (succes ? "✅ Test réussi" : "❌ Test échoué") << "\n" << endl;

    return succes;
}

// Fonctions à tester
float calculerDistance(GestionnaireSysteme& gs, Sensor* s1, Sensor* s2) {
    return static_cast<float>(gs.haversine(
        s1->getLatitude(), s1->getLongitude(),
        s2->getLatitude(), s2->getLongitude()
    ));
}

int compterMesures(Sensor* s, const string& debut, const string& fin) {
    return static_cast<int>(s->getMesuresDansIntervalle(debut, fin).size());
}

double calculerMoyenneAQI(GestionnaireSysteme& gs, double lon, double lat, double rayon, const string& debut, const string& fin) {
    return gs.consulterMoyenneQualite(lon, lat, rayon, debut, fin);
}

int nombreCapteursSimilaires(GestionnaireSysteme& gs, const string& id, const string& debut, const string& fin) {
    return static_cast<int>(gs.classerCapteursParSimilarite(id, debut, fin).size());
}

int nombreUtilisateurs(GestionnaireSysteme& gs) {
    return static_cast<int>(gs.getUsers().size());
}

int nombreTotalCapteurs(GestionnaireSysteme& gs) {
    return static_cast<int>(gs.getSensors().size());
}

bool capteurExiste(GestionnaireSysteme& gs, const string& id) {
    return gs.getSensorById(id) != nullptr;
}

float getPremiereValeurMesure(Sensor* s, const string& debut, const string& fin) {
    auto l = s->getMesuresDansIntervalle(debut, fin);
    if (!l.empty()) return l.front().getValue();
    return -1.0f;
}

string nomPremierUtilisateur(GestionnaireSysteme& gs) {
    const auto& users = gs.getUsers();
    return users.empty() ? "" : users[0].getIdUser();
}

bool classementValide(GestionnaireSysteme& gs, const string& id, const string& debut, const string& fin) {
    auto classement = gs.classerCapteursParSimilarite(id, debut, fin);
    for (size_t i = 1; i < classement.size(); ++i)
        if (classement[i].second > classement[i - 1].second) return false;
    return true;
}

// === main ===
int main() {
    GestionnaireSysteme gs;
    gs.loadData();
    string dateDebut = "2019-01-01 00:00:00";
    string dateFin = "2019-01-02 00:00:00";
    Sensor* s0 = gs.getSensorById("Sensor0");
    Sensor* s1 = gs.getSensorById("Sensor1");
    if (s0 && s1) {
        float dist = calculerDistance(gs, s0, s1);
        testFonction("Distance Sensor0/Sensor1", calculerDistance, dist, gs,s0, s1);
        testFonction("Nb mesures Sensor0", compterMesures, compterMesures(s0, dateDebut, dateFin), s0, dateDebut, dateFin);
        testFonction("Première valeur de mesure Sensor0", getPremiereValeurMesure, getPremiereValeurMesure(s0, dateDebut, dateFin), s0, dateDebut, dateFin);
    } else {
        cout << "❌ Capteurs Sensor0 ou Sensor1 introuvables.\n" << endl;
    }

    testFonction("Capteur Sensor0 existe", capteurExiste, true, gs, "Sensor0");
    testFonction("Nombre de capteurs similaires à Sensor0", nombreCapteursSimilaires,
                 99,
                 gs, "Sensor0", dateDebut, dateFin);

    testFonction("Moyenne AQI zone", calculerMoyenneAQI,
                 gs.consulterMoyenneQualite(3.2, 45.2, 30.0, dateDebut, dateFin),
                 gs, 3.2, 45.2, 30.0, dateDebut, dateFin);

    testFonction("Nombre d'utilisateurs", nombreUtilisateurs, gs.getUsers().size(), gs);
    testFonction("Nombre total de capteurs", nombreTotalCapteurs, gs.getSensors().size(), gs);
    testFonction("Nom du premier utilisateur", nomPremierUtilisateur, nomPremierUtilisateur(gs), gs);
    testFonction("Classement des capteurs valide", classementValide, true, gs, "Sensor0", dateDebut, dateFin);
    
    
        // Déclarations des variables utilisées
    double moyenneAQI;
    double longitude = -0.3 , latitude = 44.0, rayon = 10;
    string idSensor;
    vector<pair<Sensor, double>> classement;

     
    // --- SCENARIO 1 ---
    cout << "\n On teste le scénario 1 : Moyenne AQI sur une zone et periode donnee" << endl;
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
    cout << "\n On teste le scénario 2 : Classement des capteurs par similarite" << endl;
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

    return 0;
}
