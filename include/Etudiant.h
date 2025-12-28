#ifndef ETUDIANT_H
#define ETUDIANT_H

#include "Personne.h"
#include <vector>
#include <string>

class Etudiant : public Personne {
private:
    int groupe;
    std::vector<std::string> absences;  // Format: "date;module"
    std::vector<std::string> warnings;  // Format: "date;raison"

public:
    // Constructor
    Etudiant(int id, std::string nom, std::string prenom, 
             std::string login, std::string mdp, int groupe);
    
    // Destructor
    ~Etudiant();
    
    // Override from Personne
    std::string getPermissions() const override;
    std::string afficher() const override;
    
    // Getters
    int getGroupe() const;
    std::vector<std::string>& getAbsences();
    std::vector<std::string>& getWarnings();
    
    // Setters
    void setGroupe(int g);
    
    // Gestion des absences
    void ajouterAbsence(const std::string &absence);
    void supprimerAbsence(int index);
    
    // Gestion des avertissements
    void ajouterWarning(const std::string &warning);
    void supprimerWarning(int index);
};

#endif // ETUDIANT_H