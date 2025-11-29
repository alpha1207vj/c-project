// =========================
//  FICHIER : ProfessionnelSante.cpp
//  Implémentation de la classe ProfessionnelSante
//  Représente un professionnel de santé avec spécialité, disponibilités et consultations
// =========================

#include "model/ProfessionnelSante.h"
#include "model/Consultation.h"

// =========================
//  CONSTRUCTEUR
// =========================
// Initialise un professionnel avec ID, nom, mot de passe et spécialité
ProfessionnelSante::ProfessionnelSante(int id, const std::string& nomUtilisateur,
                                       const std::string& motDePasse,
                                       const std::string& specialite)
    : Utilisateur(id, nomUtilisateur, motDePasse, Role::PROFESSIONNEL_SANTE),
      specialite(specialite) {}

// =========================
//  GETTER / SETTER SPECIALITÉ
// =========================
std::string ProfessionnelSante::getSpecialite() const {
    return specialite; // Retourne la spécialité du professionnel
}

void ProfessionnelSante::setSpecialite(const std::string& s) {
    specialite = s;    // Modifie la spécialité
}

// =========================
//  GESTION DES DISPONIBILITÉS
// =========================
void ProfessionnelSante::ajouterDisponibilite(const std::chrono::system_clock::time_point& date) {
    disponibilites.push_back(date); // Ajoute une nouvelle disponibilité
}

bool ProfessionnelSante::estDisponible(const std::chrono::system_clock::time_point& date) const {
    for (const auto& d : disponibilites) {
        if (d == date) return true; // Vérifie si la date est disponible
    }
    return false;
}

// =========================
//  GESTION DES CONSULTATIONS
// =========================
void ProfessionnelSante::ajouterConsultation(Consultation* c) {
    consultations.push_back(c); // Ajoute une consultation à la liste
}

const std::vector<Consultation*>& ProfessionnelSante::getConsultations() const {
    return consultations;       // Retourne toutes les consultations
}
