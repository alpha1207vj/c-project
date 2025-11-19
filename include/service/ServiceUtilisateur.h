#ifndef SERVICE_UTILISATEUR_H
#define SERVICE_UTILISATEUR_H

#include <vector>
#include <string>
#include "model/Utilisateur.h"
#include "model/Administrateur.h"
#include "model/ProfessionnelSante.h"

class ServiceUtilisateur {
private:
    std::vector<Utilisateur*> utilisateurs;

public:
    ~ServiceUtilisateur();  // declare destructor here

    void creerUtilisateur(Utilisateur* u);
    void supprimerUtilisateur(int id);
    void modifierRole(int id, Role nouveauRole);
    Utilisateur* trouverUtilisateurParId(int id);
    void listerUtilisateurs() const;
    Utilisateur* authentifier(const std::string& nomUtilisateur, const std::string& mdp); // return Utilisateur*, not bool

    // <<< ADD THIS
    const std::vector<Utilisateur*>& getUtilisateurs() const { return utilisateurs; }
};

#endif
