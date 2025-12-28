#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H

#include "Employe.h"
#include <vector>
#include <string>

using namespace std;

class Enseignant : public Employe {
private:
    vector<int> modules;

public:
    // Constructors
    Enseignant(int id, string nom, string prenom, 
               vector<int> idmods, string login, 
               string mdp, double salaire = 0.0);
    
    // Constructor for single module (backward compatibility)
    Enseignant(int id, string nom, string prenom, 
               int idmod, string login, 
               string mdp, double salaire = 0.0);
    
    // Destructor
    ~Enseignant();
    
    // Override from Personne
    string getPermissions() const override;
    string afficher() const override;
    
    // Getters
    vector<int>& getModules();
    int getModule(); // For backward compatibility
    
    // Setters
    void setModule(int m);
    
    // Module management
    void ajouterModule(int idModule);
    void supprimerModule(int idModule);
};

#endif // ENSEIGNANT_H