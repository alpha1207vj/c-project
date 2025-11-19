#ifndef SERVICE_CONSULTATION_H
#define SERVICE_CONSULTATION_H

#include <vector>
#include <string>
#include "model/Consultation.h"
#include "model/Patient.h"
#include "model/ProfessionnelSante.h"

class ServiceConsultation {
private:
    std::vector<Consultation*> consultations;

public:
    bool programmerConsultation(Consultation* c);
    void modifierConsultation(int id, const std::string& motif, const std::string& observations);
    void annulerConsultation(int id);
    std::vector<Consultation*> listerConsultationsParPatient(Patient* p) const;
    std::vector<Consultation*> listerConsultationsParProfessionnel(ProfessionnelSante* prof) const;
};

#endif
