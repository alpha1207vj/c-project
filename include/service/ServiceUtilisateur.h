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
    int nextId = 1;  // auto-increment ID
public:
    ~ServiceUtilisateur();  // Destructor

    // Old method (manual ID)
    void creerUtilisateur(Utilisateur* u);

    // New method: auto-generate ID
    int creerUtilisateur(const std::string& username, const std::string& password, Role r,const std::string& speciality);

    void supprimerUtilisateur(int id);
   void modifierRole(int id, Role nouveauRole, const std::string& spec = "");

    Utilisateur* trouverUtilisateurParId(int id);
    void listerUtilisateurs() const;
    Utilisateur* authentifier(const std::string& nomUtilisateur, const std::string& mdp);
    void modifierSpecialite(int id, const std::string& nouvelleSpec);


    // Access all users
    const std::vector<Utilisateur*>& getUtilisateurs() const { return utilisateurs; }
};

#endif
