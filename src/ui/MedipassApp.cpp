#include "console/MedipassApp.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <limits>

// ------------------ Private Methods ------------------

// Populate the app with default admin, doctors and patients
void MedipassApp::setupDefaultData() {
    using namespace std::chrono;



    // Default patients
    auto now = system_clock::now();


}

// Basic login prompt
void MedipassApp::login() {
    std::string username, password;

    do {
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        currentUser = serviceUser.authentifier(username, password);

       if(!currentUser) {
    char r;
    std::cout << "Login failed. Retry? (Y/N): ";
    std::cin >> r; // <-- THIS WAS MISSING
    if(r == 'N' || r == 'n') {
        // Export before quitting
        servicePatient.exportToCSV("patients.csv");
        serviceUser.exportToCSV("users.csv");

        exit(0);
    }
    // If user typed Y, the loop continues
}
    } while(!currentUser);

    std::cout << "Welcome, " << currentUser->getNomUtilisateur() << "!\n";
}

// Admin dashboard and its submenus
void MedipassApp::adminMenu() {
    ServiceStatistiques stats(&servicePatient, &serviceConsultation, &serviceUser);
    int choice;

    do {
        std::cout << "\n--- Admin Menu ---\n"
                  << "1. View Statistics\n"
                  << "2. Manage Users\n"
                  << "3. Exit\n";

        choice = Utils::lireEntier("Enter choice: ");

        switch(choice) {

            case 1:
                stats.afficherStatistiquesCompletes();
                break;

            case 2: {
                // User management submenu
                int userChoice;

                do {
                    std::cout << "\n--- Manage Users ---\n"
                              << "1. Create User\n"
                              << "2. Delete User\n"
                              << "3. Change Role\n"
                              << "4. List Users\n"
                              << "5. Back\n";

                    userChoice = Utils::lireEntier("Choice: ");

                    switch(userChoice) {

                        // Create new user
                        case 1: {
                            std::string username, password, roleInput, speciality;
                            Role role;



                            std::cout << "Username: ";
                            std::getline(std::cin, username);

                            std::cout << "Password: ";
                            std::getline(std::cin, password);

                            // Role selection loop
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

                            // Professional specialty validation
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

                                    std::cout << "Invalid speciality. Try again.\n";
                                }
                            }

                            int newId =
                                serviceUser.creerUtilisateur(username, password, role, speciality);

                            std::cout << "User created with ID " << newId << ".\n";
                            break;
                        }

                        // Delete user
                        case 2: {
                            int id = Utils::lireEntier("User ID to delete: ");
                            if (currentUser && currentUser->getId() == id) {
    std::cout << "You cannot delete your own account.\n";
    break;
}
                            if(serviceUser.trouverUtilisateurParId(id)) {
                                serviceUser.supprimerUtilisateur(id);
                                std::cout << "User deleted.\n";
                            } else {
                                std::cout << "User not found.\n";
                            }
                            break;
                        }

                        // Change user role
                       // Change user role
                         case 3: {
    int id = Utils::lireEntier("Enter User ID: ");
    Utilisateur* u = serviceUser.trouverUtilisateurParId(id);

     // Prevent changing own role
if (currentUser && currentUser->getId() == id) {
    std::cout << "You cannot change your own role.\n";
    break;
}

    if (!u) {
        std::cout << "User not found.\n";
        break;
    }

    std::cout << "\nChoose new role:\n";
    std::cout << "1. Admin\n";
    std::cout << "2. Professional\n";

    int roleChoice = Utils::lireEntier("Your choice: ");
    Role newRole;
    switch (roleChoice) {
        case 1: newRole = Role::ADMINISTRATEUR; break;
        case 2: newRole = Role::PROFESSIONNEL_SANTE; break;
        default:
            std::cout << "Invalid choice.\n";
            break;
    }

    std::string spec = "";

    // If new role is professional, force to choose a speciality from predefined list
    if (newRole == Role::PROFESSIONNEL_SANTE) {
        std::cout << "\nChoose Speciality:\n";
        std::cout << "1. Generalist\n";
        std::cout << "2. Infirmier\n";
        std::cout << "3. Nurse\n";
        std::cout << "4. Gynecologist\n";
        std::cout << "5. Ophtalmologist\n";

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
                    std::cout << "Invalid choice, try again.\n";
                    specChoice = 0;
                    break;
            }
        } while(specChoice == 0);
    }

    // **Important**: replace the object with correct type
    serviceUser.modifierRole(id, newRole, spec);

    std::cout << "Role updated successfully";
    if(newRole == Role::PROFESSIONNEL_SANTE)
        std::cout << " with speciality " << spec;
    std::cout << ".\n";

    break;
}

                        // List all users
                        case 4:
                            serviceUser.listerUtilisateurs();
                            break;

                        case 5:
                            break;

                        default:
                            std::cout << "Invalid.\n";
                            break;
                    }

                } while(userChoice != 5);
                break;
            }

            case 3:
                std::cout << "Exiting Admin Menu...\n";
                return;

            default:
                std::cout << "Invalid choice.\n";
                break;
        }

    } while(choice != 3);
}

