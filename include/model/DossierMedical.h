#ifndef DOSSIERMEDICAL_H
#define DOSSIERMEDICAL_H

#include <vector>
#include "Patient.h"
#include "Antecedent.h"
#include "Consultation.h"

// =========================
// CLASSE DOSSIERMEDICAL
// =========================
// Représente le dossier médical d'un patient.
// Contient :
// - Le patient associé
// - Ses antécédents médicaux
// - Ses consultations
class DossierMedical {
private:
    // =========================
    // ATTRIBUTS
    // =========================
    Patient* patient;                          // Pointeur vers le patient
    std::vector<Antecedent*> antecedents;     // Liste des antécédents
    std::vector<Consultation*> consultations; // Liste des consultations

public:
    // =========================
    // CONSTRUCTEUR
    // =========================
    explicit DossierMedical(Patient* patient);

    // =========================
    // AJOUT DE DONNÉES
    // =========================
    void ajouterAntecedent(Antecedent* a);       // Ajouter un antécédent
    void ajouterConsultation(Consultation* c);  // Ajouter une consultation

    // =========================
    // AFFICHAGE
    // =========================
    void afficherDossier() const;                // Affiche le patient, antécédents et consultations

    // =========================
    // ACCESSEURS
    // =========================
    Patient* getPatient() const;                         // Retourne le patient
    const std::vector<Antecedent*>& getAntecedents() const;      // Retourne les antécédents (lecture seule)
    const std::vector<Consultation*>& getConsultations() const;  // Retourne les consultations (lecture seule)
    std::vector<Consultation*>& getConsultations();              // Retourne les consultations (modifiable)
};

#endif
