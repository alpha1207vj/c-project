#ifndef SERVICE_CONSULTATION_H
#define SERVICE_CONSULTATION_H

#include <vector>
#include <string>
#include "model/Consultation.h"
#include "model/Patient.h"
#include "model/ProfessionnelSante.h"

// =========================
//  SERVICE CONSULTATION
//  Gestion des consultations médicales
// =========================
class ServiceConsultation {
private:
    std::vector<Consultation*> consultations;  // Liste de toutes les consultations

public:
    // =========================
    //  PLANIFICATION ET MODIFICATION
    // =========================
    // Ajouter une consultation (ID unique)
    bool programmerConsultation(Consultation* c);

    // Modifier le motif et les observations d'une consultation existante
    void modifierConsultation(int id, const std::string& motif, const std::string& observations);

    // Annuler une consultation et la supprimer de la liste du patient
    void annulerConsultation(int id);

    // =========================
    //  RECHERCHE
    // =========================
    // Liste toutes les consultations d'un patient donné
    std::vector<Consultation*> listerConsultationsParPatient(Patient* p) const;

    // Liste toutes les consultations d'un professionnel de santé donné
    std::vector<Consultation*> listerConsultationsParProfessionnel(ProfessionnelSante* prof) const;
};

#endif
