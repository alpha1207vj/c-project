#include "service/ServiceStatistiques.h"
#include <algorithm>
#include <iostream>

ServiceStatistiques::ServiceStatistiques(ServicePatient* sp, ServiceConsultation* sc, ServiceUtilisateur* su)
    : servicePatient(sp), serviceConsultation(sc), serviceUtilisateur(su) {}

// Count all consultations in the service
int ServiceStatistiques::compterConsultations() const {
    if (!serviceConsultation) return 0;

    int total = 0;
    for (Patient* p : servicePatient->getPatients()) {
        total += serviceConsultation->listerConsultationsParPatient(p).size();
    }
    return total;
}

// Count all patients
int ServiceStatistiques::compterPatients() const {
    return servicePatient ? servicePatient->getPatients().size() : 0;
}

// Count all professionals by role
int ServiceStatistiques::compterProfessionnelsParRole(Role role) const {
    int count = 0;
    if (serviceUtilisateur) {
        // This must be inside the function!
        for (auto u : serviceUtilisateur->getUtilisateurs()) {
            if (u->getRole() == role) count++;
        }
    }
    return count;
}
#include <algorithm> // for std::transform
#include <cctype>    // for ::tolower

int ServiceStatistiques::compterProfessionnelsParSpecialite(const std::string& specialite) const {
    if (!serviceUtilisateur) return 0;

    std::string target = specialite;
    std::transform(target.begin(), target.end(), target.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    int count = 0;

    for (auto u : serviceUtilisateur->getUtilisateurs()) {
        if (u->getRole() == Role::PROFESSIONNEL_SANTE) {
            auto ps = dynamic_cast<ProfessionnelSante*>(u);
            if (ps) {
                std::string sp = ps->getSpecialite();
                std::transform(sp.begin(), sp.end(), sp.begin(),
                               [](unsigned char c){ return std::tolower(c); });

                if (sp == target) count++;
            }
        }
    }

    return count;
}

void ServiceStatistiques::afficherStatistiquesCompletes() const {
    std::cout << "=== STATISTICS ===\n";

    std::cout << "Patients: " << compterPatients() << "\n";
    std::cout << "Consultations: " << compterConsultations() << "\n\n";

    std::cout << "Professionals:\n";

    const std::vector<std::string> specialites = {
        "GENERALIST",
        "NURSE",
        "INFIRMIER",
        "GYNECOLOGIST",
        "OPHTALMOLOGIST"
    };

    for (const auto& sp : specialites) {
        // Use lowercase version of sp for counting inside the function
        std::string spLower = sp;
        std::transform(spLower.begin(), spLower.end(), spLower.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        std::cout << "  " << sp << ": " << compterProfessionnelsParSpecialite(spLower) << "\n";
    }
}
