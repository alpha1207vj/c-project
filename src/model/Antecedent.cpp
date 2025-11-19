// src/model/Antecedent.cpp
#include "model/Antecedent.h"

Antecedent::Antecedent(int id, const std::string& description, const std::chrono::system_clock::time_point& date, DossierMedical* dossier)
    : id(id), description(description), date(date), dossier(dossier) {}

int Antecedent::getId() const { return id; }
std::string Antecedent::getDescription() const { return description; }
void Antecedent::setDescription(const std::string& desc) { description = desc; }
std::chrono::system_clock::time_point Antecedent::getDate() const { return date; }
void Antecedent::setDate(const std::chrono::system_clock::time_point& d) { date = d; }

DossierMedical* Antecedent::getDossier() const { return dossier; }
