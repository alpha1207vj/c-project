// include/model/Utilisateur.h
#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <string>

enum class Role {
    ADMINISTRATEUR,
    PROFESSIONNEL_SANTE
};

class Utilisateur {
protected:
    int id;
    std::string nomUtilisateur;
    std::string motDePasse;
    Role role;

public:
    Utilisateur(int id, const std::string& nomUtilisateur, const std::string& motDePasse, Role role);
    virtual ~Utilisateur() = default; // abstract class

    // Getters
    int getId() const;
    std::string getNomUtilisateur() const;
    std::string getMotDePasse() const;
    Role getRole() const;

    // Setters
    void setNomUtilisateur(const std::string& nom);
    void setMotDePasse(const std::string& mdp);
    void setRole(Role r);

    // Method
    bool verifierMotDePasse(const std::string& mdp) const;
};

#endif
