
#ifndef MEDIPASSAPP_H
#define MEDIPASSAPP_H

#include <string>
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

class MedipassApp {
private:
    ServiceUtilisateur serviceUser;
    ServicePatient servicePatient;
    ServiceConsultation serviceConsultation;

    Utilisateur* currentUser = nullptr;

    void adminMenu();
    void professionalMenu(ProfessionnelSante* prof);

    void login();
    void setupDefaultData();

public:
    MedipassApp() = default;
    void run(); // starts the app
};

#endif
