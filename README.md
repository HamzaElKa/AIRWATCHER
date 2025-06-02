# AIRWATCHER

## Table des matières
- [À propos](#à-propos)
- [Fonctionnalités](#fonctionnalités)
- [Installation](#installation)
- [Configuration requise](#configuration-requise)
- [Ce que vous devriez savoir](#ce-que-vous-devriez-savoir)
- [Utilisation](#utilisation)
- [Tests](#tests)
- [Contributeurs](#contributeurs)

## À propos
AIRWATCHER est une application C++ permettant de gérer et d’analyser des données de capteurs de qualité de l’air (AQI). Elle permet notamment de consulter les moyennes AQI sur une zone donnée, de classer les capteurs par similarité et de visualiser les utilisateurs associés à des capteurs.

## Fonctionnalités
- Chargement automatique des données depuis fichiers.
- Consultation de la moyenne AQI sur une zone géographique et une période donnée.
- Classement des capteurs les plus similaires à un capteur donné.
- Affichage des utilisateurs et de leurs capteurs.
- Interface utilisateur interactive.
- Tests unitaires automatisés avec vérification de performance.

## Installation
Vous pouvez obtenir ce projet de deux manières :

### Clonage avec Git
```sh
git clone https://github.com/HamzaElKa/AIRWATCHER.git
cd AIRWATCHER
```

### Téléchargement en format ZIP
1. Cliquez sur le bouton "Code" sur la page GitHub du projet.
2. Sélectionnez "Download ZIP".
3. Extrayez le fichier dans un dossier de votre choix.

### Compilation
Ce projet utilise un `Makefile`. Pour compiler l’application et les tests, exécutez :
```sh
make
```

Cela génère deux exécutables :
- `airwatcher` : application interactive
- `tests` : exécutable de tests unitaires

## Configuration requise
- Système : Linux ou Windows avec terminal.
- Compilateur C++ compatible C++17 (g++ recommandé).
- Terminal/console pour exécuter les scénarios.

## Ce que vous devriez savoir
- Le programme est basé sur une architecture modulaire orientée objet.
- Tous les traitements sont centralisés dans la classe `GestionnaireSysteme`.
- L’application se lance en terminal avec menus interactifs.
- Des tests unitaires sont fournis pour vérifier le bon fonctionnement de chaque fonctionnalité.

## Utilisation

### Lancer l’application interactive
```sh
./airwatcher
```

Scénarios disponibles :
1. Moyenne AQI sur une zone et période
2. Classement des capteurs similaires
3. Liste des utilisateurs
4. Quitter

### Exemple de saisie
```
5.3 46.6 30.0 2019-01-01 00:00:00 2019-01-03 00:00:00
```

## Tests

Les tests sont situés dans `main_tests.cpp` et couvrent :
- Distance entre capteurs
- Nombre de mesures
- Moyenne AQI
- Classement de capteurs
- Chargement des utilisateurs

### Exécution des tests
```sh
./tests
```

Chaque test affiche :
- ✅ ou ❌ selon le résultat
- Résultat attendu et obtenu
- Temps d’exécution

## Contributeurs
- B3120 : EL KARCHOUNI & PAGET  
- B31xx : BELLARGUI & GALLARD
