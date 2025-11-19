#ifndef DOSSIERMEDICAL_H
#define DOSSIERMEDICAL_H

#include <vector>
#include "Patient.h"
#include "Antecedent.h"
#include "Consultation.h"

class DossierMedical {
private:
    Patient* patient;  // The patient
    std::vector<Antecedent*> antecedents;
    std::vector<Consultation*> consultations;

public:
    DossierMedical(Patient* patient);

    void ajouterAntecedent(Antecedent* a);
    void ajouterConsultation(Consultation* c);

    // Full display including patient info
    void afficherDossier() const;

    // Accessors
    Patient* getPatient() const;
    const std::vector<Antecedent*>& getAntecedents() const;
   const std::vector<Consultation*>& getConsultations() const { return consultations; }
std::vector<Consultation*>& getConsultations() { return consultations; }


};

#endif
