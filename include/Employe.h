#ifndef EMPLOYE_H
#define EMPLOYE_H

#include "Personne.h"
#include <string>

using namespace std;

class Employe : public Personne {
protected:
    string poste;
    double salaire;

public:
    // Constructor
    Employe(int id, string nom, string prenom, 
            string login, string mdp, 
            string poste, double salaire = 0.0);
    
    // Destructor
    virtual ~Employe();
    
    // Getters
    double getSalaire() const;
    string getPoste() const;
    
    // Setters
    void setSalaire(double s);
    
    // Methods
    void saisie();
};

#endif // EMPLOYE_H