#ifndef SERVICE_UTILISATEUR_H
#define SERVICE_UTILISATEUR_H

#include <vector>
#include <string>
#include "model/Utilisateur.h"
#include "model/Administrateur.h"
#include "model/ProfessionnelSante.h"

// =========================
//  SERVICE UTILISATEUR
//  Gestion des utilisateurs : création, suppression, modification, export CSV
// =========================
class ServiceUtilisateur {
private:
    std::vector<Utilisateur*> utilisateurs;  // Liste de tous les utilisateurs
    int nextId = 1;                           // ID auto-incrémenté pour les nouveaux utilisateurs

public:
    // =========================
    //  DESTRUCTEUR
    // =========================
    ~ServiceUtilisateur();  // Nettoie les utilisateurs alloués dynamiquement

    // =========================
    //  CREATION D'UTILISATEUR
    // =========================
    // Création d'un utilisateur existant (pointeur)
    void creerUtilisateur(Utilisateur* u);

    // Création avec génération automatique d'ID
    int creerUtilisateur(const std::string& username,
                         const std::string& password,
                         Role r,
                         const std::string& speciality);

    // =========================
    //  SUPPRESSION ET MODIFICATION
    // =========================
    void supprimerUtilisateur(int id);

    // Modifier le rôle d'un utilisateur existant
    void modifierRole(int id, Role nouveauRole, const std::string& spec = "");

    // Modifier la spécialité d'un professionnel
    void modifierSpecialite(int id, const std::string& nouvelleSpec);

    // =========================
    //  RECHERCHE
    // =========================
    Utilisateur* trouverUtilisateurParId(int id);           // Trouver utilisateur par ID
    Utilisateur* trouverUtilisateurParNom(const std::string& nom); // Trouver utilisateur par nom

    // =========================
    //  LISTE ET AUTHENTIFICATION
    // =========================
    void listerUtilisateurs() const;                        // Affiche tous les utilisateurs
    Utilisateur* authentifier(const std::string& nomUtilisateur, const std::string& mdp); // Login

    // =========================
    //  IMPORT / EXPORT CSV
    // =========================
    bool exportToCSV(const std::string& filename) const;
    bool importFromCSV(const std::string& filename);

    // =========================
    //  ACCESSEURS
    // =========================
    const std::vector<Utilisateur*>& getUtilisateurs() const { return utilisateurs; }
};

#endif
