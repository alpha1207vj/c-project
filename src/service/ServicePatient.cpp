#include "service/ServicePatient.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <iostream>

// --- other existing methods like creerPatient, supprimerPatient, etc ---

bool ServicePatient::exportToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if(!file.is_open()) return false;

    for(Patient* p : patients) {
        std::time_t tt = std::chrono::system_clock::to_time_t(p->getDateNaissance());
        std::tm tm = *std::localtime(&tt);
        char date[11];
        std::strftime(date, sizeof(date), "%Y-%m-%d", &tm);

        file << p->getId() << "," << p->getNom() << "," << date
             << "," << p->getAdresse() << "," << p->getTelephone() << "\n";
    }

    file.close();
    return true;
}

bool ServicePatient::importFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if(!file.is_open()) return false;

    std::string line;
    while(std::getline(file, line)) {
        std::istringstream ss(line);
        std::string idStr, nom, dateStr, adresse, telephone;

        std::getline(ss, idStr, ',');
        std::getline(ss, nom, ',');
        std::getline(ss, dateStr, ',');
        std::getline(ss, adresse, ',');
        std::getline(ss, telephone, ',');

        std::tm tm = {};
        std::istringstream ssdate(dateStr);
        ssdate >> std::get_time(&tm, "%Y-%m-%d");
        auto dob = std::chrono::system_clock::from_time_t(std::mktime(&tm));

        int id = std::stoi(idStr);
        Patient* p = new Patient(id, nom, dob, adresse, telephone);
        DossierMedical* dossier = new DossierMedical(p);
        p->setDossier(dossier);

        patients.push_back(p);
        if(id >= nextId) nextId = id + 1;
    }

    file.close();
    return true;
}




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
