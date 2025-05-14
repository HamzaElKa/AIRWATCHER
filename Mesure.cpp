#include "Mesure.h"

// Constructeurs
Mesure::Mesure() : timestamp(""), idAttribut(""), value(0) {}

Mesure::Mesure(const string& t, string idAttr, int val)
    : timestamp(t), idAttribut(idAttr), value(val) {}

// Getters
string Mesure::getTimestamp() const {
    return timestamp;
}

string Mesure::getIdAttribut() const {
    return idAttribut;
}

int Mesure::getValue() const {
    return value;
}

// Setters
void Mesure::setTimestamp(const string& t) {
    timestamp = t;
}

void Mesure::setIdAttribut(string id) {
    idAttribut = id;
}

void Mesure::setValue(int val) {
    value = val;
}