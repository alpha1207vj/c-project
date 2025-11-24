#include "service/ServicePatient.h"
#include "console/Utils.h"
#include "model/ProfessionnelSante.h"
#include "service/ServiceUtilisateur.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <iostream>

// =========================
//   EXPORT CSV
// =========================

bool ServicePatient::exportToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "PatientID;Name;DOB;Address;Phone;Antecedents;Consultations\n";

    for (Patient* p : patients) {
        file << p->getId() << ";"
             << p->getNom() << ";"
             << Utils::formatDate(p->getDateNaissance()) << ";"
             << p->getAdresse() << ";"
             << p->getTelephone() << ";";

        // Antecedents
        std::string antecedentsStr;
        for (auto a : p->getDossier()->getAntecedents()) {
            if (!antecedentsStr.empty()) antecedentsStr += ",";
            antecedentsStr += a->getDescription() + "|" + Utils::formatDate(a->getDate());
        }
        file << "\"" << antecedentsStr << "\";";

        // Consultations
        std::string consultationsStr;
        for (auto c : p->getDossier()->getConsultations()) {
            if (!consultationsStr.empty()) consultationsStr += ",";
            consultationsStr += std::to_string(c->getId()) + "|" +
                                Utils::formatDate(c->getDate()) + "|" +
                                c->getMotif() + "|" +
                                c->getProfessionnel()->getNomUtilisateur();
        }
        file << "\"" << consultationsStr << "\"\n";
    }

    return true;
}

// =========================
//   IMPORT CSV
// =========================

bool ServicePatient::importFromCSV(const std::string& filename, ServiceUtilisateur& serviceUser) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, dobStr, address, phone, antecedentsStr, consultationsStr;

        std::getline(ss, idStr, ';');
        std::getline(ss, name, ';');
        std::getline(ss, dobStr, ';');
        std::getline(ss, address, ';');
        std::getline(ss, phone, ';');
        std::getline(ss, antecedentsStr, ';');
        std::getline(ss, consultationsStr, ';');

        int id = std::stoi(idStr);
        auto dob = Utils::parseDate(dobStr);

        Patient* p = new Patient(id, name, dob, address, phone);
        DossierMedical* dossier = new DossierMedical(p);
        p->setDossier(dossier);

        // === Antecedents ===
        if (antecedentsStr.size() > 2) {
            antecedentsStr = antecedentsStr.substr(1, antecedentsStr.size() - 2); // remove quotes
            std::stringstream antSS(antecedentsStr);

            std::string entry;
            while (std::getline(antSS, entry, ',')) {
                std::stringstream fields(entry);
                std::string desc, dateStr;
                std::getline(fields, desc, '|');
                std::getline(fields, dateStr, '|');

                dossier->ajouterAntecedent(
                    new Antecedent(
                        dossier->getAntecedents().size() + 1,
                        desc,
                        Utils::parseDate(dateStr),
                        dossier
                    )
                );
            }
        }

        // === Consultations ===
        if (consultationsStr.size() > 2) {
            consultationsStr = consultationsStr.substr(1, consultationsStr.size() - 2);
            std::stringstream consSS(consultationsStr);

            std::string entry;
            while (std::getline(consSS, entry, ',')) {
                std::stringstream fields(entry);
                std::string idCStr, dateStr, motif, profName;

                std::getline(fields, idCStr, '|');
                std::getline(fields, dateStr, '|');
                std::getline(fields, motif, '|');
                std::getline(fields, profName, '|');

                Utilisateur* u = nullptr;
for (auto usr : serviceUser.getUtilisateurs()) {
    if (usr->getNomUtilisateur() == profName) { // compare strings
        u = usr;
        break;
    }
}
ProfessionnelSante* prof = dynamic_cast<ProfessionnelSante*>(u);
if (!prof) continue;
                dossier->ajouterConsultation(
                    new Consultation(
                        std::stoi(idCStr),
                        Utils::parseDate(dateStr),
                        p,
                        prof,
                        motif,
                        "",
                        dossier
                    )
                );
            }
        }

        patients.push_back(p);
    }
    int maxId = 0;
for (auto p : patients) {
    if (p->getId() > maxId)
        maxId = p->getId();
}
nextId = maxId + 1;
    return true;
}



// =========================
//   METHODES DIVERSES
// =========================

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
        std::cout << "Patient: " << p->getNom()
                  << ", Adresse: " << p->getAdresse()
                  << std::endl;
    }
}

int ServicePatient::creerPatient(const std::string& name,
                                 const std::chrono::system_clock::time_point& dob,
                                 const std::string& address,
                                 const std::string& phone) {

    int id = nextId++;

    Patient* p = new Patient(id, name, dob, address, phone);

    DossierMedical* dossier = new DossierMedical(p);
    p->setDossier(dossier);

    patients.push_back(p);
    return id;
}
// ServiceUtilisateur.cpp
Utilisateur* ServiceUtilisateur::trouverUtilisateurParNom(const std::string& nom) {
    for (auto u : utilisateurs) {
        if (u->getNomUtilisateur() == nom)
            return u;
    }
    return nullptr;
}
