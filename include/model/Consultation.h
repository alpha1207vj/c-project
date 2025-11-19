// include/model/Consultation.h
#ifndef CONSULTATION_H
#define CONSULTATION_H

#include <string>
#include <chrono>

// Déclarations anticipées pour éviter les inclusions circulaires.
class Patient;
class ProfessionnelSante;
class DossierMedical;

// Classe représentant une consultation médicale.
// Elle relie un patient, un professionnel de santé, un motif,
// des observations et un lien vers le dossier médical.
class Consultation {
private:
    int id;   // Identifiant unique de la consultation
    std::chrono::system_clock::time_point date;
    // Date et heure de la consultation

    Patient* patient;                    // Patient concerné
    ProfessionnelSante* professionnel;   // Professionnel ayant réalisé la consultation
    std::string motif;                   // Raison de la consultation
    std::string observations;            // Notes et observations médicales
    DossierMedical* dossier;             // Dossier médical associé

public:
    // Constructeur initialisant tous les champs nécessaires à une consultation.
    Consultation(int id,
                 const std::chrono::system_clock::time_point& date,
                 Patient* patient,
                 ProfessionnelSante* professionnel,
                 const std::string& motif,
                 const std::string& observations,
                 DossierMedical* dossier);

    // ----- Getters / Setters -----

    // Retourne l'identifiant unique.
    int getId() const;

    // Retourne la date de la consultation.
    std::chrono::system_clock::time_point getDate() const;

    // Modifie la date.
    void setDate(const std::chrono::system_clock::time_point& d);

    // Retourne le patient associé.
    Patient* getPatient() const;

    // Retourne le professionnel associé.
    ProfessionnelSante* getProfessionnel() const;

    // Retourne le motif.
    std::string getMotif() const;

    // Modifie le motif.
    void setMotif(const std::string& m);

    // Retourne les observations.
    std::string getObservations() const;

    // Modifie les observations.
    void setObservations(const std::string& o);

    // Retourne le dossier médical lié à la consultation.
    DossierMedical* getDossier() const;
};

#endif
