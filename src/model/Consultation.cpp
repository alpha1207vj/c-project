#include "model/Consultation.h"

// =========================
//  CONSTRUCTEUR
// =========================
Consultation::Consultation(int id,
                           const std::chrono::system_clock::time_point& date,
                           Patient* patient,
                           ProfessionnelSante* professionnel,
                           const std::string& motif,
                           const std::string& observations,
                           DossierMedical* dossier)
    : id(id), date(date), patient(patient), professionnel(professionnel),
      motif(motif), observations(observations), dossier(dossier) {}

// =========================
//  GETTERS / SETTERS
// =========================

// --- ID ---
int Consultation::getId() const { return id; }

// --- Date ---
std::chrono::system_clock::time_point Consultation::getDate() const { return date; }
void Consultation::setDate(const std::chrono::system_clock::time_point& d) { date = d; }

// --- Patient ---
Patient* Consultation::getPatient() const { return patient; }

// --- Professional ---
ProfessionnelSante* Consultation::getProfessionnel() const { return professionnel; }

// --- Motif ---
std::string Consultation::getMotif() const { return motif; }
void Consultation::setMotif(const std::string& m) { motif = m; }

// --- Observations ---
std::string Consultation::getObservations() const { return observations; }
void Consultation::setObservations(const std::string& o) { observations = o; }

// --- Dossier associé ---
DossierMedical* Consultation::getDossier() const { return dossier; }
