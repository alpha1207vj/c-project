#include "console/MedipassApp.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <limits>

// ================== Méthodes privées ==================

// Initialise l'application avec des données par défaut (admin, médecins, patients)
void MedipassApp::setupDefaultData() {
    using namespace std::chrono;

    // Placeholder pour l'initialisation de patients par défaut
    auto now = system_clock::now();
    // Ici vous pouvez ajouter des patients ou utilisateurs par défaut si nécessaire
}

// ------------------ Connexion ------------------

// Invite de connexion de base
void MedipassApp::login() {
    std::string username, password;

    do {
        // Demander le nom d'utilisateur
        std::cout << "Nom d'utilisateur (ou taper STOP pour arreter): ";
        std::cin >> username;

        // Quitter le programme si l'utilisateur tape STOP
        if (username == "STOP") {
            std::cout << "Arret du programme...\n";
            servicePatient.exportToCSV("patients.csv");
            serviceUser.exportToCSV("users.csv");
            exit(0);
        }

        // Demander le mot de passe
        std::cout << "Mot de passe: ";
        std::cin >> password;

        // Tentative d'authentification
        currentUser = serviceUser.authentifier(username, password);

        if (!currentUser) {
            // Réessayer si échec de la connexion
            char r;
            std::cout << "Connection ratee , recommencez (Y/N): ";
            std::cin >> r;
            if (r == 'N' || r == 'n') {
                servicePatient.exportToCSV("patients.csv");
                serviceUser.exportToCSV("users.csv");
                exit(0);
            }
        }

    } while (!currentUser);

    // Connexion réussie
    std::cout << "Bienvenue, " << currentUser->getNomUtilisateur() << "!\n";
}

// ================== Menu Administrateur ==================

