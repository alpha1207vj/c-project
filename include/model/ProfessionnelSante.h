#ifndef PROFESSIONNELSANTE_H
#define PROFESSIONNELSANTE_H

#include <vector>
#include <chrono>       // pour std::chrono::system_clock::time_point
#include "model/Utilisateur.h"

class Consultation;     // Déclaration anticipée pour éviter les inclusions circulaires

// =========================
//  CLASSE PROFESSIONNEL SANTÉ
// =========================
// Hérite de Utilisateur et représente un professionnel de santé.
// Ajoute :
// - Spécialité médicale
// - Créneaux horaires de disponibilité
// - Liste des consultations associées
class ProfessionnelSante : public Utilisateur {
private:
    // =========================
    // ATTRIBUTS
    // =========================
    std::string specialite;   // Spécialité médicale
    std::vector<std::chrono::system_clock::time_point> disponibilites; // Créneaux horaires
    std::vector<Consultation*> consultations; // Consultations du professionnel

public:
    // =========================
    // CONSTRUCTEUR
    // =========================
    ProfessionnelSante(int id,
                       const std::string& nomUtilisateur,
                       const std::string& motDePasse,
                       const std::string& specialite);

    // =========================
    // GETTERS / SETTERS
    // =========================
    std::string getSpecialite() const;      // Retourne la spécialité
    void setSpecialite(const std::string& s);// Modifie la spécialité

    // =========================
    // GESTION DES DISPONIBILITÉS
    // =========================
    void ajouterDisponibilite(const std::chrono::system_clock::time_point& date);
    bool estDisponible(const std::chrono::system_clock::time_point& date) const;

    // =========================
    // GESTION DES CONSULTATIONS
    // =========================
    void ajouterConsultation(Consultation* c);
    const std::vector<Consultation*>& getConsultations() const;
};

#endif
