#include "model/Administrateur.h"

// =========================
//  CONSTRUCTEUR
// =========================
// L'administrateur est simplement un utilisateur avec le rôle ADMINISTRATEUR
Administrateur::Administrateur(int id,
                               const std::string& nomUtilisateur,
                               const std::string& motDePasse)
    : Utilisateur(id, nomUtilisateur, motDePasse, Role::ADMINISTRATEUR) {}
