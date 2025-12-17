#ifndef ETUDIANT_H
#define ETUDIANT_H

#include "Personne.h"
#include <string>
using namespace std;

class Etudiant : public Personne {
private:
    int matricule;
    string classe;
    string filiere;
    int heuresAbsence;

public:
    // Constructeur
    Etudiant(int id, string nom, string prenom, int matricule);

    // Destructeur
    ~Etudiant();

    // Getters
    int getMatricule() const;
    int getHeuresAbsence() const;

    // Méthodes
    void ajouterAbsence(int heures);
    void afficher() const;
};

#endif
