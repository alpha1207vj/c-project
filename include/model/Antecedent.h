// =========================
//  FICHIER: Antecedent.h
// =========================
#ifndef ANTECEDENT_H
#define ANTECEDENT_H

#include <string>
#include <chrono>

// =========================
//  DÉCLARATION ANTICIPÉE
// =========================
// Permet d'éviter les inclusions circulaires avec DossierMedical.
class DossierMedical;

// =========================
//  CLASSE ANTECEDENT
// =========================
// Représente un antécédent médical d’un patient.
// Cela peut être : une maladie passée, une opération, une allergie, etc.
class Antecedent {
private:
    int id;                         // Identifiant unique de l'antécédent
    std::string description;        // Description détaillée de l'événement médical
    std::chrono::system_clock::time_point date; // Date de l'antécédent
    DossierMedical* dossier;        // Pointeur vers le dossier médical associé

public:
    // =========================
    //  CONSTRUCTEUR
    // =========================
    // Initialise un antécédent avec :
    // - id : identifiant unique
    // - description : texte décrivant l'antécédent
    // - date : date de l'événement
    // - dossier : dossier médical auquel il est associé
    Antecedent(int id,
               const std::string& description,
               const std::chrono::system_clock::time_point& date,
               DossierMedical* dossier);

    // =========================
    //  GETTERS / SETTERS
    // =========================

    int getId() const;                        // Retourne l’identifiant
    std::string getDescription() const;       // Retourne la description
    void setDescription(const std::string& desc); // Modifie la description
    std::chrono::system_clock::time_point getDate() const; // Retourne la date
    void setDate(const std::chrono::system_clock::time_point& d); // Modifie la date
    DossierMedical* getDossier() const;       // Retourne le dossier associé
};

#endif
