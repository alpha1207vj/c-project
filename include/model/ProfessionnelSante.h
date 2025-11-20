// include/model/ProfessionnelSante.h
#ifndef PROFESSIONNELSANTE_H
#define PROFESSIONNELSANTE_H

#include <vector>
#include <chrono> // Gestion des dates et heures
#include "model/Utilisateur.h"

class Consultation; // Déclaration anticipée pour éviter les inclusions circulaires

// Classe représentant un professionnel de santé dans le système.
// Hérite d’Utilisateur et ajoute des informations spécifiques
// comme la spécialité, les disponibilités et les consultations associées.
class ProfessionnelSante : public Utilisateur {
private:
    std::string specialite;   // Spécialité médicale du professionnel
    std::vector<std::chrono::system_clock::time_point> disponibilites;
    // Liste des créneaux horaires où le professionnel est disponible

    std::vector<Consultation*> consultations;
    // Relation 1 → plusieurs : un professionnel peut avoir plusieurs consultations

public:
    // Constructeur initialisant les informations de base du professionnel.

    ProfessionnelSante(int id, const std::string& nomUtilisateur,
                       const std::string& motDePasse, const std::string& specialite);

    // ----- Getters / Setters -----

    // Retourne la spécialité du professionnel.
    std::string getSpecialite() const;

    // Modifie la spécialité.
    void setSpecialite(const std::string& s);

    // ----- Disponibilités -----

    // Ajoute un créneau de disponibilité au professionnel.
    void ajouterDisponibilite(const std::chrono::system_clock::time_point& date);

    // Vérifie si un créneau donné fait partie des disponibilités.
    bool estDisponible(const std::chrono::system_clock::time_point& date) const;

    // ----- Consultations -----

    // Ajoute une consultation à la liste de celles du professionnel.
    void ajouterConsultation(Consultation* c);

    // Retourne la liste des consultations associées au professionnel.
    const std::vector<Consultation*>& getConsultations() const;
};

#endif
