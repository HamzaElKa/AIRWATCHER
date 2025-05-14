#include "Mesure.h"

Mesure::Mesure(const string& t, int idAttr, int val)
    : timestamp(t), idAttribut(idAttr), value(val) {}

string Mesure::getTimestamp() const { return timestamp; }
int Mesure::getIdAttribut() const { return idAttribut; }
int Mesure::getValue() const { return value; }

void Mesure::setTimestamp(const string& t) { timestamp = t; }
void Mesure::setIdAttribut(int id) { idAttribut = id; }
void Mesure::setValue(int val) { value = val; }
