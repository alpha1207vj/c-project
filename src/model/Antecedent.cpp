#include "model/Antecedent.h"

// =========================
//  CONSTRUCTEUR
// =========================
Antecedent::Antecedent(int id,
                       const std::string& description,
                       const std::chrono::system_clock::time_point& date,
                       DossierMedical* dossier)
    : id(id), description(description), date(date), dossier(dossier) {}

// =========================
//  GETTERS / SETTERS
// =========================

// --- ID ---
int Antecedent::getId() const { return id; }

// --- Description ---
std::string Antecedent::getDescription() const { return description; }
void Antecedent::setDescription(const std::string& desc) { description = desc; }

// --- Date ---
std::chrono::system_clock::time_point Antecedent::getDate() const { return date; }
void Antecedent::setDate(const std::chrono::system_clock::time_point& d) { date = d; }

// --- Dossier associé ---
DossierMedical* Antecedent::getDossier() const { return dossier; }
