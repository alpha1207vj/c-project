#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <string>

// =========================
//  ENUM ROLE
// =========================
enum class Role {
    ADMINISTRATEUR,
    PROFESSIONNEL_SANTE
};

// =========================
//  CLASSE UTILISATEUR
// =========================
class Utilisateur {
protected:
    int id;                     // Identifiant unique
    std::string nomUtilisateur; // Nom d'utilisateur
    std::string motDePasse;     // Mot de passe
    Role role;                  // Rôle (admin ou professionnel)

public:
    // =========================
    //  CONSTRUCTEUR / DESTRUCTEUR
    // =========================
    Utilisateur(int id, const std::string& nomUtilisateur, const std::string& motDePasse, Role role);
    virtual ~Utilisateur() = default; // classe de base

    // =========================
    //  GETTERS
    // =========================
    int getId() const;
    std::string getNomUtilisateur() const;
    std::string getMotDePasse() const;
    Role getRole() const;

    // Pour accéder directement au mot de passe (optionnel)
    const std::string& getMdp() const { return motDePasse; }

    // =========================
    //  SETTERS
    // =========================
    void setNomUtilisateur(const std::string& nom);
    void setMotDePasse(const std::string& mdp);
    void setRole(Role r);

    // =========================
    //  MÉTHODES
    // =========================
    // Vérifie si le mot de passe fourni correspond
    bool verifierMotDePasse(const std::string& mdp) const;
};

#endif
