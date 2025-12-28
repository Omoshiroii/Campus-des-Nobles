#include "Etudiant.h"

using namespace std;

Etudiant::Etudiant(int id, string nom, string prenom, 
                   string login, string mdp, int groupe)
    : Personne(id, nom, prenom, login, mdp), groupe(groupe) {
}

Etudiant::~Etudiant() {
}

string Etudiant::getPermissions() const {
    return "ETUDIANT";
}

int Etudiant::getGroupe() const {
    return groupe;
}

vector<string>& Etudiant::getAbsences() {
    return absences;
}

vector<string>& Etudiant::getWarnings() {
    return warnings;
}

void Etudiant::setGroupe(int g) {
    groupe = g;
}

// Gestion des absences
void Etudiant::ajouterAbsence(const string &absence) {
    absences.push_back(absence);
}

void Etudiant::supprimerAbsence(int index) {
    if(index >= 0 && index < absences.size()) {
        absences.erase(absences.begin() + index);
    }
}

// Gestion des avertissements
void Etudiant::ajouterWarning(const string &warning) {
    warnings.push_back(warning);
}

void Etudiant::supprimerWarning(int index) {
    if(index >= 0 && index < warnings.size()) {
        warnings.erase(warnings.begin() + index);
    }
}

string Etudiant::afficher() const {
    string result = to_string(id) + ";" + nom + ";" + prenom + ";" + 
                    login + ";" + motDePasse + ";" + to_string(groupe);

    // Add absences
    result += ";";
    for(size_t i = 0; i < absences.size(); i++) {
        result += absences[i];
        if(i < absences.size() - 1) 
            result += "|";
    }

    // Add warnings
    result += ";";
    for(size_t i = 0; i < warnings.size(); i++) {
        result += warnings[i];
        if(i < warnings.size() - 1) 
            result += "|";
    }

    return result;
}