#include "Administratif.h"

using namespace std;

Administratif::Administratif(int id, string nom, string prenom, 
                             string login, string mdp, double salaire)
    : Employe(id, nom, prenom, login, mdp, "Administratif", salaire) {
}

Administratif::~Administratif() {
}

string Administratif::getPermissions() const {
    return "ADMIN";
}

string Administratif::afficher() const {
    return to_string(id) + ";" + nom + ";" + prenom + ";" + 
           login + ";" + motDePasse + ";" + to_string(salaire);
}