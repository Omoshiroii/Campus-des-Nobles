#include "Employe.h"
#include <iostream>

using namespace std;

Employe::Employe(int id, string nom, string prenom, 
                 string login, string mdp, 
                 string poste, double salaire)
    : Personne(id, nom, prenom, login, mdp), 
      poste(poste), salaire(salaire) {
}

Employe::~Employe() {
}

double Employe::getSalaire() const {
    return salaire;
}

string Employe::getPoste() const {
    return poste;
}

void Employe::setSalaire(double s) {
    salaire = s;
}

void Employe::saisie() {
    cout << "\nSaisie du salaire: ";
    cin >> salaire;
    while(salaire < 0) {
        cout << "Salaire invalide. Veuillez entrer un salaire positif: ";
        cin >> salaire;
    }
}