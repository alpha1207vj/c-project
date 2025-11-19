#include "service/ServiceStatistiques.h"

ServiceStatistiques::ServiceStatistiques(ServicePatient* sp, ServiceConsultation* sc, ServiceUtilisateur* su)
    : servicePatient(sp), serviceConsultation(sc), serviceUtilisateur(su) {}

// Count all consultations in the service
int ServiceStatistiques::compterConsultations() const {
    return serviceConsultation ? serviceConsultation->listerConsultationsParPatient(nullptr).size() : 0;
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
