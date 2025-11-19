#include <iostream>
#include <string>
#include <chrono>
#include "service/ServiceUtilisateur.h"
#include "service/ServicePatient.h"
#include "service/ServiceConsultation.h"
#include "service/ServiceStatistiques.h"
#include "model/Administrateur.h"
#include "model/ProfessionnelSante.h"
#include "model/Patient.h"
#include "model/Consultation.h"
#include "model/DossierMedical.h"
#include "model/Antecedent.h"
#include "console/Utils.h"

// ------------------ Admin Menu ------------------
void adminMenu(ServiceUtilisateur& serviceUser, ServicePatient& servicePatient, ServiceConsultation& serviceConsultation) {
    ServiceStatistiques stats(&servicePatient, &serviceConsultation, &serviceUser);
    int choice;

    do {
        std::cout << "\n--- Admin Menu ---\n";
        std::cout << "1. View Statistics\n";
        std::cout << "2. Manage Users\n";
        std::cout << "3. Exit\n";
        choice = Utils::lireEntier("Enter choice: ");


        switch(choice) {
            case 1:
                std::cout << "Total Patients: " << stats.compterPatients() << "\n";
                std::cout << "Total Consultations: " << stats.compterConsultations() << "\n";
                std::cout << "Total Professionals: " << stats.compterProfessionnelsParRole(Role::PROFESSIONNEL_SANTE) << "\n";
                break;
            case 2: {
                int userChoice;
                do {
                    std::cout << "\n--- Manage Users ---\n";
                    std::cout << "1. Create User\n2. Delete User\n3. Change Role\n4. List Users\n5. Back\n";
                    userChoice = Utils::lireEntier("Choice: ");
                    switch(userChoice) {
                        case 1: {
                            int id = Utils::lireEntier("Enter user ID: ");

    // Check if ID is already taken
    if (serviceUser.trouverUtilisateurParId(id)) {
        std::cout << "Error: User ID " << id << " is already taken.\n";
    } else {
        std::string username, password, roleInput;
        std::cout << "Username: "; std::cin >> username;
        std::cout << "Password: "; std::cin >> password;
        std::cout << "Role (ADMIN/PROF): "; std::cin >> roleInput;

        if (roleInput == "ADMIN")
            serviceUser.creerUtilisateur(new Administrateur(id, username, password));
        else
            serviceUser.creerUtilisateur(new ProfessionnelSante(id, username, password, "General"));

        std::cout << "User created.\n";
    }
    break;
                        }
                        case 2: {
                            int id;
    id = Utils::lireEntier("User ID to delete: ");
    Utilisateur* u = serviceUser.trouverUtilisateurParId(id);
    if (u) {
        serviceUser.supprimerUtilisateur(id);
        std::cout << "User deleted.\n";
    } else {
        std::cout << "Error: User with ID " << id << " not found.\n";
    }
    break;
                        }
                        case 3: {
                           int id;
    id = Utils::lireEntier("User ID: ");
    Utilisateur* u = serviceUser.trouverUtilisateurParId(id);
    if (u) {
        std::string newRole;
        std::cout << "New Role (ADMIN/PROF): ";
        std::cin >> newRole;
        Role r = (newRole=="ADMIN") ? Role::ADMINISTRATEUR : Role::PROFESSIONNEL_SANTE;
        serviceUser.modifierRole(id,r);
        std::cout << "Role updated.\n";
    } else {
        std::cout << "Error: User with ID " << id << " not found.\n";
    }
    break;
                        }
                        case 4:
                            serviceUser.listerUtilisateurs();
                            break;
                        case 5: break;
                        default: std::cout << "Invalid.\n";
                    }
                } while(userChoice != 5);
                break;
            }
            case 3:
                std::cout << "Exiting Admin Menu...\n";
                break;
            default: std::cout << "Invalid choice.\n";
        }

    } while(choice != 3);
}

