// include/model/Patient.h
#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <chrono>

// Déclaration anticipée pour éviter une inclusion circulaire.
// Le détail de DossierMedical sera connu dans le .cpp ou ailleurs.
class DossierMedical;

// Classe représentant un patient du système.
// Contient ses informations personnelles ainsi que son dossier médical.
class Patient {
private:
    int id;   // Identifiant unique du patient
    std::string nom;   // Nom complet du patient

    // Date de naissance du patient, stockée avec std::chrono pour précision.
    std::chrono::system_clock::time_point dateNaissance;

    std::string adresse;    // Adresse du patient
    std::string telephone;  // Numéro de téléphone
    DossierMedical* dossier; // Pointeur vers le dossier médical associé

public:
    // Constructeur initialisant toutes les informations principales du patient.
    Patient(int id, const std::string& nom,
            const std::chrono::system_clock::time_point& dateNaissance,
            const std::string& adresse, const std::string& telephone);

    // ----- Getters / Setters -----

    // Retourne l'identifiant unique.
    int getId() const;

    // Retourne le nom du patient.
    std::string getNom() const;

    // Modifie le nom.
    void setNom(const std::string& n);

    // Retourne la date de naissance.
    std::chrono::system_clock::time_point getDateNaissance() const;

    // Retourne l'adresse.
    std::string getAdresse() const;

    // Modifie l'adresse.
    void setAdresse(const std::string& a);

    // Retourne le numéro de téléphone.
    std::string getTelephone() const;

    // Modifie le numéro de téléphone.
    void setTelephone(const std::string& t);

    // Retourne le dossier médical associé.
    DossierMedical* getDossier() const;

    // Associe un dossier médical au patient.
    void setDossier(DossierMedical* d);
};

#endif
