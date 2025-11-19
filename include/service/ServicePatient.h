#ifndef SERVICE_PATIENT_H
#define SERVICE_PATIENT_H

#include <vector>
#include <string>
#include "model/Patient.h"
#include "model/DossierMedical.h"
#include "model/Antecedent.h"

class ServicePatient {
private:
    std::vector<Patient*> patients;

public:
    // Getter for statistics and logic
    const std::vector<Patient*>& getPatients() const { return patients; }

    // CRUD operations
    void creerPatient(Patient* p);
    void supprimerPatient(int id);
    void mettreAJourPatient(Patient* p);
    Patient* trouverPatientParId(int id);
    void listerPatients() const;
};

#endif
