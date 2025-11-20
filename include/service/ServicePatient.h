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
    int nextId = 1; // initialize first patient ID

public:
    // Getter for statistics and logic
    const std::vector<Patient*>& getPatients() const { return patients; }

    // CRUD operations
    void creerPatient(Patient* p);
    void supprimerPatient(int id);
    void mettreAJourPatient(Patient* p);
    Patient* trouverPatientParId(int id);
    void listerPatients() const;
      int creerPatient(const std::string& name,
                     const std::chrono::system_clock::time_point& dob,
                     const std::string& address,
                     const std::string& phone);
};

#endif
