#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <numeric>

using namespace std;

// ================ Classe Personne (abstraite) ================
class Personne {
protected:
    string nom;
    string prenom;
    string cin;

public:
    Personne(string n = "", string p = "", string id = "")
        : nom(n), prenom(p), cin(id) {}

    virtual ~Personne() = default;

    // Méthode abstraite → classe abstraite
    virtual void afficher() const = 0;

    // Getters
    string getNom() const { return nom; }
    string getPrenom() const { return prenom; }
    string getCIN() const { return cin; }

    // Setters
    void setNom(const string& n) { nom = n; }
    void setPrenom(const string& p) { prenom = p; }
    void setCIN(const string& id) { cin = id; }

    // Surcharge de ==
    bool operator==(const Personne& autre) const {
        return cin == autre.cin;
    }

    // Surcharge de <<
    friend ostream& operator<<(ostream& os, const Personne& p);
};

ostream& operator<<(ostream& os, const Personne& p) {
    os << p.prenom << " " << p.nom << " (CIN: " << p.cin << ")";
    return os;
}

// ================ Classe Etudiant ================
class Etudiant : public Personne {
private:
    string matricule;
    map<string, vector<float>> notesParMatiere;

public:
    Etudiant(string n = "", string p = "", string id = "", string mat = "")
        : Personne(n, p, id), matricule(mat) {}

    // Implémentation obligatoire
    void afficher() const override {
        cout << "Étudiant: " << prenom << " " << nom
             << " | CIN: " << cin
             << " | Matricule: " << matricule << "\n";
    }

    // Getters / Setters
    string getMatricule() const { return matricule; }
    void setMatricule(const string& m) { matricule = m; }

    // === Méthodes fonctionnelles (à compléter en Décembre) ===
    void ajouterNote(const string& matiere, float note) {
        // À améliorer : validation, exceptions

    }

    float moyenneParMatiere(const string& matiere) const {

    }

    float moyenneGenerale() const {

    }

    const map<string, vector<float>>& getNotes() const {
        return notesParMatiere;
    }

    // === STUB DE LOGIN (non exigé, mais inclus) ===
    bool login(const string& username, const string& password) {
        // Vous remplirez ou supprimerez cette méthode plus tard
        return true; // stub: succès par défaut
    }

    // Surcharge de ==
    bool operator==(const Etudiant& autre) const {
        return matricule == autre.matricule;
    }

    // Surcharge de <<
    friend ostream& operator<<(ostream& os, const Etudiant& e);
};

ostream& operator<<(ostream& os, const Etudiant& e) {
    os << "Étudiant: " << e.prenom << " " << e.nom
       << " | Matricule: " << e.matricule;
    return os;
}

