#include "console/Utils.h"

int Utils::lireEntier(const std::string& message) {
    int valeur;
    while (true) {
        std::cout << message;
        std::cin >> valeur;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Erreur: veuillez entrer un nombre valide.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valeur;
        }
    }
}
