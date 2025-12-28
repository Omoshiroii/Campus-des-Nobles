#ifndef ADMINISTRATIF_H
#define ADMINISTRATIF_H

#include "Employe.h"
#include <string>

using namespace std;

class Administratif : public Employe {
public:
    // Constructor
    Administratif(int id, string nom, string prenom, 
                  string login, string mdp, 
                  double salaire = 0.0);
    
    // Destructor
    ~Administratif();
    
    // Override from Personne
    string getPermissions() const override;
    string afficher() const override;
};

#endif // ADMINISTRATIF_H