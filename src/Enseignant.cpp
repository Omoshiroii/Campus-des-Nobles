#include "Enseignant.h"
#include <iostream>

using namespace std;

Enseignant::Enseignant(int id, string nom, string prenom, 
                       vector<int> idmods, string login, 
                       string mdp, double salaire)
    : Employe(id, nom, prenom, login, mdp, "Enseignant", salaire), 
      modules(idmods) {
}

Enseignant::Enseignant(int id, string nom, string prenom, 
                       int idmod, string login, 
                       string mdp, double salaire)
    : Employe(id, nom, prenom, login, mdp, "Enseignant", salaire) {
    modules.push_back(idmod);
}

Enseignant::~Enseignant() {
}

string Enseignant::getPermissions() const {
    return "ENSEIGNANT";
}

vector<int>& Enseignant::getModules() {
    return modules;
}

int Enseignant::getModule() {
    return modules.empty() ? 0 : modules[0];
}

void Enseignant::setModule(int m) {
    if(modules.empty()) 
        modules.push_back(m);
    else 
        modules[0] = m;
}

void Enseignant::ajouterModule(int idModule) {
    // Check if module already exists
    for(auto &m : modules) {
        if(m == idModule) {
            cout << "\nCe module est deja assigne a cet enseignant.\n";
            return;
        }
    }
    modules.push_back(idModule);
    cout << "\nModule ajoute avec succes.\n";
}

void Enseignant::supprimerModule(int idModule) {
    for(auto it = modules.begin(); it != modules.end(); ++it) {
        if(*it == idModule) {
            modules.erase(it);
            cout << "\nModule supprime avec succes.\n";
            return;
        }
    }
    cout << "\nModule non trouve.\n";
}

string Enseignant::afficher() const {
    string result = to_string(id) + ";" + nom + ";" + prenom + ";";
    
    // Add modules separated by |
    for(size_t i = 0; i < modules.size(); i++) {
        result += to_string(modules[i]);
        if(i < modules.size() - 1) 
            result += "|";
    }
    
    result += ";" + login + ";" + motDePasse + ";" + to_string(salaire);
    return result;
}