#include "Attribut.h"

Attribut::Attribut(int id, const string& u, const string& d)
    : idAttribut(id), unit(u), description(d) {}

int Attribut::getIdAttribut() const { return idAttribut; }
string Attribut::getUnit() const { return unit; }
string Attribut::getDescription() const { return description; }

void Attribut::setIdAttribut(int id) { idAttribut = id; }
void Attribut::setUnit(const string& u) { unit = u; }
void Attribut::setDescription(const string& d) { description = d; }
