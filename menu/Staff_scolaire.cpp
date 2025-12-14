#include "Staff_scolaire.h"
#include <iostream>

using namespace std;

Staff_scolaire::Staff_scolaire(string n, string p, int i, string dep, string fonc, bool perm)
    : Employe(n, p, i, dep)
{
    fonction = fonc;
    estPermanent = perm;
}

Staff_scolaire::~Staff_scolaire() {}

void Staff_scolaire::saisir_note() {
    // stub — staff don’t grade.
}

void Staff_scolaire::enregistrement_absence() {
    // stub for now: empty
}

void Staff_scolaire::afficher() {
    cout << "Staff: " << nom << " " << prenom 
              << " | Fonction: " << fonction 
              << " | Permanent: " << (estPermanent ? "Oui" : "Non") 
              << endl;
}
