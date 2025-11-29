// =========================
//  FICHIER : Utilisateur.cpp
//  Implémentation de la classe Utilisateur
//  Modèle de base pour un utilisateur (Admin ou Professionnel)
// =========================

#include "model/Utilisateur.h"

// =========================
//  CONSTRUCTEUR
// =========================
// Initialise un utilisateur avec ID, nom, mot de passe et rôle
Utilisateur::Utilisateur(int id, const std::string& nomUtilisateur,
                         const std::string& motDePasse, Role role)
    : id(id), nomUtilisateur(nomUtilisateur), motDePasse(motDePasse), role(role) {}

// =========================
//  GETTERS
// =========================
int Utilisateur::getId() const {
    return id;  // Retourne l'ID unique de l'utilisateur
}

std::string Utilisateur::getNomUtilisateur() const {
    return nomUtilisateur;  // Retourne le nom d'utilisateur
}

std::string Utilisateur::getMotDePasse() const {
    return motDePasse;      // Retourne le mot de passe
}

Role Utilisateur::getRole() const {
    return role;            // Retourne le rôle de l'utilisateur
}

// =========================
//  SETTERS
// =========================
void Utilisateur::setNomUtilisateur(const std::string& nom) {
    nomUtilisateur = nom;   // Modifie le nom d'utilisateur
}

void Utilisateur::setMotDePasse(const std::string& mdp) {
    motDePasse = mdp;       // Modifie le mot de passe
}

void Utilisateur::setRole(Role r) {
    role = r;               // Modifie le rôle de l'utilisateur
}

// =========================
//  MÉTHODE DE VÉRIFICATION
// =========================
// Vérifie si le mot de passe fourni correspond à celui de l'utilisateur
bool Utilisateur::verifierMotDePasse(const std::string& mdp) const {
    return motDePasse == mdp;
}
