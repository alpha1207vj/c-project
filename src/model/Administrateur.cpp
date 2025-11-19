// src/model/Administrateur.cpp
#include "model/Administrateur.h"

Administrateur::Administrateur(int id, const std::string& nomUtilisateur, const std::string& motDePasse)
    : Utilisateur(id, nomUtilisateur, motDePasse, Role::ADMINISTRATEUR) {}
