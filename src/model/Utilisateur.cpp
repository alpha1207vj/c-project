// src/model/Utilisateur.cpp
#include "model/Utilisateur.h"

Utilisateur::Utilisateur(int id, const std::string& nomUtilisateur, const std::string& motDePasse, Role role)
    : id(id), nomUtilisateur(nomUtilisateur), motDePasse(motDePasse), role(role) {}

// Getters
int Utilisateur::getId() const { return id; }
std::string Utilisateur::getNomUtilisateur() const { return nomUtilisateur; }
std::string Utilisateur::getMotDePasse() const { return motDePasse; }
Role Utilisateur::getRole() const { return role; }

// Setters
void Utilisateur::setNomUtilisateur(const std::string& nom) { nomUtilisateur = nom; }
void Utilisateur::setMotDePasse(const std::string& mdp) { motDePasse = mdp; }
void Utilisateur::setRole(Role r) { role = r; }

// Method
bool Utilisateur::verifierMotDePasse(const std::string& mdp) const {
    return motDePasse == mdp;
}
