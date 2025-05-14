#include "Mesure.h"

Mesure::Mesure(const string& t, string idAttr, int val)
    : timestamp(t), idAttribut(idAttr), value(val) {}

string Mesure::getTimestamp() const { return timestamp; }
string Mesure::getIdAttribut() const { return idAttribut; }
int Mesure::getValue() const { return value; }

void Mesure::setTimestamp(const string& t) { timestamp = t; }
void Mesure::setIdAttribut(string id) { idAttribut = id; }
void Mesure::setValue(int val) { value = val; }
