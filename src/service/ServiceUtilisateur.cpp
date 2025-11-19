#include "service/ServiceUtilisateur.h"
#include <iostream>

// Destructor: clean up all allocated users
ServiceUtilisateur::~ServiceUtilisateur() {
    for (auto u : utilisateurs) {
        delete u;
    }
}

// Add a user
void ServiceUtilisateur::creerUtilisateur(Utilisateur* u) {
    utilisateurs.push_back(u);
}

// Delete a user by ID
void ServiceUtilisateur::supprimerUtilisateur(int id) {
    for (auto it = utilisateurs.begin(); it != utilisateurs.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;  // free memory
            utilisateurs.erase(it);
            break;
        }
    }
}

// Change a user's role
void ServiceUtilisateur::modifierRole(int id, Role nouveauRole) {
    for (auto u : utilisateurs) {
        if (u->getId() == id) {
            u->setRole(nouveauRole);
            break;
        }
    }
}

// Find a user by ID
Utilisateur* ServiceUtilisateur::trouverUtilisateurParId(int id) {
    for (auto u : utilisateurs) {
        if (u->getId() == id) return u;
    }
    return nullptr;
}

// List all users
void ServiceUtilisateur::listerUtilisateurs() const {
    for (auto u : utilisateurs) {
        std::cout << "ID: " << u->getId()
                  << ", Username: " << u->getNomUtilisateur()
                  << ", Role: " << static_cast<int>(u->getRole())
                  << std::endl;
    }
}

// Authenticate user by username & password
Utilisateur* ServiceUtilisateur::authentifier(const std::string& nomUtilisateur, const std::string& mdp) {
    for (auto u : utilisateurs) {
        if (u->getNomUtilisateur() == nomUtilisateur && u->getMotDePasse() == mdp) {
            return u;
        }
    }
    return nullptr;
}
