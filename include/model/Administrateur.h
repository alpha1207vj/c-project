// include/model/Administrateur.h
#ifndef ADMINISTRATEUR_H
#define ADMINISTRATEUR_H

#include "model/Utilisateur.h"

// Classe représentant un administrateur du système.
// Hérite de Utilisateur avec un rôle spécifique (ADMINISTRATEUR).
// Ne possède pas d’attributs supplémentaires ici,
// mais permet de distinguer clairement ce type d’utilisateur
// dans la logique du programme.
class Administrateur : public Utilisateur {
public:
    // Constructeur : initialise un administrateur avec son identifiant,
    // nom d’utilisateur et mot de passe. Le rôle est fixé automatiquement.
    Administrateur(int id, const std::string& nomUtilisateur, const std::string& motDePasse);

    // Destructeur par défaut (rien de spécial à libérer ici).
    ~Administrateur() = default;
};

#endif
