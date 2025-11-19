#ifndef SERVICE_STATISTIQUES_H
#define SERVICE_STATISTIQUES_H

#include "ServicePatient.h"
#include "ServiceConsultation.h"
#include "ServiceUtilisateur.h"

class ServiceStatistiques {
private:
    ServicePatient* servicePatient;
    ServiceConsultation* serviceConsultation;
    ServiceUtilisateur* serviceUtilisateur;

public:
    ServiceStatistiques(ServicePatient* sp, ServiceConsultation* sc, ServiceUtilisateur* su);

    int compterPatients() const;
    int compterConsultations() const;
    int compterProfessionnelsParRole(Role role) const;
};

#endif
