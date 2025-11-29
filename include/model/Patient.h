#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <chrono>

class DossierMedical; // Déclaration anticipée pour éviter l’inclusion circulaire

// =========================
// CLASSE PATIENT
// =========================
// Représente un patient du système médical.
// Contient :
// - Informations personnelles
// - Référence vers son dossier médical
class Patient {
private:
    // =========================
    // ATTRIBUTS
    // =========================
    int id;                           // Identifiant unique
    std::string nom;                  // Nom complet
    std::chrono::system_clock::time_point dateNaissance; // Date de naissance
    std::string adresse;              // Adresse
    std::string telephone;            // Téléphone
    DossierMedical* dossier;          // Pointeur vers le dossier médical

public:
    // =========================
    // CONSTRUCTEUR
    // =========================
    Patient(int id, const std::string& nom,
            const std::chrono::system_clock::time_point& dateNaissance,
            const std::string& adresse,
            const std::string& telephone);

    // =========================
    // GETTERS / SETTERS
    // =========================
    int getId() const;                        // Retourne l’identifiant
    std::string getNom() const;               // Retourne le nom
    void setNom(const std::string& n);        // Modifie le nom
    std::chrono::system_clock::time_point getDateNaissance() const; // Date de naissance
    std::string getAdresse() const;           // Retourne l’adresse
    void setAdresse(const std::string& a);    // Modifie l’adresse
    std::string getTelephone() const;         // Retourne le téléphone
    void setTelephone(const std::string& t);  // Modifie le téléphone
    DossierMedical* getDossier() const;       // Retourne le dossier médical
    void setDossier(DossierMedical* d);       // Associe un dossier médical
};

#endif
