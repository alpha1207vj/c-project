#include "service/ServiceStatistiques.h"
#include <algorithm>
#include <iostream>
#include <cctype> // pour ::tolower

// =========================
//  CONSTRUCTEUR
// =========================
// Initialise le service de statistiques avec les services existants
ServiceStatistiques::ServiceStatistiques(ServicePatient* sp, ServiceConsultation* sc, ServiceUtilisateur* su)
    : servicePatient(sp), serviceConsultation(sc), serviceUtilisateur(su) {}

// =========================
//  COMPTER CONSULTATIONS
// =========================
// Compte toutes les consultations existantes
int ServiceStatistiques::compterConsultations() const {
    if (!serviceConsultation) return 0;

    int total = 0;
    for (Patient* p : servicePatient->getPatients()) {
        total += serviceConsultation->listerConsultationsParPatient(p).size();
    }
    return total;
}

// =========================
//  COMPTER PATIENTS
// =========================
// Compte tous les patients
int ServiceStatistiques::compterPatients() const {
    return servicePatient ? servicePatient->getPatients().size() : 0;
}

// =========================
//  COMPTER PROFESSIONNELS PAR ROLE
// =========================
int ServiceStatistiques::compterProfessionnelsParRole(Role role) const {
    int count = 0;
    if (serviceUtilisateur) {
        for (auto u : serviceUtilisateur->getUtilisateurs()) {
            if (u->getRole() == role) count++;
        }
    }
    return count;
}

// =========================
//  COMPTER PROFESSIONNELS PAR SPECIALITE
// =========================
int ServiceStatistiques::compterProfessionnelsParSpecialite(const std::string& specialite) const {
    if (!serviceUtilisateur) return 0;

    // Transforme la spécialité cible en minuscules pour comparaison
    std::string target = specialite;
    std::transform(target.begin(), target.end(), target.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    int count = 0;

    for (auto u : serviceUtilisateur->getUtilisateurs()) {
        if (u->getRole() == Role::PROFESSIONNEL_SANTE) {
            auto ps = dynamic_cast<ProfessionnelSante*>(u);
            if (ps) {
                // Transforme la spécialité de l'utilisateur en minuscules
                std::string sp = ps->getSpecialite();
                std::transform(sp.begin(), sp.end(), sp.begin(),
                               [](unsigned char c){ return std::tolower(c); });

                if (sp == target) count++;
            }
        }
    }

    return count;
}

// =========================
//  AFFICHER STATISTIQUES COMPLETES
// =========================
void ServiceStatistiques::afficherStatistiquesCompletes() const {
    std::cout << "=== STATISTICS ===\n";

    std::cout << "Patients: " << compterPatients() << "\n";
    std::cout << "Consultations: " << compterConsultations() << "\n\n";

    std::cout << "Professionals:\n";

    // Liste prédéfinie des spécialités
    const std::vector<std::string> specialites = {
        "GENERALIST",
        "NURSE",
        "INFIRMIER",
        "GYNECOLOGIST",
        "OPHTALMOLOGIST"
    };

    for (const auto& sp : specialites) {
        // Compte les professionnels par spécialité
        std::string spLower = sp;
        std::transform(spLower.begin(), spLower.end(), spLower.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        std::cout << "  " << sp << ": " << compterProfessionnelsParSpecialite(spLower) << "\n";
    }
}
