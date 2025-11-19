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