// Professional (doctor) dashboard
void MedipassApp::professionalMenu(ProfessionnelSante* prof) {
    int choice = 0;

    do {
        std::cout << "\n--- Professional Menu ---\n"
                  << "1. View My Patients\n"
                  << "2. View Patient Dossier\n"
                  << "3. Schedule Consultation\n"
                  << "4. Modify Consultation\n"
                  << "5. Cancel Consultation\n"
                  << "6. Add Patient\n"
                  << "7. Add Antecedent\n"
                  << "8. Exit\n";

        choice = Utils::lireEntier("Enter your choice: ");

        switch(choice) {

            case 1:
                // List all patients
                for(Patient* p : servicePatient.getPatients())
                    std::cout << "Patient ID: " << p->getId()
                              << ", Name: " << p->getNom() << "\n";
                break;

            case 2: {
                // Show dossier of a given patient
                int pid = Utils::lireEntier("Enter Patient ID: ");
                Patient* p = servicePatient.trouverPatientParId(pid);

                if(p && p->getDossier())
                    p->getDossier()->afficherDossier();
                else
                    std::cout << "Patient or dossier not found.\n";

                break;
            }

            case 3: {
                // Schedule a new consultation
                int consId = Utils::lireEntier("Enter Consultation ID: ");
                int pid = Utils::lireEntier("Enter Patient ID: ");

                Patient* p = servicePatient.trouverPatientParId(pid);
                if(!p) {
                    std::cout << "Patient not found.\n";
                    break;
                }

                std::string motif, obs;

                std::cout << "Enter Motif: ";
                std::getline(std::cin, motif);

                std::cout << "Enter Observations: ";
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

            case 4: {
                // Edit consultation
                int cid = Utils::lireEntier("Enter Consultation ID to modify: ");


                std::string motif, obs;

                std::cout << "Enter new Motif: ";
                std::getline(std::cin, motif);

                std::cout << "Enter new Observations: ";
                std::getline(std::cin, obs);

                serviceConsultation.modifierConsultation(cid, motif, obs);
                break;
            }

            case 5: {
                // Cancel consultation
                int cid = Utils::lireEntier("Enter Consultation ID to cancel: ");
                serviceConsultation.annulerConsultation(cid);
                std::cout << "Consultation canceled.\n";
                break;
            }


            case 6: {
                // Add a new patient
                std::string name, address, phone;
                std::string dobStr;
                std::chrono::system_clock::time_point dob;



                std::cout << "Patient Name: ";
                std::getline(std::cin, name);

                std::cout << "Date of Birth (YYYY-MM-DD, default 2000-01-01): ";
                std::getline(std::cin, dobStr);

                std::tm tm = {};
                std::istringstream ss(dobStr);

                if(ss >> std::get_time(&tm, "%Y-%m-%d")) {
                    dob = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                } else {
                    std::cout << "Invalid format, using default date.\n";
                    std::tm def = {};
                    def.tm_year = 2000 - 1900;
                    def.tm_mon = 0;
                    def.tm_mday = 1;
                    dob = std::chrono::system_clock::from_time_t(std::mktime(&def));
                }

                std::cout << "Address: ";
                std::getline(std::cin, address);

                // Phone validation loop
                while(true) {
                    std::cout << "Phone (numbers only): ";
                    std::getline(std::cin, phone);

                    bool valid = !phone.empty();
                    for(char c : phone)
                        if(!isdigit(c)) valid = false;

                    if(valid)
                        break;

                    std::cout << "Invalid phone.\n";
                }

                int newId = servicePatient.creerPatient(name, dob, address, phone);
                std::cout << "Patient created with ID " << newId << ".\n";
                break;
            }

            case 7: {
                // Add antecedent to patient dossier
                int patientId;
                std::cout << "Enter Patient ID to add antecedent: ";
                patientId = Utils::lireEntier("");

                Patient* patient = servicePatient.trouverPatientParId(patientId);

                if(!patient || !patient->getDossier()) {
                    std::cout << "Patient not found or dossier missing.\n";
                    break;
                }


                std::string desc;

                std::cout << "Enter antecedent description: ";
                std::getline(std::cin, desc);

                int newAntecedentId =
                    patient->getDossier()->getAntecedents().size() + 1;

                auto now = std::chrono::system_clock::now();

                patient->getDossier()->ajouterAntecedent(
                    new Antecedent(newAntecedentId, desc, now, patient->getDossier())
                );

                std::cout << "Antecedent added with ID " << newAntecedentId << ".\n";
                break;
            }

            case 8:
                std::cout << "Exiting Professional Menu...\n";
                return;

            default:
                std::cout << "Invalid choice.\n";
                break;
        }

    } while(choice != 8);
}

// ------------------ Public Method ------------------
void MedipassApp::run() {
    setupDefaultData();

    // Import data automatically
    servicePatient.importFromCSV("patients.csv",serviceUser);
    serviceUser.importFromCSV("users.csv");

    while(true) { // Loop for multiple logins
        login();

        if(currentUser->getRole() == Role::ADMINISTRATEUR)
            adminMenu();
        else if(currentUser->getRole() == Role::PROFESSIONNEL_SANTE)
            professionalMenu(static_cast<ProfessionnelSante*>(currentUser));

        currentUser = nullptr;
        std::cout << "\nReturning to login...\n";
    }
}
