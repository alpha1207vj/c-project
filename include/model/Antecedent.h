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
// Exemple : maladie passée, opération, allergie, etc.
class Antecedent {
private:
    int id;  // Identifiant unique de l'antécédent
    std::string description;  // Description détaillée
    std::chrono::system_clock::time_point date; // Date de l'antécédent
    DossierMedical* dossier; // Pointeur vers le dossier médical associé

public:
    // =========================
    //  CONSTRUCTEUR
    // =========================
    // Initialise un antécédent avec ses informations
    Antecedent(int id,
               const std::string& description,
               const std::chrono::system_clock::time_point& date,
               DossierMedical* dossier);

    // =========================
    //  GETTERS / SETTERS
    // =========================

    // Retourne l’identifiant unique
    int getId() const;

    // Retourne la description
    std::string getDescription() const;

    // Modifie la description
    void setDescription(const std::string& desc);

    // Retourne la date
    std::chrono::system_clock::time_point getDate() const;

    // Modifie la date
    void setDate(const std::chrono::system_clock::time_point& d);

    // Retourne le dossier médical associé
    DossierMedical* getDossier() const;
};

#endif