// Affiche le menu principal et sous-menus pour l'administrateur
void MedipassApp::adminMenu() {
    ServiceStatistiques stats(&servicePatient, &serviceConsultation, &serviceUser);
    int choice;

    do {
        // Affichage du menu principal de l'administrateur
        std::cout << "\n--- Menu ADMIN ---\n"
                  << "1. Voir les statistiques du systeme \n"
                  << "2. Gerer les utilisateurs\n"
                  << "3. Deconnexion\n";

        choice = Utils::lireEntier("Entrer un choix: ");

        switch(choice) {

            // ------------------ Voir les statistiques ------------------
            case 1:
                stats.afficherStatistiquesCompletes();
                break;

            // ------------------ Gestion des utilisateurs ------------------
            case 2: {
                int userChoice;

                do {
                    // Affichage du sous-menu de gestion des utilisateurs
                    std::cout << "\n--- Gerer les utilisateurs ---\n"
                              << "1. Creer un utilisateur\n"
                              << "2. Supprimer un utilisateur\n"
                              << "3. Changer le role d'un utilisateur\n"
                              << "4. Liste des utilisateurs \n"
                              << "5. Retour\n";

                    userChoice = Utils::lireEntier("Choice: ");

                    switch(userChoice) {

                        // -------- Créer un utilisateur --------
                        case 1: {
                            std::string username, password, roleInput, speciality;
                            Role role;

                            std::cout << "Username: ";
                            std::getline(std::cin, username);

                            std::cout << "Password: ";
                            std::getline(std::cin, password);

                            // Boucle de sélection du rôle
                            do {
                                std::cout << "Role (ADMIN/PROF): ";
                                std::getline(std::cin, roleInput);
                                std::transform(roleInput.begin(), roleInput.end(),
                                               roleInput.begin(), ::toupper);

                                if(roleInput == "ADMIN")
                                    role = Role::ADMINISTRATEUR;
                                else if(roleInput == "PROF")
                                    role = Role::PROFESSIONNEL_SANTE;
                                else
                                    std::cout << "Invalid role, try again.\n";

                            } while(roleInput != "ADMIN" && roleInput != "PROF");

                            // Validation de la spécialité si professionnel
                            if(role == Role::PROFESSIONNEL_SANTE) {
                                while(true) {
                                    std::cout << "Speciality (GENERALIST/NURSE/INFIRMIER/GYNECOLOGIST/OPHTALMOLOGIST): ";
                                    std::getline(std::cin, speciality);
                                    std::transform(speciality.begin(), speciality.end(),
                                                   speciality.begin(), ::tolower);

                                    if(speciality == "generalist" ||
                                       speciality == "nurse" ||
                                       speciality == "infirmier" ||
                                       speciality == "gynecologist" ||
                                       speciality == "ophtalmologist") {
                                        break;
                                    }

                                    std::cout << "Specialite invalide, recommencez.\n";
                                }
                            }

                            int newId =
                                serviceUser.creerUtilisateur(username, password, role, speciality);
                            std::cout << "Utilisateur cree a l'id n*" << newId << ".\n";
                            break;
                        }

                        // -------- Supprimer un utilisateur --------
                        case 2: {
                            int id = Utils::lireEntier("Id de l'utilisateur a supprimer: ");

                            if (currentUser && currentUser->getId() == id) {
                                std::cout << "Vous ne pouvez pas supprimer votre compte.\n";
                                break;
                            }

                            if(serviceUser.trouverUtilisateurParId(id)) {
                                serviceUser.supprimerUtilisateur(id);
                                std::cout << "Utilisateur supprimer.\n";
                            } else {
                                std::cout << "Aucun utilisateur trouve.\n";
                            }
                            break;
                        }

                        // -------- Changer le rôle --------
                        case 3: {
                            int id = Utils::lireEntier("Entrer l'id de l'utilisateur: ");
                            Utilisateur* u = serviceUser.trouverUtilisateurParId(id);

                            if (currentUser && currentUser->getId() == id) {
                                std::cout << "Vous ne pouvez pas changez votre propre role.\n";
                                break;
                            }

                            if (!u) {
                                std::cout << "Utilisateur non trouve.\n";
                                break;
                            }

                            std::cout << "\nChoisir nouveau role:\n";
                            std::cout << "1. Admin\n";
                            std::cout << "2. Professionel\n";

                            int roleChoice = Utils::lireEntier("Votre choix: ");
                            Role newRole;
                            switch (roleChoice) {
                                case 1: newRole = Role::ADMINISTRATEUR; break;
                                case 2: newRole = Role::PROFESSIONNEL_SANTE; break;
                                default:
                                    std::cout << "Choix invalide.\n";
                                    break;
                            }

                            std::string spec = "";

                            // Choisir la spécialité si professionnel
                            if (newRole == Role::PROFESSIONNEL_SANTE) {
                                std::cout << "\nChoose Speciality:\n"
                                          << "1. Generalist\n2. Infirmier\n3. Infirmiere\n"
                                          << "4. Gynecologiste\n5. Ophtalmologiste\n";

                                int specChoice;
                                do {
                                    specChoice = Utils::lireEntier("Your choice: ");
                                    switch(specChoice) {
                                        case 1: spec = "generalist"; break;
                                        case 2: spec = "infirmier"; break;
                                        case 3: spec = "nurse"; break;
                                        case 4: spec = "gynecologist"; break;
                                        case 5: spec = "ophtalmologist"; break;
                                        default:
                                            std::cout << "Choix invalide, recommencez.\n";
                                            specChoice = 0;
                                            break;
                                    }
                                } while(specChoice == 0);
                            }

                            serviceUser.modifierRole(id, newRole, spec);

                            std::cout << "Role mis a jour avec succes";
                            if(newRole == Role::PROFESSIONNEL_SANTE)
                                std::cout << " avec specialite " << spec;
                            std::cout << ".\n";

                            break;
                        }

                        // -------- Lister les utilisateurs --------
                        case 4:
                            serviceUser.listerUtilisateurs();
                            break;

                        case 5:
                            break;

                        default:
                            std::cout << "Invalide.\n";
                            break;
                    }

                } while(userChoice != 5);
                break;
            }

            // ------------------ Quitter le menu admin ------------------
            case 3:
                std::cout << "SORTIE DU MENU ADMIN...\n";
                return;

            default:
                std::cout << "Choix invalide.\n";
                break;
        }

    } while(choice != 3);
}

// ================== Menu Professionnel ==================

