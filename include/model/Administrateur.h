// =========================
//  FICHIER: Administrateur.h
// =========================
#ifndef ADMINISTRATEUR_H
#define ADMINISTRATEUR_H

#include "model/Utilisateur.h"

// =========================
//  CLASSE ADMINISTRATEUR
// =========================
// Représente un administrateur du système.
// Hérite de la classe Utilisateur et a un rôle spécifique : ADMINISTRATEUR.
// Pas d’attributs supplémentaires, mais permet de distinguer facilement
// ce type d’utilisateur dans la logique de l’application.
class Administrateur : public Utilisateur {
public:
    // =========================
    //  CONSTRUCTEUR
    // =========================
    // Initialise un administrateur avec :
    // - identifiant (id)
    // - nom d’utilisateur (nomUtilisateur)
    // - mot de passe (motDePasse)
    // Le rôle est fixé automatiquement à ADMINISTRATEUR.
    Administrateur(int id, const std::string& nomUtilisateur, const std::string& motDePasse);

    // =========================
    //  DESTRUCTEUR
    // =========================
    // Par défaut, rien de spécial à libérer ici.
    ~Administrateur() = default;
};

#endif
