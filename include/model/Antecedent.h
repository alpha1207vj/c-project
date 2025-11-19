// include/model/Antecedent.h
#ifndef ANTECEDENT_H
#define ANTECEDENT_H

#include <string>
#include <chrono>

// Déclaration anticipée pour éviter une inclusion circulaire.
class DossierMedical;

// Classe représentant un antécédent médical d’un patient.
// Peut être une maladie passée, une opération, une allergie, etc.
class Antecedent {
private:
    int id;                         // Identifiant unique de l'antécédent
    std::string description;        // Description de l'événement médical
    std::chrono::system_clock::time_point date;
    // Date à laquelle cet antécédent a eu lieu

    DossierMedical* dossier;        // Dossier médical auquel cet antécédent appartient

public:
    // Constructeur initialisant toutes les informations de l’antécédent.
    Antecedent(int id,
               const std::string& description,
               const std::chrono::system_clock::time_point& date,
               DossierMedical* dossier);

    // ----- Getters / Setters -----

    // Retourne l’identifiant.
    int getId() const;

    // Retourne la description.
    std::string getDescription() const;

    // Modifie la description.
    void setDescription(const std::string& desc);

    // Retourne la date de l’antécédent.
    std::chrono::system_clock::time_point getDate() const;

    // Modifie la date.
    void setDate(const std::chrono::system_clock::time_point& d);

    // Retourne le dossier auquel appartient cet antécédent.
    DossierMedical* getDossier() const;
};

#endif
