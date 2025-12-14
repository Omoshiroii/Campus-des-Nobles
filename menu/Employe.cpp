#include "Employe.h"
#include <iostream>

using namespace std;

Employe::Employe(string n, string p, int i, string dep)
    : Personne(n, p)  // call base class constructor
{
    id = i;
    departement = dep;
}

Employe::~Employe() {
    // empty — but virtual destructor is important for abstract classes
}

void Employe::afficher() {
    cout << "Employe: " << nom << " " << prenom 
              << " (ID: " << id << ", Dept: " << departement << ")" << endl;
}
