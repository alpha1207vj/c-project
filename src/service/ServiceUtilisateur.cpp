#include "service/ServiceUtilisateur.h"
#include <string>
#include "model/Administrateur.h"
#include "model/ProfessionnelSante.h"
#include <iostream>  // for std::cout

// Destructor: clean up allocated users
ServiceUtilisateur::~ServiceUtilisateur() {
    for(auto u : utilisateurs)
        delete u;
}

// Create user with automatic ID
int ServiceUtilisateur::creerUtilisateur(const std::string& username,
                                         const std::string& password,
                                         Role r,  const std::string& speciality) {
    // Find next available unique ID
    bool unique = false;
    int id;
    while (!unique) {
        id = nextId++;
        unique = true;
        for (const auto& u : utilisateurs) {
            if (u->getId() == id) {
                unique = false;
                break;
            }
        }
    }

    // Create user
    Utilisateur* u;
    if (r == Role::ADMINISTRATEUR)
        u = new Administrateur(id, username, password);
    else
        u = new ProfessionnelSante(id, username, password,speciality);

    utilisateurs.push_back(u);
    return id;
}
// Create user from pointer (existing method)
void ServiceUtilisateur::creerUtilisateur(Utilisateur* u) {
    utilisateurs.push_back(u);
}

// Find user by ID
Utilisateur* ServiceUtilisateur::trouverUtilisateurParId(int id) {
    for(auto u : utilisateurs)
        if(u->getId() == id) return u;
    return nullptr;
}

// Delete user by ID
void ServiceUtilisateur::supprimerUtilisateur(int id) {
    for(auto it = utilisateurs.begin(); it != utilisateurs.end(); ++it) {
        if((*it)->getId() == id) {
            delete *it;
            utilisateurs.erase(it);
            return;
        }
    }
}

// Change user role
void ServiceUtilisateur::modifierRole(int id, Role nouveauRole, const std::string& spec) {
    Utilisateur* u = trouverUtilisateurParId(id);
    if(!u) return;

    if(nouveauRole == Role::PROFESSIONNEL_SANTE) {
        ProfessionnelSante* newProf = new ProfessionnelSante(
            u->getId(), u->getNomUtilisateur(), u->getMdp(), spec
        );

        // Replace in vector
        for (size_t i = 0; i < utilisateurs.size(); ++i) {
            if (utilisateurs[i]->getId() == id) {
                delete utilisateurs[i];
                utilisateurs[i] = newProf;
                break;
            }
        }
    } else {
        // Just update role
        u->setRole(nouveauRole);
    }
}


// List all users
void ServiceUtilisateur::listerUtilisateurs() const {
    for (auto u : utilisateurs) {
        std::cout << "ID: " << u->getId()
                  << ", Username: " << u->getNomUtilisateur()
                  << ", Role: " << ((u->getRole() == Role::ADMINISTRATEUR) ? "ADMIN" : "PROF");

        // If it's a professional, show the speciality
        if (u->getRole() == Role::PROFESSIONNEL_SANTE) {
            const ProfessionnelSante* ps = dynamic_cast<const ProfessionnelSante*>(u);
            if (ps) {
                std::cout << ", Speciality: " << ps->getSpecialite();
            }
        }

        std::cout << "\n";
    }
}

void ServiceUtilisateur::modifierSpecialite(int id, const std::string& nouvelleSpec) {
    Utilisateur* u = trouverUtilisateurParId(id);
    if (!u) return;

    // Try casting to professional
    auto prof = dynamic_cast<ProfessionnelSante*>(u);
    if (prof) {
        prof->setSpecialite(nouvelleSpec);
    }
}

// Authenticate
Utilisateur* ServiceUtilisateur::authentifier(const std::string& nomUtilisateur, const std::string& mdp) {
    for(auto u : utilisateurs)
        if(u->getNomUtilisateur() == nomUtilisateur && u->getMdp() == mdp)
            return u;
    return nullptr;
}
