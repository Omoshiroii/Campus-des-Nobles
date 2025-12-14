#ifndef EMPLOYE_H
#define EMPLOYE_H

#include "Personne.h"
#include <string>

using namespace std;

/*example class personne has -nom, -prenom as protected variables
constructeur/destructeur
methods pure virtual *afficher* → abstract
pour que class emplye herite de la class personne */

class Employe : public Personne {
private:
    int id;
    string departement;

public:
    Employe(string n, string p, int i, string dep);
    virtual ~Employe();

    // Pure virtual methods → force implementation in subclasses
    virtual void saisir_note() = 0;
    virtual void enregistrement_absence() = 0;

    // Virtual (but not pure) — can be overridden
    virtual void afficher();
};

#endif // EMPLOYE_H
