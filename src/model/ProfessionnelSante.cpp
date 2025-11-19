// src/model/ProfessionnelSante.cpp
#include "model/ProfessionnelSante.h"
#include "model/Consultation.h"

ProfessionnelSante::ProfessionnelSante(int id, const std::string& nomUtilisateur, const std::string& motDePasse, const std::string& specialite)
    : Utilisateur(id, nomUtilisateur, motDePasse, Role::PROFESSIONNEL_SANTE), specialite(specialite) {}

std::string ProfessionnelSante::getSpecialite() const { return specialite; }
void ProfessionnelSante::setSpecialite(const std::string& s) { specialite = s; }

void ProfessionnelSante::ajouterDisponibilite(const std::chrono::system_clock::time_point& date) {
    disponibilites.push_back(date);
}

bool ProfessionnelSante::estDisponible(const std::chrono::system_clock::time_point& date) const {
    for (const auto& d : disponibilites) {
        if (d == date) return true;
    }
    return false;
}

void ProfessionnelSante::ajouterConsultation(Consultation* c) { consultations.push_back(c); }

const std::vector<Consultation*>& ProfessionnelSante::getConsultations() const { return consultations; }