// Affiche le menu principal pour le professionnel de santé
void MedipassApp::professionalMenu(ProfessionnelSante* prof) {
    int choice = 0;

    do {
        // Affichage du menu professionnel
        std::cout << "\n--- Menu Professionnel ---\n"
                  << "1. Voir mes patients\n"
                  << "2. Voir le dossier d'un patient\n"
                  << "3. Programmer une consultation\n"
                  << "4. Modifier une consultation\n"
                  << "5. Annuler une consultation\n"
                  << "6. Ajouter un patient\n"
                  << "7. Ajouter un antécédent\n"
                  << "8. Quitter\n";

        choice = Utils::lireEntier("Entrez votre choix : ");

        switch(choice) {

            // -------- Voir les patients --------
            case 1:
                for(Patient* p : servicePatient.getPatients())
                    std::cout << "ID Patient : " << p->getId()
                              << ", Nom : " << p->getNom() << "\n";
                break;

            // -------- Voir le dossier du patient --------
            case 2: {
                int pid = Utils::lireEntier("Entrez l'ID du patient : ");
                Patient* p = servicePatient.trouverPatientParId(pid);

                if(p && p->getDossier())
                    p->getDossier()->afficherDossier();
                else
                    std::cout << "Patient ou dossier introuvable.\n";
                break;
            }

            // -------- Programmer une consultation --------
            case 3: {
                int consId = Utils::lireEntier("Entrez l'ID de la consultation : ");
                int pid = Utils::lireEntier("Entrez l'ID du patient : ");

                Patient* p = servicePatient.trouverPatientParId(pid);
                if(!p) {
                    std::cout << "Patient introuvable.\n";
                    break;
                }

                std::string motif, obs;
                std::cout << "Entrez le motif : ";
                std::getline(std::cin, motif);

                std::cout << "Entrez les observations : ";
                std::getline(std::cin, obs);

                Consultation* c =
                    new Consultation(consId, std::chrono::system_clock::now(),
                                     p, prof, motif, obs, p->getDossier());

                if(!serviceConsultation.programmerConsultation(c))
                    delete c;
                else
                    p->getDossier()->ajouterConsultation(c);

                break;
            }

            // -------- Modifier une consultation --------
            case 4: {
                int cid = Utils::lireEntier("Entrez l'ID de la consultation à modifier : ");

                std::string motif, obs;
                std::cout << "Entrez le nouveau motif : ";
                std::getline(std::cin, motif);

                std::cout << "Entrez les nouvelles observations : ";
                std::getline(std::cin, obs);

                serviceConsultation.modifierConsultation(cid, motif, obs);
                break;
            }

            // -------- Annuler une consultation --------
            case 5: {
                int cid = Utils::lireEntier("Entrez l'ID de la consultation à annuler : ");
                serviceConsultation.annulerConsultation(cid);
                std::cout << "Consultation annulée.\n";
                break;
            }

            // -------- Ajouter un patient --------
            case 6: {
                std::string name, address, phone, dobStr;
                std::chrono::system_clock::time_point dob;

                std::cout << "Nom du patient : ";
                std::getline(std::cin, name);

                std::cout << "Date de naissance (YYYY-MM-DD, défaut 2000-01-01) : ";
                std::getline(std::cin, dobStr);

                std::tm tm = {};
                std::istringstream ss(dobStr);

                if(ss >> std::get_time(&tm, "%Y-%m-%d")) {
                    dob = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                } else {
                    std::cout << "Format invalide, date par défaut utilisée.\n";
                    std::tm def = {};
                    def.tm_year = 2000 - 1900;
                    def.tm_mon = 0;
                    def.tm_mday = 1;
                    dob = std::chrono::system_clock::from_time_t(std::mktime(&def));
                }

                std::cout << "Adresse : ";
                std::getline(std::cin, address);

                // Validation du téléphone
                while(true) {
                    std::cout << "Téléphone (chiffres uniquement) : ";
                    std::getline(std::cin, phone);

                    bool valid = !phone.empty();
                    for(char c : phone)
                        if(!isdigit(c)) valid = false;

                    if(valid) break;
                    std::cout << "Numéro invalide.\n";
                }

                int newId = servicePatient.creerPatient(name, dob, address, phone);
                std::cout << "Patient créé avec l'ID " << newId << ".\n";
                break;
            }

            // -------- Ajouter un antécédent --------
            case 7: {
                int patientId = Utils::lireEntier("Entrez l'ID du patient pour ajouter un antécédent : ");

                Patient* patient = servicePatient.trouverPatientParId(patientId);

                if(!patient || !patient->getDossier()) {
                    std::cout << "Patient introuvable ou dossier manquant.\n";
                    break;
                }

                std::string desc;
                std::cout << "Entrez la description de l'antécédent : ";
                std::getline(std::cin, desc);

                int newAntecedentId = patient->getDossier()->getAntecedents().size() + 1;
                auto now = std::chrono::system_clock::now();

                patient->getDossier()->ajouterAntecedent(
                    new Antecedent(newAntecedentId, desc, now, patient->getDossier())
                );

                std::cout << "Antécédent ajouté avec l'ID " << newAntecedentId << ".\n";
                break;
            }

            // -------- Quitter le menu professionnel --------
            case 8:
                std::cout << "Sortie du menu professionnel...\n";
                return;

            default:
                std::cout << "Choix invalide.\n";
                break;
        }

    } while(choice != 8);
}

// ================== Méthode publique ==================

// Boucle principale de l'application
void MedipassApp::run() {
    // Initialisation des utilisateurs et patients par défaut
    setupDefaultData();

    // Importation des données existantes depuis les fichiers CSV
    servicePatient.importFromCSV("patients.csv", serviceUser);
    serviceUser.importFromCSV("users.csv");

    // Boucle principale pour gérer plusieurs connexions
    while(true) {
        login();

        if(currentUser->getRole() == Role::ADMINISTRATEUR)
            adminMenu();
        else if(currentUser->getRole() == Role::PROFESSIONNEL_SANTE)
            professionalMenu(static_cast<ProfessionnelSante*>(currentUser));

        currentUser = nullptr;
        std::cout << "\nReturning to login...\n";
    }
}
