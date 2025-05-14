#include "Attribut.h"

Attribut::Attribut(string id, const string& u, const string& d)
    : idAttribut(id), unit(u), description(d) {}

string Attribut::getIdAttribut() const { return idAttribut; }
string Attribut::getUnit() const { return unit; }
string Attribut::getDescription() const { return description; }

void Attribut::setIdAttribut(string id) { idAttribut = id; }
void Attribut::setUnit(const string& u) { unit = u; }
void Attribut::setDescription(const string& d) { description = d; }
