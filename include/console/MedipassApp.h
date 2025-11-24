#ifndef MEDIPASSAPP_H
#define MEDIPASSAPP_H

#include <string>

// =========================
//  INCLUSIONS DES SERVICES
// =========================
#include "service/ServiceUtilisateur.h"   // Gestion des utilisateurs (login, création, etc.)
#include "service/ServicePatient.h"       // Gestion des patients (CRUD, export CSV, etc.)
#include "service/ServiceConsultation.h"  // Gestion des consultations
#include "service/ServiceStatistiques.h"  // Statistiques et analyses diverses

// =========================
//  INCLUSIONS DES MODELES
// =========================
#include "model/Administrateur.h"         // Classe Administrateur
#include "model/ProfessionnelSante.h"     // Classe Professionnel de santé
#include "model/Patient.h"                 // Classe Patient
#include "model/Consultation.h"            // Classe Consultation
#include "model/DossierMedical.h"          // Dossier médical associé au patient
#include "model/Antecedent.h"              // Antécédents médicaux

#include "console/Utils.h"                 // Fonctions utilitaires pour l'interface console

// =========================
//  CLASSE PRINCIPALE DE L'APPLICATION
// =========================
class MedipassApp {
private:
    // =========================
    //  SERVICES
    // =========================
    ServiceUtilisateur serviceUser;         // Service pour gérer les utilisateurs
    ServicePatient servicePatient;          // Service pour gérer les patients
    ServiceConsultation serviceConsultation;// Service pour gérer les consultations

    // =========================
    //  UTILISATEUR ACTUEL
    // =========================
    Utilisateur* currentUser = nullptr;     // Pointeur vers l'utilisateur actuellement connecté

    // =========================
    //  MENUS INTERNES
    // =========================
    void adminMenu();                        // Menu spécifique pour l'administrateur
    void professionalMenu(ProfessionnelSante* prof); // Menu pour le professionnel de santé

    // =========================
    //  FONCTIONS D'INITIALISATION ET CONNEXION
    // =========================
    void login();                            // Gestion de la connexion
    void setupDefaultData();                 // Initialisation de données par défaut

public:
    // =========================
    //  CONSTRUCTEUR ET EXÉCUTION
    // =========================
    MedipassApp() = default;                 // Constructeur par défaut
    void run();                              // Lancement de l'application
};

#endif
