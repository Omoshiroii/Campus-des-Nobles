#include "Etablissement.h"
#include <iostream>
using namespace std;
class Etablissement {
private:
    vector<shared_ptr<Personne>> personnes;
    vector<shared_ptr<Module>> modules;

public:
//Ajoute une personne à l'établissement
void Etablissement::ajouterPersonne(const shared_ptr<Personne>& personne) {
    personnes.push_back(personne);
}
  //Recherche une personne par son ID
shared_ptr<Personne> Etablissement::rechercherParId(int id) const {
    for (const auto& personne : personnes) {
        if (personne->getId() == id) {
            return personne;
        }
    }
    return nullptr;
}
  // Enregistrement d'une note
void Etablissement::enregistrerNote(int idEtudiant, int idModule, float note) {
    cout << "[STUB] enregistrerNote() appelee" << endl;
}
//Enregistrement d'une absence
void Etablissement::enregistrerAbsence(int idEtudiant, int heures) {
    cout << "[STUB] enregistrerAbsence() appelee" << endl;
}