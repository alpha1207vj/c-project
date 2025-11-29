#include "model/DossierMedical.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include "model/ProfessionnelSante.h"

// ---------------------------
// Constructeur
// ---------------------------
// Initialise le dossier médical avec un patient donné
DossierMedical::DossierMedical(Patient* p) : patient(p) {}

// ---------------------------
// Ajout d'antécédent
// ---------------------------
void DossierMedical::ajouterAntecedent(Antecedent* a) {
    antecedents.push_back(a);
}

// ---------------------------
// Ajout de consultation
// ---------------------------
void DossierMedical::ajouterConsultation(Consultation* c) {
    consultations.push_back(c);
}

// ---------------------------
// Convert chrono::time_point en date lisible
// ---------------------------
std::string formatDate(const std::chrono::system_clock::time_point& tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&t));
    return std::string(buf);
}

// ---------------------------
// Affichage complet du dossier
// ---------------------------
void DossierMedical::afficherDossier() const {
    if (!patient) {
        std::cout << "No patient associated with this dossier.\n";
        return;
    }

    // --- Informations patient ---
    std::cout << "\n--- Patient Info ---\n";
    std::cout << "ID: " << patient->getId() << "\n";
    std::cout << "Name: " << patient->getNom() << "\n";
    std::cout << "Date of Birth: " << formatDate(patient->getDateNaissance()) << "\n";
    std::cout << "Address: " << patient->getAdresse() << "\n";
    std::cout << "Phone: " << patient->getTelephone() << "\n";

    // --- Antécédents ---
    std::cout << "\n--- Antecedents ---\n";
    if (antecedents.empty()) {
        std::cout << "No antecedents recorded.\n";
    } else {
        for (auto a : antecedents) {
            std::cout << "ID: " << a->getId()
                      << ", Description: " << a->getDescription()
                      << ", Date: " << formatDate(a->getDate()) << "\n";
        }
    }

    // --- Consultations ---
    std::cout << "\n--- Consultations ---\n";
    if (consultations.empty()) {
        std::cout << "No consultations recorded.\n";
    } else {
        for (auto c : consultations) {
            std::cout << "ID: " << c->getId()
                      << ", Date: " << formatDate(c->getDate())
                      << ", Motif: " << c->getMotif()
                      << ", Observations: " << c->getObservations()
                      << ", Doctor: " << c->getProfessionnel()->getNomUtilisateur() << "\n";
        }
    }

    std::cout << "-----------------------\n";
}

// ---------------------------
// Accesseurs
// ---------------------------
Patient* DossierMedical::getPatient() const { return patient; }
const std::vector<Antecedent*>& DossierMedical::getAntecedents() const { return antecedents; }

// Retourne les consultations en lecture seule
const std::vector<Consultation*>& DossierMedical::getConsultations() const {
    return consultations;
}

// Retourne les consultations modifiables
std::vector<Consultation*>& DossierMedical::getConsultations() {
    return consultations;
}
