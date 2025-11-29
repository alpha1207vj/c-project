#ifndef SERVICE_PATIENT_H
#define SERVICE_PATIENT_H

#include <vector>
#include <string>
#include "model/Patient.h"
#include "model/DossierMedical.h"
#include "model/Antecedent.h"
#include "service/ServiceUtilisateur.h"
#include <chrono>

// =========================
//  SERVICE PATIENT
//  Gestion des patients : CRUD, export/import CSV, statistiques
// =========================
class ServicePatient {
private:
    std::vector<Patient*> patients;  // Liste des patients
    int nextId = 1;                  // ID auto-incrémenté pour les nouveaux patients

public:
    // =========================
    //  GETTERS
    // =========================
    // Retourne la liste complète des patients
    const std::vector<Patient*>& getPatients() const { return patients; }

    // =========================
    //  CRUD PATIENTS
    // =========================
    void creerPatient(Patient* p);   // Ajouter un patient existant
    int creerPatient(const std::string& name,
                     const std::chrono::system_clock::time_point& dob,
                     const std::string& address,
                     const std::string& phone);  // Créer un patient avec génération automatique d'ID
    void supprimerPatient(int id);   // Supprimer un patient par ID
    void mettreAJourPatient(Patient* p); // Mettre à jour un patient existant
    Patient* trouverPatientParId(int id); // Trouver un patient par ID
    void listerPatients() const;     // Afficher tous les patients

    // =========================
    //  EXPORT / IMPORT CSV
    // =========================
    bool exportToCSV(const std::string& filename) const;                          // Exporter tous les patients en CSV
    bool importFromCSV(const std::string& filename, ServiceUtilisateur& serviceUser); // Importer depuis CSV en associant les professionnels
};

#endif
