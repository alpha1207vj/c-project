#include "service/ServicePatient.h"
#include <iostream>

void ServicePatient::creerPatient(Patient* p) {
    patients.push_back(p);
}

void ServicePatient::supprimerPatient(int id) {
    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if ((*it)->getId() == id) {
            patients.erase(it);
            break;
        }
    }
}

Patient* ServicePatient::trouverPatientParId(int id) {
    for (auto p : patients) {
        if (p->getId() == id)
            return p;
    }
    return nullptr;
}

void ServicePatient::mettreAJourPatient(Patient* p) {
    Patient* existing = trouverPatientParId(p->getId());
    if (existing) {
        existing->setNom(p->getNom());
        existing->setAdresse(p->getAdresse());
        existing->setTelephone(p->getTelephone());
    }
}

void ServicePatient::listerPatients() const {
    for (auto p : patients) {
        std::cout << "Patient: " << p->getNom() << ", Adresse: " << p->getAdresse() << std::endl;
    }
}
int ServicePatient::creerPatient(const std::string& name,
                                 const std::chrono::system_clock::time_point& dob,
                                 const std::string& address,
                                 const std::string& phone) {
    // Generate unique ID
    int id;
    bool unique = false;
    while(!unique) {
        id = nextId++;
        unique = true;
        for (auto p : patients) {
            if (p->getId() == id) {
                unique = false;
                break;
            }
        }
    }

    Patient* p = new Patient(id, name, dob, address, phone);

    // Create empty medical dossier
    DossierMedical* dossier = new DossierMedical(p);
    p->setDossier(dossier);

    patients.push_back(p);
    return id;
}
