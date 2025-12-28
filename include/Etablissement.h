#ifndef ETABLISSEMENT_H
#define ETABLISSEMENT_H

#include "Etudiant.h"
#include "Enseignant.h"
#include "Administratif.h"
#include "Note.h"
#include "Module.h"
#include "Groupe.h"
#include <vector>
#include <string>

class Etablissement {
private:
    std::vector<Etudiant> etudiants;
    std::vector<Enseignant> enseignants;
    std::vector<Administratif> admins;
    std::vector<Note> notes;
    std::vector<Module> modules;
    std::vector<Groupe> groupes;

public:
    // Constructor & Destructor
    Etablissement();
    ~Etablissement();
    
    // File operations
    void charger();
    void sauvegarder();
    
    // Etudiant operations
    void etudiantConsulterAbsences(Etudiant &e);
    void etudiantConsulterWarnings(Etudiant &e);
    
    // Enseignant operations
    void enseignantAjouterNote(Enseignant &e);
    void enseignantGererModules(Enseignant &e);
    
    // Admin operations
    void adminAjouterEtudiant();
    void adminGererAbsences();
    void adminGererWarnings();
    
    // Helper methods
    void ajouterNote(int idEtudiant, int idModule, float valeur);
};

#endif // ETABLISSEMENT_H