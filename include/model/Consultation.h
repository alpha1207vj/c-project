#ifndef CONSULTATION_H
#define CONSULTATION_H

#include <string>
#include <chrono>

// Déclarations anticipées pour éviter les inclusions circulaires
class Patient;
class ProfessionnelSante;
class DossierMedical;

// ---------------------------
// Classe : Consultation
// Représente une consultation médicale d’un patient par un professionnel de santé.
// Contient le motif, les observations et un lien vers le dossier médical.
// ---------------------------
class Consultation {
private:
    int id;   // Identifiant unique de la consultation

    std::chrono::system_clock::time_point date;
    // Date et heure de la consultation (std::chrono pour précision)

    Patient* patient;                    // Pointeur vers le patient concerné
    ProfessionnelSante* professionnel;   // Pointeur vers le professionnel qui a fait la consultation
    std::string motif;                   // Motif ou raison de la consultation
    std::string observations;            // Observations ou notes du professionnel
    DossierMedical* dossier;             // Dossier médical associé à cette consultation

public:
    // ---------------------------
    // Constructeur
    // Initialise tous les champs nécessaires pour une consultation
    // ---------------------------
    Consultation(int id,
                 const std::chrono::system_clock::time_point& date,
                 Patient* patient,
                 ProfessionnelSante* professionnel,
                 const std::string& motif,
                 const std::string& observations,
                 DossierMedical* dossier);

    // ----- Getters / Setters -----

    // Retourne l'identifiant unique de la consultation
    int getId() const;

    // Retourne la date et heure de la consultation
    std::chrono::system_clock::time_point getDate() const;

    // Modifie la date et heure de la consultation
    void setDate(const std::chrono::system_clock::time_point& d);

    // Retourne le patient associé à cette consultation
    Patient* getPatient() const;

    // Retourne le professionnel de santé associé
    ProfessionnelSante* getProfessionnel() const;

    // Retourne le motif de la consultation
    std::string getMotif() const;

    // Modifie le motif
    void setMotif(const std::string& m);

    // Retourne les observations
    std::string getObservations() const;

    // Modifie les observations
    void setObservations(const std::string& o);

    // Retourne le dossier médical lié à cette consultation
    DossierMedical* getDossier() const;
};

#endif
