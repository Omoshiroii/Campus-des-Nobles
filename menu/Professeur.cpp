#include "Professeur.h"
#include <iostream>

using namespace std;

Professeur::Professeur(string n, string p, int i, string dep,
                       string specia, int heures)
    : Employe(n, p, i, dep)
{
    specialite = spec;
    nbHeuresCours = heures;
}

Professeur::~Professeur() {}

void Professeur::saisir_note() {
    // stub — empty as requested
}

void Professeur::enregistrement_absence() {
    // stub — empty
}

void Professeur::afficher() {
    cout << "Professeur: " << nom << " " << prenom 
              << " | Specialite: " << specialite 
              << " | Heures: " << nbHeuresCours << endl;
}
