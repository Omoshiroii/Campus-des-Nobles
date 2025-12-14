#ifndef PROFESSEUR_H
#define PROFESSEUR_H

#include "Employe.h"
#include <string>

using namespace std;

class Professeur : public Employe {
private:
    string specialite;
    int nbHeuresCours;

public:
    Professeur(string n, string p, int i, string dep,
               string specia, int heures);
    ~Professeur();

    void saisir_note() override;
    void enregistrement_absence() override;
    void afficher() override;
};

#endif // PROFESSEUR_H
