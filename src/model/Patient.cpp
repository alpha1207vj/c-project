// src/model/Patient.cpp
#include "model/Patient.h"

Patient::Patient(int id, const std::string& nom, const std::chrono::system_clock::time_point& dateNaissance,
                 const std::string& adresse, const std::string& telephone)
    : id(id), nom(nom), dateNaissance(dateNaissance), adresse(adresse), telephone(telephone), dossier(nullptr) {}

// Getters/Setters
int Patient::getId() const { return id; }
std::string Patient::getNom() const { return nom; }
void Patient::setNom(const std::string& n) { nom = n; }
std::chrono::system_clock::time_point Patient::getDateNaissance() const { return dateNaissance; }
std::string Patient::getAdresse() const { return adresse; }
void Patient::setAdresse(const std::string& a) { adresse = a; }
std::string Patient::getTelephone() const { return telephone; }
void Patient::setTelephone(const std::string& t) { telephone = t; }

DossierMedical* Patient::getDossier() const { return dossier; }
void Patient::setDossier(DossierMedical* d) { dossier = d; }