// ------------------ Professional Menu ------------------
void professionalMenu(ProfessionnelSante* prof, ServicePatient& servicePatient, ServiceConsultation& serviceConsultation) {
    int choice = 0;
    do {
        std::cout << "\n--- Professional Menu ---\n";
        std::cout << "1. View My Patients\n";
        std::cout << "2. View Patient Dossier\n";
        std::cout << "3. Schedule Consultation\n";
        std::cout << "4. Modify Consultation\n";
        std::cout << "5. Cancel Consultation\n";
        std::cout << "6. List Consultations by Patient\n";
        std::cout << "7. Exit\n";
        choice = Utils::lireEntier("Enter your choice: ");
        switch (choice) {
            case 1: {
                std::cout << "\n--- My Patients ---\n";
                for (Patient* p : servicePatient.getPatients()) {
                    std::cout << "Patient ID: " << p->getId() << ", Name: " << p->getNom() << "\n";
                }
                break;
            }
            case 2: {
                int pid;
                pid = Utils::lireEntier("Enter Patient ID to view dossier: ");
                Patient* p = servicePatient.trouverPatientParId(pid);
                if (p && p->getDossier()) {
                    p->getDossier()->afficherDossier();
                } else {
                    std::cout << "Patient or dossier not found.\n";
                }
                break;
            }
            case 3: {
                int pid, consId;
                std::string motif, obs;
                consId = Utils::lireEntier("Enter Consultation ID: ");
                pid = Utils::lireEntier("Enter Patient ID: ");
                Patient* p = servicePatient.trouverPatientParId(pid);
                if (!p) { std::cout << "Patient not found.\n"; break; }
                std::cout << "Enter Motif: "; std::cin.ignore(); std::getline(std::cin, motif);
                std::cout << "Enter Observations: "; std::getline(std::cin, obs);

                Consultation* c = new Consultation(consId, std::chrono::system_clock::now(), p, prof, motif, obs, p->getDossier());

// Try to schedule it, check for duplicate ID
if(!serviceConsultation.programmerConsultation(c)) {
    delete c; // cleanup if creation failed
} else {
    p->getDossier()->ajouterConsultation(c); // only add if scheduling succeeded
}
     break;
            }
            case 4: {
                int cid;
                std::string motif, obs;
                cid = Utils::lireEntier("Enter Consultation ID to modify: ");
                std::cout << "Enter new Motif: "; std::getline(std::cin, motif);
                std::cout << "Enter new Observations: "; std::getline(std::cin, obs);
                serviceConsultation.modifierConsultation(cid, motif, obs);

                break;
            }
            case 5: {
                int cid;
                cid = Utils::lireEntier("Enter Consultation ID to cancel: ");
                serviceConsultation.annulerConsultation(cid);
                std::cout << "Consultation canceled.\n";
                break;
            }
            case 6: {
                int pid;
                pid = Utils::lireEntier("Enter Patient ID: ");
                Patient* p = servicePatient.trouverPatientParId(pid);
                if (!p) { std::cout << "Patient not found.\n"; break; }
                const auto& consList = serviceConsultation.listerConsultationsParPatient(p);
                std::cout << "Consultations for " << p->getNom() << ":\n";
                for (auto c : consList) {
                    std::cout << "ID: " << c->getId() << ", Motif: " << c->getMotif() << ", Observations: " << c->getObservations() << "\n";
                }
                break;
            }
            case 7:
                std::cout << "Exiting Professional Menu...\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 7);
}

// ------------------ Main ------------------
int main() {
    ServiceUtilisateur serviceUser;
    ServicePatient servicePatient;
    ServiceConsultation serviceConsultation;

    auto now = std::chrono::system_clock::now();

    // --- Default users ---
    serviceUser.creerUtilisateur(new Administrateur(1,"admin","adminpass"));
    serviceUser.creerUtilisateur(new ProfessionnelSante(2,"doc1","doc1pass","Cardiology"));
    serviceUser.creerUtilisateur(new ProfessionnelSante(3,"doc2","doc2pass","Pediatrics"));

    // --- Default patients and dossiers ---
    Patient* alice = new Patient(1,"Alice", now, "123 Street","111-222");
    DossierMedical* dAlice = new DossierMedical(alice);
    alice->setDossier(dAlice);
    dAlice->ajouterAntecedent(new Antecedent(1,"Diabetes",now,dAlice));
    servicePatient.creerPatient(alice);

    Patient* bob = new Patient(2,"Bob", now, "456 Avenue","333-444");
    DossierMedical* dBob = new DossierMedical(bob);
    bob->setDossier(dBob);
    dBob->ajouterAntecedent(new Antecedent(2,"Hypertension",now,dBob));
    servicePatient.creerPatient(bob);

    // --- Login ---
    std::string username, password;
    Utilisateur* currentUser = nullptr;

    do {
        std::cout << "Username: "; std::cin >> username;
        std::cout << "Password: "; std::cin >> password;
        currentUser = serviceUser.authentifier(username,password);
        if(!currentUser) {
            std::cout << "Login failed. Retry? (Y/N): ";
            char r; std::cin >> r;
            if(r=='N'||r=='n') return 0;
        }
    } while(!currentUser);

    std::cout << "Welcome, " << currentUser->getNomUtilisateur() << "!\n";

    if(currentUser->getRole() == Role::ADMINISTRATEUR)
        adminMenu(serviceUser, servicePatient, serviceConsultation);
    else if(currentUser->getRole() == Role::PROFESSIONNEL_SANTE)
        professionalMenu(dynamic_cast<ProfessionnelSante*>(currentUser), servicePatient, serviceConsultation);

    std::cout << "Logging out.\n";
    return 0;
}
