#ifndef SERVICE_STATISTIQUES_H
#define SERVICE_STATISTIQUES_H

#include "ServicePatient.h"
#include "ServiceConsultation.h"
#include "ServiceUtilisateur.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

// =========================
//  SERVICE STATISTIQUES
//  Calcul et affichage des statistiques pour l'application
// =========================
class ServiceStatistiques {
private:
    ServicePatient* servicePatient;           // Service de gestion des patients
    ServiceConsultation* serviceConsultation; // Service de gestion des consultations
    ServiceUtilisateur* serviceUtilisateur;   // Service de gestion des utilisateurs

public:
    // =========================
    //  CONSTRUCTEUR
    // =========================
    ServiceStatistiques(ServicePatient* sp, ServiceConsultation* sc, ServiceUtilisateur* su);

    // =========================
    //  MÉTHODES DE COMPTAGE
    // =========================
    int compterPatients() const;                             // Nombre total de patients
    int compterConsultations() const;                        // Nombre total de consultations
    int compterProfessionnelsParRole(Role role) const;       // Nombre de professionnels par rôle
    int compterProfessionnelsParSpecialite(const std::string& specialite) const; // Nombre par spécialité

    // =========================
    //  AFFICHAGE
    // =========================
    void afficherStatistiquesCompletes() const;             // Affiche toutes les statistiques
};

#endif
