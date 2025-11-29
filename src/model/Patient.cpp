// =========================
//  FICHIER : Patient.cpp
//  Implémentation de la classe Patient
//  Représente un patient avec informations personnelles et dossier médical
// =========================

#include "model/Patient.h"

// =========================
//  CONSTRUCTEUR
// =========================
// Initialise un patient avec ID, nom, date de naissance, adresse et téléphone
Patient::Patient(int id, const std::string& nom,
                 const std::chrono::system_clock::time_point& dateNaissance,
                 const std::string& adresse, const std::string& telephone)
    : id(id), nom(nom), dateNaissance(dateNaissance),
      adresse(adresse), telephone(telephone), dossier(nullptr) {}

// =========================
//  GETTERS / SETTERS
// =========================

// ID (lecture seule)
int Patient::getId() const { return id; }

// Nom
std::string Patient::getNom() const { return nom; }
void Patient::setNom(const std::string& n) { nom = n; }

// Date de naissance
std::chrono::system_clock::time_point Patient::getDateNaissance() const { return dateNaissance; }

// Adresse
std::string Patient::getAdresse() const { return adresse; }
void Patient::setAdresse(const std::string& a) { adresse = a; }

// Téléphone
std::string Patient::getTelephone() const { return telephone; }
void Patient::setTelephone(const std::string& t) { telephone = t; }

// Dossier médical
DossierMedical* Patient::getDossier() const { return dossier; }
void Patient::setDossier(DossierMedical* d) { dossier = d; }
