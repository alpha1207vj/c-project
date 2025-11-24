#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <limits>
#include <string>
#include <sstream>     // pour std::ostringstream et std::istringstream
#include <iomanip>     // pour std::put_time et std::get_time
#include <chrono>      // pour std::chrono::system_clock et time_point
#include <ctime>       // pour std::tm

// =========================
//  CLASSE UTILITAIRE
// =========================
// La classe Utils regroupe des fonctions utilitaires statiques pour
// gérer la saisie console et la manipulation de dates.
class Utils {
public:
    // =========================
    //  SAISIE UTILISATEUR
    // =========================
    // Lit un entier depuis la console avec un message personnalisé.
    // Gère les erreurs de saisie et ne renvoie que des entiers valides.
    static int lireEntier(const std::string& message);

    // =========================
    //  FORMATAGE DE DATE
    // =========================
    // Convertit un time_point en chaîne "YYYY-MM-DD"
    static std::string formatDate(const std::chrono::system_clock::time_point& tp) {
        std::time_t t = std::chrono::system_clock::to_time_t(tp); // conversion vers time_t
        std::tm tm = *std::localtime(&t);                         // conversion vers tm
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d");                   // formatage
        return oss.str();
    }

    // =========================
    //  PARSING DE DATE
    // =========================
    // Convertit une chaîne "YYYY-MM-DD" en time_point
    static std::chrono::system_clock::time_point parseDate(const std::string& s) {
        std::tm tm = {};                                        // structure tm vide
        std::istringstream ss(s);
        ss >> std::get_time(&tm, "%Y-%m-%d");                   // parsing depuis la chaîne
        return std::chrono::system_clock::from_time_t(std::mktime(&tm)); // conversion en time_point
    }
};

#endif
