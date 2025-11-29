#include "console/Utils.h"
#include <iostream>
#include <limits> // Pour std::numeric_limits

// ================== Utils ==================

// Lit un entier depuis l'entrée standard avec un message.
// Tant que l'utilisateur ne fournit pas un entier valide, la fonction redemande.
// message : texte affiché à l'utilisateur pour lui indiquer ce qu'il doit entrer
int Utils::lireEntier(const std::string& message) {
    int valeur;

    while (true) {
        // Affiche le message pour demander l'entrée
        std::cout << message;
        std::cin >> valeur;

        // Vérifie si l'entrée est invalide (pas un entier)
        if (std::cin.fail()) {
            // Réinitialise le flux pour pouvoir réessayer
            std::cin.clear();
            // Ignore les caractères restants jusqu'à la fin de ligne
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Erreur: veuillez entrer un nombre valide.\n";
        } else {
            // Ignore les caractères restants jusqu'à la fin de ligne
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // Retourne l'entier valide
            return valeur;
        }
    }
}
