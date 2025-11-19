// src/model/Consultation.cpp
#include "model/Consultation.h"

Consultation::Consultation(int id,
                           const std::chrono::system_clock::time_point& date,
                           Patient* patient,
                           ProfessionnelSante* professionnel,
                           const std::string& motif,
                           const std::string& observations,
                           DossierMedical* dossier)
    : id(id), date(date), patient(patient), professionnel(professionnel), motif(motif), observations(observations), dossier(dossier) {}

// Getters/Setters
int Consultation::getId() const { return id; }
std::chrono::system_clock::time_point Consultation::getDate() const { return date; }
void Consultation::setDate(const std::chrono::system_clock::time_point& d) { date = d; }

Patient* Consultation::getPatient() const { return patient; }
ProfessionnelSante* Consultation::getProfessionnel() const { return professionnel; }

std::string Consultation::getMotif() const { return motif; }
void Consultation::setMotif(const std::string& m) { motif = m; }

std::string Consultation::getObservations() const { return observations; }
void Consultation::setObservations(const std::string& o) { observations = o; }

DossierMedical* Consultation::getDossier() const { return dossier; }
