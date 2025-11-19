#include "service/ServiceConsultation.h"
#include "model/DossierMedical.h"
#include <iostream>
#include <algorithm>

bool ServiceConsultation::programmerConsultation(Consultation* c) {
    for (auto existing : consultations) {
        if (existing->getId() == c->getId()) {
            std::cout << "Error: Consultation ID " << c->getId() << " already exists.\n";
            return false;
        }
    }
    consultations.push_back(c);
    std::cout << "Consultation scheduled successfully (ID: " << c->getId() << ").\n";
    return true;
}

void ServiceConsultation::modifierConsultation(int id, const std::string& motif, const std::string& observations) {
    bool found = false;
    for (auto c : consultations) {
        if (c->getId() == id) {
            c->setMotif(motif);
            c->setObservations(observations);
            found = true;
            std::cout << "Consultation (ID: " << id << ") modified successfully.\n";
            break;
        }
    }
    if (!found) {
        std::cout << "Error: Consultation with ID " << id << " not found. Nothing was modified.\n";
    }
}

void ServiceConsultation::annulerConsultation(int id) {
    bool found = false;
    for (auto it = consultations.begin(); it != consultations.end(); ++it) {
        if ((*it)->getId() == id) {
            Consultation* c = *it;  // save pointer

            // Remove from the patient's dossier if it exists
            if (c->getPatient() && c->getPatient()->getDossier()) {
                auto& consList = c->getPatient()->getDossier()->getConsultations();
                consList.erase(std::remove(consList.begin(), consList.end(), c), consList.end());
            }

            consultations.erase(it);  // remove from service list
            delete c;                 // free memory

            found = true;
            std::cout << "Consultation (ID: " << id << ") canceled successfully.\n";
            break;
        }
    }
    if (!found) {
        std::cout << "Error: Consultation with ID " << id << " not found. Nothing was canceled.\n";
    }
}


std::vector<Consultation*> ServiceConsultation::listerConsultationsParPatient(Patient* p) const {
    std::vector<Consultation*> result;
    for (auto c : consultations) {
        if (c->getPatient() == p)
            result.push_back(c);
    }
    return result;
}

std::vector<Consultation*> ServiceConsultation::listerConsultationsParProfessionnel(ProfessionnelSante* prof) const {
    std::vector<Consultation*> result;
    for (auto c : consultations) {
        if (c->getProfessionnel() == prof)
            result.push_back(c);
    }
    return result;
}
