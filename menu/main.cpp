 // Campus des nobles - Alpha - Projet C++ Programmation Orientée Objet
// Taha Zerrad, Salsabil Benhnich, Oussama El Attabi, Rania Mahfoud, Badr Al Fezghari
// Bases de donnéees représentées par des fichiers .txt

// !! pour le test initial, on peut se connecter avec l'admin (Nom d'utilisateur: abcd, Mot de passe: 1234)
// !! pour le test initial, on peut quitter le programme dans le login en entrant (Nom d'utilisateur: 0)

// NOUVEAUX UPDATES:
    // 1. Surcharge de l'opérateur + pour la classe Note:
        // On peut ajouter une valeur à la valeur d'une note (Note + float)
        // On peut ajouter la valeur d'une note à la valeur une autre (Note + Note)
    // 2. Surcharge de l'opérateur = pour la classe Note:
        // On peut affecter une valeur à la valeur d'une note (Note = float)
        // On peut affecter la valeur d'une note à la valeur une autre (Note = Note)
    // 3. Empechement d'ajouter une note à un étudiant qui a déja une note.
        // Si l'étudiant a déjà une note dans ce module, on affiche "Essayez de modifier"
    // 4. Modification d'une note.
        // Enseignant peut modifier la note d'un étudiant dans le module
    // 5. Surcharge de l'opérateur << pour la classe Note:
        // Pour afficher un objet de classe Note, on affiche sa valeur
    // 6. Calcul de moyenne par groupe.
        // Selon son module, l'enseignant peut calculer la moyenne des notes d'un groupe.

/* Références: 1) 132, 2) 140, 3) 410, 4) 530, 5) 153, 6) 546. */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// Helper simple: lecture d'entier depuis la console avec validation
// (utilise getline + stoi pour eviter les desordres de cin)
int lireInt(const string &invite) {
    while (true) {
        cout << invite;
        string ligne;
        if(!std::getline(cin, ligne)) {
            // EOF or error
            exit(0);
        }
        try {
            size_t pos;
            int val = stoi(ligne, &pos);
            if (pos != ligne.size()) throw invalid_argument("extra");
            return val;
        } catch (...) {
            cout << "Entree invalide. Reessayez." << endl;
        }
    }
}

// Lit une ligne non vide depuis l'entree standard (prompt affiché)
string lireString(const string &invite) {
    string s;
    while (true) {
        cout << invite;
        if(!std::getline(cin, s)) exit(0);
        if(s.size() == 0) {
            cout << "Entree vide. Reessayez." << endl;
            continue;
        }
        return s;
    }
}

// Lit un flottant avec validation
float lireFloat(const string &invite) {
    while (true) {
        cout << invite;
        string ligne;
        if(!std::getline(cin, ligne)) exit(0);
        try {
            size_t pos;
            float val = stof(ligne, &pos);
            if (pos != ligne.size()) throw invalid_argument("extra");
            return val;
        } catch (...) {
            cout << "Entree invalide. Reessayez." << endl;
        }
    }
}

class Personne {
protected:
    int id;
    string nom;
    string prenom;
    string numTel;
    string dateNaissance;
    string login;
    string motDePasse;
public:
    Personne(int id, string nom, string prenom, string numTel, string dateNaissance, string login, string mdp)
    : id(id), nom(nom), prenom(prenom), numTel(numTel), dateNaissance(dateNaissance), login(login), motDePasse(mdp) { }
    virtual ~Personne() { }

    virtual string getPermissions() const = 0;
    int getId() const { return id; }
    string getNom() const { return nom; }
    string getPrenom() const { return prenom; }
    string getNumTel() const { return numTel; }
    string getDateNaissance() const { return dateNaissance; }
    string getLogin() const { return login; }
    string getMotDePasse() const { return motDePasse; }

    void setNom(const string &n) { nom = n; }
    void setPrenom(const string &p) { prenom = p; }
    void setNumTel(const string &nt) { numTel = nt; }
    void setDateNaissance(const string &dn) { dateNaissance = dn; }
    void setLogin(const string &l) { login = l; }
    void setMdp(const string &m) { motDePasse = m; }

    virtual string afficher() const = 0;
};

class Etudiant : public Personne {
private:
    int groupe;
    int salleId;
    float moyenne;
    int nbAbsences;
    int nbAvertissements;
public:
    Etudiant(int id, string nom, string prenom, string numTel, string dateNaissance, string login, string mdp, int groupe, float moyenne, int nbAbsences, int nbAvertissements, int salleId = 0)
    : Personne(id, nom, prenom, numTel, dateNaissance, login, mdp), groupe(groupe), salleId(salleId), moyenne(moyenne), nbAbsences(nbAbsences), nbAvertissements(nbAvertissements) { }

    string getPermissions() const override { return "ETUDIANT"; }
    int getGroupe() const { return groupe; }
    int getSalleId() const { return salleId; }
    float getMoyenne() const { return moyenne; }
    int getNbAbsences() const { return nbAbsences; }
    int getNbAvertissements() const { return nbAvertissements; }

    void setGroupe(int g) { groupe = g; }
    void setSalleId(int s) { salleId = s; }
    void setMoyenne(float m) { moyenne = m; }
    void setNbAbsences(int a) { nbAbsences = a; }
    void setNbAvertissements(int av) { nbAvertissements = av; }

    string afficher() const override {
        return to_string(id) + ";" + nom + ";" + prenom + ";" + numTel + ";" + dateNaissance + ";" + login + ";" + motDePasse + ";" + to_string(groupe) + ";" + to_string(moyenne) + ";" + to_string(nbAbsences) + ";" + to_string(nbAvertissements) + ";" + to_string(salleId);
    }
};

class Employe : public Personne {
protected:
    string poste;
public:
    Employe(int id, string nom, string prenom, string login, string mdp, string poste)
    : Personne(id, nom, prenom, "", "", login, mdp), poste(poste) { }
};

class Enseignant : public Employe {
private:
    int module;
public:
    Enseignant(int id, string nom, string prenom, int idmod, string login, string mdp)
    : Employe(id, nom, prenom, login, mdp, "Enseignant"), module(idmod) { }

    string getPermissions() const override { return "ENSEIGNANT"; }
    int getModule() { return module; }

    int getModule() const { return module; }

    void setModule(int m) { module =  m; }

    string afficher() const override {
        return to_string(id) + ";" + nom + ";" + prenom + ";" + to_string(module) + ";" + login + ";" + motDePasse;
    }
};

class Administratif : public Employe {
public:
    Administratif(int id, string nom, string prenom, string login, string mdp)
    : Employe(id, nom, prenom, login, mdp, "Administratif") { }

    string getPermissions() const override { return "ADMIN"; }

    string afficher() const override {
        return to_string(id) + ";" + nom + ";" + prenom + ";" + login + ";" + motDePasse;
    }
};

class Parent : public Personne {
private:
    int idEnfant;
public:
    Parent(int id, string nom, string prenom, string login, string mdp, int idEnfant)
    : Personne(id, nom, prenom, "", "", login, mdp), idEnfant(idEnfant) { }

    string getPermissions() const override { return "PARENT"; }
    int getIdEnfant() const { return idEnfant; }

    string afficher() const override {
        return to_string(id) + ";" + nom + ";" + prenom + ";" + login + ";" + motDePasse + ";" + to_string(idEnfant);
    }
};

class Note {
private:
    int idEtudiant;
    int idModule;
    float valeur;
    int coefficient;
public:
    Note(int idEtu, int idMod, float val, int coef = 1)
    : idEtudiant(idEtu), idModule(idMod), valeur(val), coefficient(coef) { }

    int getIdEtudiant() const { return idEtudiant; }
    int getIdModule() const { return idModule; }
    float getValeur() const { return valeur; }
    int getCoefficient() const { return coefficient; }

    string afficher() const {
        return to_string(idEtudiant) + ";" + to_string(idModule) + ";" + to_string(valeur) + ";" + to_string(coefficient);
    }

    Note operator+(const Note& N) {
        return Note(this->idEtudiant, this->idModule, this->valeur + N.valeur, this->coefficient);
    }

    Note operator+(const float n) {
        return Note(this->idEtudiant, this->idModule, this->valeur + n, this->coefficient);
    }

    Note& operator=(const Note& N) {
        if(this == &N){
            return *this;
        }
        this->valeur = N.valeur;
        return *this;
    }

    Note& operator=(const float n) {
        this->valeur = n;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Note& N) {
        os << N.valeur;
        return os;
    }
};

class Module {
private:
    int id;
    string nom;
public:
    Module(int i, string n)
    : id(i), nom(n) { }

    int getId() const { return id; }
    string getNom() const { return nom; }

    string afficher() const {
        return to_string(id) + ";" + nom;
    }
};

class Groupe {
private:
    int id;
    int effectif;
public:
    Groupe(int i, int e) : id(i), effectif(e) { }

    int getId() const { return id; }
    int getEffectif() const { return effectif; }

    void incrementer() { effectif++; }
    void decrementer() { effectif--; }

    string afficher() const {
        return to_string(id) + ";" + to_string(effectif);
    }
};

class Salle {
private:
    int id;
    int capacite;
    string nom;
public:
    Salle(int i, int c, string n)
    : id(i), capacite(c), nom(n) { }

    int getId() const { return id; }
    int getCapacite() const { return capacite; }
    string getNom() const { return nom; }

    void setCapacite(int c) { capacite = c; }
    void setNom(const string &n) { nom = n; }

    string afficher() const {
        return to_string(id) + ";" + to_string(capacite) + ";" + nom;
    }
};

class Etablissement {
private:
    vector<Etudiant> etudiants;
    vector<Enseignant> enseignants;
    vector<Administratif> admins;
    vector<Parent> parents;
    vector<Note> notes;
    vector<Module> modules;
    vector<Groupe> groupes;
    vector<Salle> salles;
    vector<pair<int,int>> absences; // pair<idEtudiant, totalHours>
    vector<pair<int,int>> avertissements; // pair<idEtudiant, count>
public:
    vector<Module> getModules() const { return modules; }

    string getNomModule(int idModule) const {
        for(const auto &m : modules) {
            if(m.getId() == idModule) return m.getNom();
        }
        return "Module inconnu";
    }

    // Salle Management Methods
    string getNomSalle(int idSalle) const {
        if(idSalle == 0) return "Non assignee";
        for(const auto &s : salles) {
            if(s.getId() == idSalle) return s.getNom();
        }
        return "Salle inconnue";
    }

    int capaciteSalle(int salleId) const {
        for(const auto &s : salles) {
            if(s.getId() == salleId) return s.getCapacite();
        }
        return 0;
    }

    int nombreEtudiantsDansSalle(int salleId) const {
        int count = 0;
        for(const auto &e : etudiants) {
            if(e.getSalleId() == salleId) count++;
        }
        return count;
    }

    bool assignerEtudiantASalle(int idEtudiant, int salleId) {
        // Find the student
        Etudiant* etu = nullptr;
        for(auto &e : etudiants) {
            if(e.getId() == idEtudiant) {
                etu = &e;
                break;
            }
        }
        if(!etu) {
            cout << "\nEtudiant introuvable.\n";
            return false;
        }

        // Find the salle
        Salle* salle = nullptr;
        for(auto &s : salles) {
            if(s.getId() == salleId) {
                salle = &s;
                break;
            }
        }
        if(!salle) {
            cout << "\nSalle introuvable.\n";
            return false;
        }

        // Check capacity
        int occuped = nombreEtudiantsDansSalle(salleId);
        if(occuped >= salle->getCapacite()) {
            cout << "\nErreur: La salle " << salle->getNom() << " est pleine (" << occuped << "/" << salle->getCapacite() << ").\n";
            return false;
        }

        // Assign
        etu->setSalleId(salleId);
        cout << "\nEtudiant assigne a la salle " << salle->getNom() << ".\n";
        return true;
    }

    void listerSalles() const {
        cout << "\n--- Liste des salles ---\n";
        if(salles.empty()) {
            cout << "Aucune salle disponible.\n";
            return;
        }
        for(const auto &s : salles) {
            int occuped = nombreEtudiantsDansSalle(s.getId());
            cout << left << setw(3) << s.getId() << " | " 
                 << left << setw(20) << s.getNom() 
                 << " | Occupation: " << occuped << "/" << s.getCapacite();
            if(occuped >= s.getCapacite()) cout << " [PLEINE]";
            else if(occuped >= s.getCapacite() * 0.9) cout << " [PRESQUE PLEINE]";
            cout << "\n";
        }
    }

    void ajouterSalle(){
        int id = (!salles.size()) ? 1 : salles.back().getId() + 1;
        int capacite = lireInt("\nCapacite de la salle: ");
        string nom = lireString("Nom de la salle: ");
        salles.emplace_back(id, capacite, nom);
        cout << "\nSalle ajoutee avec succes.\n";
    }

    void supprimerSalle(){
        int id = lireInt("\nID de la salle a supprimer: ");
        
        for(auto it = salles.begin(); it != salles.end(); ++it) {
            if(it->getId() == id) {
                int count = nombreEtudiantsDansSalle(id);
                if(count > 0) {
                    cout << "\nAttention: " << count << " etudiant(s) sont dans cette salle.\n";
                    cout << "Ils seront desassignes de la salle.\n";
                    for(auto &e : etudiants) {
                        if(e.getSalleId() == id) e.setSalleId(0);
                    }
                }
                salles.erase(it);
                cout << "\nSalle supprimee.\n";
                return;
            }
        }
        cout << "\nSalle introuvable.\n";
    }

    void modifierSalle(){
        int id = lireInt("\nID de la salle a modifier: ");
        
        for(auto &s : salles) {
            if(s.getId() == id) {
                int choix;
                do {
                    cout << "\n1. Modifier nom\n";
                    cout << "2. Modifier capacite\n";
                    cout << "0. Retour\n" << endl;
                    choix = lireInt("Choix: ");
                    
                    switch(choix) {
                        case 1: {
                            string newNom = lireString("\nNouveau nom: ");
                            s.setNom(newNom);
                            cout << "\nNom modifie.\n";
                            break;
                        }
                        case 2: {
                            int newCap = lireInt("\nNouvelle capacite: ");
                            int occuped = nombreEtudiantsDansSalle(id);
                            if(newCap < occuped) {
                                cout << "\nErreur: La nouvelle capacite (" << newCap 
                                     << ") ne peut pas etre inferieure au nombre d'etudiants actuels (" << occuped << ").\n";
                            } else {
                                s.setCapacite(newCap);
                                cout << "\nCapacite modifiee.\n";
                            }
                            break;
                        }
                    }
                } while(choix != 0);
                return;
            }
        }
        cout << "\nSalle introuvable.\n";
    }

    void voirEtudiantsDansSalle(){
        int salleId = lireInt("\nID de la salle: ");
        
        // Check if salle exists
        bool salleExists = false;
        string nomSalle;
        for(const auto &s : salles) {
            if(s.getId() == salleId) {
                salleExists = true;
                nomSalle = s.getNom();
                break;
            }
        }
        if(!salleExists) {
            cout << "\nSalle introuvable.\n";
            return;
        }

        cout << "\n--- Etudiants dans la salle " << nomSalle << " ---\n";
        bool found = false;
        for(const auto &e : etudiants) {
            if(e.getSalleId() == salleId) {
                cout << e.getId() << " - " << e.getNom() << " " << e.getPrenom() 
                     << " (Groupe " << e.getGroupe() << ")\n";
                found = true;
            }
        }
        if(!found) {
            cout << "Aucun etudiant dans cette salle.\n";
        }
    }

    void charger() {
        ifstream file;
        string ligne;

        file.open("salles.txt");
        if(file.is_open()) {
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token, nom;
            int id, capacite;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,token,';'); capacite = stoi(token);
            getline(ss,nom,';');

            salles.emplace_back(id, capacite, nom);
        }
        file.close();
        }

        file.open("groupes.txt");
        if(file.is_open()) {
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int id, effectif;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,token,';'); effectif = stoi(token);

            groupes.emplace_back(id, effectif);
        }
        file.close();
        }

        file.open("modules.txt");
        if(file.is_open()) {
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int id;
            string nom;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,nom,';');

            modules.emplace_back(id, nom);
        }
        file.close();
        }

        file.open("etudiants.txt");
        if(file.is_open()) {
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int id, groupe, nbAbsences, nbAvertissements, salleId;
            string nom, prenom, numTel, dateNaissance, login, mdp;
            float moyenne;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,nom,';');
            getline(ss,prenom,';');
            getline(ss,numTel,';');
            getline(ss,dateNaissance,';');
            getline(ss,login,';');
            getline(ss,mdp,';');
            getline(ss,token,';'); groupe = stoi(token);
            getline(ss,token,';'); moyenne = stof(token);
            getline(ss,token,';'); nbAbsences = stoi(token);
            getline(ss,token,';'); nbAvertissements = stoi(token);
            salleId = 0;
            if(getline(ss,token,';')) salleId = stoi(token);

            etudiants.emplace_back(id, nom, prenom, numTel, dateNaissance, login, mdp, groupe, moyenne, nbAbsences, nbAvertissements, salleId);
        }
        file.close();
        }

        file.open("enseignants.txt");
        if(file.is_open()) {
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int id,idmod;
            string nom, prenom, login, mdp;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,nom,';');
            getline(ss,prenom,';');
            getline(ss,token,';'); idmod = stoi(token);
            getline(ss,login,';');
            getline(ss,mdp,';');

            enseignants.emplace_back(id, nom, prenom, idmod, login, mdp);
        }
        file.close();
        }

        file.open("administratifs.txt");
        if(file.is_open()) {
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int id;
            string nom, prenom, login, mdp;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,nom,';');
            getline(ss,prenom,';');
            getline(ss,login,';');
            getline(ss,mdp,';');

            admins.emplace_back(id, nom, prenom, login, mdp);
        }
        file.close();
        }

        file.open("notes.txt");
        if(file.is_open()) {
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int idEtu, idMod;
            float note;
            int coef = 1;

            getline(ss,token,';'); idEtu = stoi(token);
            getline(ss,token,';'); idMod = stoi(token);
            getline(ss,token,';'); note = stof(token);
            if(getline(ss,token,';')) coef = stoi(token);

            notes.emplace_back(idEtu, idMod, note, coef);
        }
        file.close();
        }

        file.open("absences.txt");
        if(file.is_open()) {
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int idEtu, hours;
            getline(ss,token,';'); idEtu = stoi(token);
            getline(ss,token,';'); hours = stoi(token);
            absences.emplace_back(idEtu, hours);
        }
        file.close();
        }

        file.open("avertissements.txt");
        if(file.is_open()) {
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int idEtu, count;
            getline(ss,token,';'); idEtu = stoi(token);
            getline(ss,token,';'); count = stoi(token);
            avertissements.emplace_back(idEtu, count);
        }
        file.close();
        }

        file.open("parents.txt");
        if(file.is_open()) {
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int id, idEnfant;
            string nom, prenom, login, mdp;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,nom,';');
            getline(ss,prenom,';');
            getline(ss,login,';');
            getline(ss,mdp,';');
            getline(ss,token,';'); idEnfant = stoi(token);

            parents.emplace_back(id, nom, prenom, login, mdp, idEnfant);
        }
        file.close();
        }

        // !! pour le test initial, il existe trois modules
        if(!modules.size()){
            ofstream fichier;
            fichier.open("modules.txt");
            fichier << "1;POO" << endl;
            fichier << "2;Developpement Web" << endl;
            fichier << "3;Communication Pro" << endl;
            modules.emplace_back(1,"POO");
            modules.emplace_back(2,"Developpement Web");
            modules.emplace_back(3,"Communication Pro");
            fichier.close();
        }

        // Add default salles for testing
        if(!salles.size()){
            ofstream fichier;
            fichier.open("salles.txt");
            fichier << "1;30;Salle A101" << endl;
            fichier << "2;25;Salle B202" << endl;
            salles.emplace_back(1, 30, "Salle A101");
            salles.emplace_back(2, 25, "Salle B202");
            fichier.close();
        }

        // !! pour le test initial, il existe un admin (Nom d'utilisateur: abcd, Mot de passe: 1234)
        if(!admins.size()){
            ofstream fichier;
            fichier.open("administratifs.txt");
            fichier << "201;Test;Admin;abcd;1234" << endl;
            admins.emplace_back(201, "Test", "Admin", "abcd", "1234");
            fichier.close();
        }

        // Test parent (Nom d'utilisateur: parent1, Mot de passe: 5555, child ID: 1)
        if(!parents.size()){
            ofstream fichier;
            fichier.open("parents.txt");
            fichier << "301;Doe;Parent;parent1;5555;1" << endl;
            parents.emplace_back(301, "Doe", "Parent", "parent1", "5555", 1);
            fichier.close();
        }

        // Defaults for testing: ensure at least one group, some students and teachers
        if(!groupes.size()){
            ofstream fichier;
            fichier.open("groupes.txt");
            fichier << "1;2" << endl;
            groupes.emplace_back(1,2);
            fichier.close();
        }

        if(!etudiants.size()){
            ofstream fichier;
            fichier.open("etudiants.txt");
            // Format: id;nom;prenom;numTel;dateNaissance;login;mdp;groupe;moyenne;nbAbsences;nbAvertissements;salleId
            fichier << "1;Doe;John;0000;2000-01-01;stu1;1111;1;0;0;0;0" << endl;
            fichier << "2;Smith;Alice;0000;2000-01-02;stu2;2222;1;0;0;0;0" << endl;
            etudiants.emplace_back(1, "Doe", "John", "0000", "2000-01-01", "stu1", "1111", 1, 0.0f, 0, 0, 0);
            etudiants.emplace_back(2, "Smith", "Alice", "0000", "2000-01-02", "stu2", "2222", 1, 0.0f, 0, 0, 0);
            fichier.close();
        }

        if(!enseignants.size()){
            ofstream fichier;
            fichier.open("enseignants.txt");
            fichier << "101;Prof;Alpha;1;prof1;3333" << endl;
            fichier << "102;Prof;Beta;2;prof2;4444" << endl;
            enseignants.emplace_back(101, "Prof", "Alpha", 1, "prof1", "3333");
            enseignants.emplace_back(102, "Prof", "Beta", 2, "prof2", "4444");
            fichier.close();
        }
    }

    void sauvegarder() {
        ofstream file;

        file.open("salles.txt");
        for(auto &s : salles) { file << s.afficher() << endl; }
        file.close();

        file.open("groupes.txt");
        for(auto &g : groupes) { file << g.afficher() << endl; }
        file.close();

        file.open("modules.txt");
        for(auto &m : modules) { file << m.afficher() << endl; }
        file.close();

        file.open("etudiants.txt");
        for(auto &e : etudiants) { file << e.afficher() << endl; }
        file.close();

        file.open("enseignants.txt");
        for(auto &ens : enseignants) { file << ens.afficher() << endl; }
        file.close();

        file.open("administratifs.txt");
        for(auto &a : admins) { file << a.afficher() << endl; }
        file.close();

        file.open("parents.txt");
        for(auto &p : parents) { file << p.afficher() << endl; }
        file.close();

        file.open("notes.txt");
        if(file.is_open()){
        for(auto &n : notes) {
            file << n.afficher() << endl;
        }
        file.close();
        } else cout << "Erreur: impossible d'ouvrir notes.txt pour ecriture\n";

        file.open("absences.txt");
        if(file.is_open()){
        for(auto &a : absences) {
            file << a.first << ";" << a.second << endl;
        }
        file.close();
        } else cout << "Erreur: impossible d'ouvrir absences.txt pour ecriture\n";

        file.open("avertissements.txt");
        if(file.is_open()){
        for(auto &a : avertissements) {
            file << a.first << ";" << a.second << endl;
        }
        file.close();
        } else cout << "Erreur: impossible d'ouvrir avertissements.txt pour ecriture\n";
    }

    Personne* authentifier(string login, string mdp) {
        for(auto &e : etudiants)
            if(e.getLogin() == login && e.getMotDePasse() == mdp)
                return &e;

        for(auto &ens : enseignants)
            if(ens.getLogin() == login && ens.getMotDePasse() == mdp)
                return &ens;

        for(auto &a : admins)
            if(a.getLogin() == login && a.getMotDePasse() == mdp)
                return &a;

        for(auto &p : parents)
            if(p.getLogin() == login && p.getMotDePasse() == mdp)
                return &p;

        return nullptr;
    }

    void ajouterNote(int idEtudiant, int idModule, float valeur) {
        bool existe1 = false;
        bool existe2 = false;
        bool existe3 = true;
        for(auto &e : etudiants) {
            if(e.getId() == idEtudiant) {
                existe1 = true;
                break;
            }
        }
        if(!existe1) {
            cout << "\nEtudiant introuvable.\n";
            return;
        }
        for(auto &m : modules) {
            if(m.getId() == idModule) {
                existe2 = true;
                break;
            }
        }
        if(!existe2) {
            cout << "\nModule introuvable.\n";
            return;
        }
        for(auto &n : notes) {
            if(n.getIdEtudiant() == idEtudiant && n.getIdModule() == idModule) {
                existe3 = false;
            }
        }
        if(!existe3) {
            cout << "\nEtudiant deja a une note dans ce module. Essayez de modifier la note.\n";
            return;
        }
        if(valeur > 20 || valeur < 0){
            cout << "\nNote invalide.\n";
            return;
        }
        notes.emplace_back(idEtudiant, idModule, valeur);
        cout << "\nNote ajoutee avec succes.\n";
        mettreAJourMoyenneEtudiant(idEtudiant);
    }

    void mettreAJourMoyenneEtudiant(int idEtudiant) {
        float somme = 0;
        int totalCoef = 0;
        for(const auto &n : notes) {
            if(n.getIdEtudiant() == idEtudiant) {
                somme += n.getValeur() * n.getCoefficient();
                totalCoef += n.getCoefficient();
            }
        }
        if(totalCoef > 0) {
            float newMoyenne = somme / totalCoef;
            for(auto &e : etudiants) {
                if(e.getId() == idEtudiant) {
                    e.setMoyenne(newMoyenne);
                    break;
                }
            }
        }
    }

    void supprimerNote(int idEtudiant, int idModule){
        bool existe = false;
        bool noteExiste = false;
        for(auto &e : etudiants) { if(e.getId() == idEtudiant) { existe = true; break; } }
        if(!existe) {
            cout << "\nEtudiant introuvable.\n";
            return;
        }
        for(auto a = notes.begin(); a != notes.end();) {
            if (a->getIdEtudiant() == idEtudiant && a->getIdModule() == idModule) {
                a = notes.erase(a);
                cout << "\nNote supprimee avec succes.\n";
                mettreAJourMoyenneEtudiant(idEtudiant);
                noteExiste = true;
                break;
            } else {
                ++a;
            }
        }
        if(!noteExiste) {
            cout << "\nAucune note trouvee pour cet etudiant dans ce module.\n";
        }
    }

    void modifierNote(int idEtudiant, int idModule){
        bool existe = false;
        for(auto &e : etudiants) { if(e.getId() == idEtudiant) { existe = true; break; } }
        if(!existe) {
            cout << "\nEtudiant introuvable.\n";
            return;
        }
        for(auto e = etudiants.begin(); e != etudiants.end(); ++e) {
            if (e->getId() == idEtudiant) {
                for(auto &n : notes) {
                    if (n.getIdEtudiant() == idEtudiant && n.getIdModule() == idModule) {
                        float note = lireFloat("Donnez la nouvelle note: ");
                        if(note > 20 || note < 0)
                            cout << "\nEchec de modification de note.\n";
                        else {
                            n = note;
                            cout << "\nNote modifiee.\n";
                            mettreAJourMoyenneEtudiant(idEtudiant);
                            return; // stop after modification
                        }
                    }
                }
            }
        }
    }

    void exporterNotesEtudiant(int idEtudiant) {
        string nomfichier = "notes_" + to_string(idEtudiant) + ".csv";
        ofstream file(nomfichier);
        file << "Module;Note\n";
        for(auto &n : notes) {
            if(n.getIdEtudiant() == idEtudiant) {
                file << n.getIdModule() << ";" << n.getValeur() << "\n";
            }
        }
        cout << "\nVos notes sont exportees dans " << nomfichier << "." << endl;
        file.close();
    }

    void exporterEtudiantsParGroupe(int groupe) {
        string nomFichier = "etudiants_groupe_" + to_string(groupe) + ".csv";
        ofstream file(nomFichier);
        file << "sep=;\n";
        file << "ID;Nom;Prenom;Groupe\n";
        for(auto &e : etudiants) {
            if(e.getGroupe() == groupe) {
                file << e.getId() << ";" << e.getNom() << ";" << e.getPrenom() << ";" << e.getGroupe() << "\n";
            }
        }
        file.close();
        cout << "\nExport des etudiants de groupe " << groupe << " effectue vers " << nomFichier << "." << endl;
    }

    void exporterEnseignants() {
        ofstream file("enseignants.csv");
        file << "sep=;\n";
        file << "ID;Nom;Prenom\n";
        for(auto &e : enseignants) {
            file << e.getId() << ";" << e.getNom() << ";" << e.getPrenom() << "\n";
        }
        file.close();
        cout << "\nExport des enseignants effectue vers enseignants.csv" << endl;
    }

    void etudiantExporterNotes(const Etudiant &e) {
        exporterNotesEtudiant(e.getId());
    }

    // Enregistre des heures d'absence pour un etudiant (ajoute si deja present)
    void enregistrerAbsence(int idEtudiant, int hours) {
        bool existe = false;
        for(const auto &e : etudiants) if(e.getId() == idEtudiant) { existe = true; break; }
        if(!existe) { cout << "\nEtudiant introuvable." << endl; return; }
        for(auto &a : absences) {
            if(a.first == idEtudiant) { a.second += hours; cout << "\nAbsence enregistree." << endl; return; }
        }
        absences.emplace_back(idEtudiant, hours);
        cout << "\nAbsence enregistree." << endl;
    }

    // Enregistre un avertissement pour un etudiant (compte incrementé)
    void enregistrerAvertissement(int idEtudiant) {
        bool existe = false;
        for(const auto &e : etudiants) if(e.getId() == idEtudiant) { existe = true; break; }
        if(!existe) { cout << "\nEtudiant introuvable." << endl; return; }
        for(auto &a : avertissements) {
            if(a.first == idEtudiant) { a.second += 1; cout << "\nAvertissement enregistre." << endl; return; }
        }
        avertissements.emplace_back(idEtudiant, 1);
        cout << "\nAvertissement enregistre." << endl;
    }

    // Affiche le total d'heures d'absence pour chaque etudiant (pour l'enseignant)
    void afficherAbsencesPourEnseignant(Enseignant &e) const {
        cout << "\n--- Absences (tous les etudiants) ---\n";
        for(const auto &stu : etudiants) {
            int total = 0;
            for(const auto &a : absences) if(a.first == stu.getId()) total += a.second;
            cout << "Etudiant " << stu.getId() << " - " << stu.getNom() << " " << stu.getPrenom() << " : " << total << "h\n";
        }
    }

    void listerEtudiantsDansModule(int idModule) const {
        cout << "\n--- Etudiants ayant des notes dans le module: " << getNomModule(idModule) << " ---\n";
        bool trouve = false;
        for(const auto &n : notes) {
            if(n.getIdModule() == idModule) {
                for(const auto &stu : etudiants) {
                    if(stu.getId() == n.getIdEtudiant()) {
                        cout << stu.getId() << " - " << stu.getNom() << " " << stu.getPrenom() 
                             << " (Groupe " << stu.getGroupe() << ") | Note: " << n.getValeur() << "\n";
                        trouve = true;
                        break;
                    }
                }
            }
        }
        if(!trouve) {
            cout << "Aucun etudiant n'a encore de note dans ce module.\n";
            cout << "\n--- Tous les etudiants (pour reference) ---\n";
            for(const auto &stu : etudiants) {
                cout << stu.getId() << " - " << stu.getNom() << " " << stu.getPrenom() 
                     << " (Groupe " << stu.getGroupe() << ")\n";
            }
        }
    }

    void enseignantAjouterOuModifierNote(Enseignant &e) {
        int idEtu = lireInt("\nID Etudiant: ");
        float note = lireFloat("Note: ");
        // check if note exists
        for(auto &n : notes) {
            if(n.getIdEtudiant() == idEtu && n.getIdModule() == e.getModule()) {
                if(note < 0 || note > 20) { cout << "\nNote invalide." << endl; return; }
                n = note;
                cout << "\nNote modifiee." << endl;
                mettreAJourMoyenneEtudiant(idEtu);
                return;
            }
        }
        ajouterNote(idEtu, e.getModule(), note);
    }

    void consulterNotesEtudiant(const Etudiant &e) const {
        cout << "\n--- Mes notes ---\n";
        float somme = 0; int count = 0;
        for(const auto &m : modules) {
            bool found = false;
            for(const auto &n : notes) {
                if(n.getIdEtudiant() == e.getId() && n.getIdModule() == m.getId()){
                    cout << m.getNom() << " : " << n.getValeur() << "\n";
                    somme += n.getValeur();
                    count++;
                    found = true;
                    break;
                }
            }
            if(!found) {
                cout << m.getNom() << " : " << "-" << "\n";
            }
        }
        if(count > 0) {
            cout << "Moyenne: " << (somme / count) << "\n";
        } else {
            cout << "Aucune note disponible.\n";
        }
    }

    void consulterAbsencesEtudiant(const Etudiant &e) const {
        int total = 0;
        for(const auto &a : absences) {
            if(a.first == e.getId()) total += a.second;
        }
        cout << "\n--- Mes absences ---\n";
        cout << "Total heures d'absence: " << total << "\n";
        const int seuil = 20;
        if(total > seuil) cout << "Attention: depassement du seuil d'absences (" << seuil << "h).\n";
    }

    void consulterModulesPourEtudiant(const Etudiant &e) const {
        cout << "\n--- Modules disponibles ---\n";
        for(const auto &m : modules) {
            cout << m.getId() << ". " << m.getNom();
            // find professor
            for(const auto &ens : enseignants) {
                if(ens.getModule() == m.getId()) {
                    cout << " | Prof: " << ens.getNom() << " " << ens.getPrenom();
                    break;
                }
            }
            cout << "\n";
        }
    }

    void enseignantAjouterNote(Enseignant &e) {
        string nomModule = getNomModule(e.getModule());
        cout << "\n--- Ajout de note pour le module: " << nomModule << " ---\n";
        int idEtu = lireInt("ID Etudiant: ");
        float note = lireFloat("Note (0-20): ");
        ajouterNote(idEtu, e.getModule(), note);
    }

    void enseignantSupprimerNote(Enseignant &e) {
        string nomModule = getNomModule(e.getModule());
        cout << "\n--- Suppression de note pour le module: " << nomModule << " ---\n";
        int idEtu = lireInt("ID Etudiant: ");
        supprimerNote(idEtu, e.getModule());
    }

    void enseignantModifierNote(Enseignant &e) {
        string nomModule = getNomModule(e.getModule());
        cout << "\n--- Modification de note pour le module: " << nomModule << " ---\n";
        int idEtu = lireInt("ID Etudiant: ");
        modifierNote(idEtu, e.getModule());
    }

    void enseignantConsulterNotes(Enseignant &e) const {
        cout << "\n--- Liste des notes ---\n";
        for(const auto &n : notes) {
            if(n.getIdModule() == e.getModule()){
                cout << "Etudiant " << n.getIdEtudiant() << " | Note " << n.getValeur() << "\n";
            }
        }
    }

    void enseignantCalculerMoyenneGroupe(Enseignant &ens) const {
        bool existe = false;
        bool existe2 = false;
        float moyenne = 0;
        int etudtrouve = 0;
        int id = lireInt("\nID du groupe: ");
        for(auto &g : groupes) { if(g.getId() == id) { existe = true; break; } }
        for(auto &n : notes) {
            for(auto &e : etudiants) {
                if(n.getIdEtudiant() == e.getId() && e.getGroupe() == id && n.getIdModule() == ens.getModule()){
                    moyenne += n.getValeur();
                    existe2 = true;
                    etudtrouve++;
                }
            }
        }
        if(!existe)
            cout << "\nGroupe introuvable.\n";
        else if(!existe2)
            cout << "\nAucune note a calculer.\n";
        else {
            moyenne /= etudtrouve;
            cout << "\nMoyenne de groupe " << id << " est " << moyenne << "." << endl;
        }
    }

    void consulterDonnees(const Etudiant &p) const {
        cout << "\n--- Mes informations ---\n";
        cout << "ID: " << p.getId() << "\n";
        cout << "Nom: " << p.getNom() << "\n";
        cout << "Prenom: " << p.getPrenom() << "\n";
        cout << "Groupe: " << p.getGroupe() << "\n";
        cout << "Salle: " << getNomSalle(p.getSalleId()) << "\n";
        int total = 0;
        for(const auto &a : absences) if(a.first == p.getId()) total += a.second;
        int warn = 0;
        for(const auto &av : avertissements) if(av.first == p.getId()) warn += av.second;
        cout << "Absences (heures): " << total << "\n";
        cout << "Avertissements: " << warn << "\n";
    }

    void consulterDonnees(Enseignant &p) const {
        cout << "\n--- Mes informations ---\n";
        cout << "ID: " << p.getId() << "\n";
        cout << "Nom: " << p.getNom() << "\n";
        cout << "Prenom: " << p.getPrenom() << "\n";
        cout << "ID de module: " << p.getModule() << "\n";
    }

    void consulterDonnees(const Administratif &p) const {
        cout << "\n--- Mes informations ---\n";
        cout << left << setw(18) << "ID:" << p.getId() << "\n";
        cout << left << setw(18) << "Nom:" << p.getNom() << "\n";
        cout << left << setw(18) << "Prenom:" << p.getPrenom() << "\n";
        cout << left << setw(18) << "Poste:" << "Administratif" << "\n";
    }

    void adminConsulterModules() const{
        bool existe = false;
        for(auto &m : modules) { existe = true; cout << "\n" << to_string(m.getId()) << ". " << m.getNom(); }
        cout << "\n";
        if(!existe) cout << "Aucun module.\n";
    }

    void adminAjouterModule(){
        int id = (!modules.size())?1:modules.back().getId()+1;
        string modu = lireString("\nNom de module: ");
        modules.emplace_back(id, modu);
        cout << "\nModule ajoute.\n";
    }

    void adminSupprimerModule(){
        int id = lireInt("\nID de module a supprimer: ");
        for(auto it = modules.begin(); it != modules.end(); ++it) {
            if(it->getId() == id) {
                for(auto e = enseignants.begin(); e != enseignants.end();) { if (e->getModule() == id) { e = enseignants.erase(e); } else { ++e; } }
                modules.erase(it);
                cout << "\nModule supprime.\n";
                return;
            }
        }
        cout << "\nModule introuvable.\n";
    }

    void adminAjouterGroupe(){
        groupes.emplace_back(groupes.size() + 1, 0);
        cout << "\nGroupe ajoute.\n";
    }

    void adminSupprimerGroupe(){
        int id;
        id = lireInt("\nID de groupe a supprimer: ");
        for(auto it = groupes.begin(); it != groupes.end(); ++it) {
            if(it->getId() == id) {
                for(auto e = etudiants.begin(); e != etudiants.end();) { if (e->getGroupe() == id) {
                    for(auto a = notes.begin(); a != notes.end();) { if (a->getIdEtudiant() == e->getId()) { a = notes.erase(a); } else { ++a; } }
                    e = etudiants.erase(e);
                } else { ++e; } }
                groupes.erase(it);
                cout << "\nGroupe supprime.\n";
                return;
            }
        }
        cout << "\nGroupe introuvable.\n";
    }

    void adminAjouterEtudiant(){
        int groupe;
        string nom, prenom, login, mdp;
        string numTel, dateNaissance;
        bool deja = false;
        bool existe = false;

        cout << "\nNom: "; nom = lireString("");
        cout << "Prenom: "; prenom = lireString("");
        cout << "Numero de telephone (optionnel): "; numTel = lireString("");
        cout << "Date de naissance (YYYY-MM-DD) (optionnel): "; dateNaissance = lireString("");
        cout << "Login: "; login = lireString("");
        cout << "Mot de passe: "; mdp = lireString("");
        groupe = lireInt("Groupe: ");

        for(auto &g : groupes) { if(g.getId() == groupe) { existe = true; break; } }
        if(!existe){ cout << "\nGroupe introuvable.\n"; return; }

        for (const auto& e : etudiants) { if (e.getLogin() == login) { deja = true; break; } }
        for (const auto& ens : enseignants) { if (ens.getLogin() == login) { deja = true; break; } }
        for (const auto& a : admins) { if (a.getLogin() == login) { deja = true; break; } }

        if(deja)
            cout << "\nLogin existe deja.\n";
        else {
            int newEtudiantId = !etudiants.size() ? 1 : etudiants.back().getId() + 1;
            etudiants.emplace_back(newEtudiantId, nom, prenom, numTel, dateNaissance, login, mdp, groupe, 0.0f, 0, 0, 0);
            cout << "\nEtudiant ajoute avec succes.\n";
            for(auto &g : groupes) { if(g.getId() == groupe){ g.incrementer(); break; } }
            
            // Ask if user wants to assign to a salle
            cout << "Assigner a une salle? (1=Oui, 0=Non): ";
            int assign = lireInt("");
            if(assign == 1) {
                listerSalles();
                int idSalle = lireInt("ID de la salle: ");
                assignerEtudiantASalle(newEtudiantId, idSalle);
            }
        }
    }

    void adminAjouterEnseignant(){
        int id;
        string nom, prenom, login, mdp;
        bool deja = false;
        bool existe = false;

        cout << "\nNom: "; nom = lireString("");
        cout << "Prenom: "; prenom = lireString("");
        id = lireInt("ID de module: ");
        cout << "Login: "; login = lireString("");
        cout << "Mot de passe: "; mdp = lireString("");

        for(auto &m : modules) { if(m.getId() == id) { existe = true; break; } }
        if(!existe){ cout << "\nModule introuvable.\n"; return; }

        for (const auto& e : etudiants) { if (e.getLogin() == login) { deja = true; break; } }
        for (const auto& ens : enseignants) { if (ens.getLogin() == login) { deja = true; break; } }
        for (const auto& a : admins) { if (a.getLogin() == login) { deja = true; break; } }

        if(deja)
            cout << "\nLogin existe deja.\n";
        else {
            enseignants.emplace_back(!enseignants.size()?101:enseignants.back().getId()+1, nom, prenom, id, login, mdp);
            cout << "\nEnseignant ajoute avec succes.\n";
        }
    }

    void adminSupprimerEtudiant(){
        int id = lireInt("\nID de l'etudiant a supprimer: ");

        for(auto it = etudiants.begin(); it != etudiants.end(); ++it) {
            if(it->getId() == id) {
                for(auto &g : groupes) { if(g.getId() == it->getGroupe()){ g.decrementer(); break; } }
                for(auto a = notes.begin(); a != notes.end();) { if (a->getIdEtudiant() == id) { a = notes.erase(a); } else { ++a; } }
                etudiants.erase(it);
                cout << "\nEtudiant supprime.\n";
                return;
            }
        }
        cout << "\nEtudiant introuvable.\n";
    }

    void adminSupprimerEnseignant(){
        int id = lireInt("\nID de l'enseignant a supprimer: ");

        for(auto it = enseignants.begin(); it != enseignants.end(); ++it) {
            if(it->getId() == id) {
                enseignants.erase(it);
                cout << "\nEnseignant supprime.\n";
                return;
            }
        }
        cout << "\nEnseignant introuvable.\n";
    }

    void adminModifierEtudiant(){
        int id = lireInt("\nID de l'etudiant a modifier: ");

        for(auto &e : etudiants) {
            if(e.getId() == id) {
                int choix;
                do {
                    cout << "\n1. Modifier nom\n";
                    cout << "2. Modifier prenom\n";
                    cout << "3. Modifier login\n";
                    cout << "4. Modifier mot de passe\n";
                    cout << "5. Modifier groupe\n";
                    cout << "6. Modifier salle\n";
                    cout << "0. Retour\n" << endl;
                    choix = lireInt("Choix: ");

                    switch (choix) {
                        case 1: {
                            string v = lireString("\nNouveau nom: ");
                            e.setNom(v);
                            break;
                        }
                        case 2: {
                            string v = lireString("\nNouveau prenom: ");
                            e.setPrenom(v);
                            break;
                        }
                        case 3: {
                            string v = lireString("\nNouveau login: ");
                            bool deja = false;
                            for (const auto& ee : etudiants) { if (ee.getLogin() == v) { deja = true; break; } }
                            for (const auto& ens : enseignants) { if (ens.getLogin() == v) { deja = true; break; } }
                            for (const auto& a : admins) { if (a.getLogin() == v) { deja = true; break; } }
                            if(deja) cout << "\nLogin existe deja.\n";
                            else e.setLogin(v);
                            break;
                        }
                        case 4: {
                            string v = lireString("\nNouveau mot de passe: ");
                            e.setMdp(v);
                            break;
                        }
                        case 5: {
                            int gg = lireInt("\nNouveau groupe: ");
                            bool existe = false;
                            for(auto &g : groupes) { if(g.getId() == gg){ existe = true; break; } }
                            if(!existe) { cout << "\nGroupe introuvable.\n"; return; }
                            for(auto &g : groupes) { if(g.getId() == e.getGroupe()){ g.decrementer(); break; } }
                            e.setGroupe(gg);
                            for(auto &g : groupes) { if(g.getId() == gg){ g.incrementer(); break; } }
                            break;
                        }
                        case 6: {
                            listerSalles();
                            int idSalle = lireInt("\nNouvelle salle (0 pour desassigner): ");
                            if(idSalle == 0) {
                                e.setSalleId(0);
                                cout << "\nEtudiant desassigne de la salle.\n";
                            } else {
                                assignerEtudiantASalle(e.getId(), idSalle);
                            }
                            break;
                        }
                    }
                } while (choix != 0);

                cout << "\nModification terminee.\n";
                return;
            }
        }
        cout << "\nEtudiant introuvable.\n";
    }

    void adminModifierEnseignant(){
        int id = lireInt("\nID de l'enseignant a modifier: ");

        for(auto &e : enseignants) {
            if(e.getId() == id) {
                int choix;
                do {
                    cout << "\n1. Modifier nom\n";
                    cout << "2. Modifier prenom\n";
                    cout << "3. Modifier login\n";
                    cout << "4. Modifier mot de passe\n";
                    cout << "0. Retour\n" << endl;
                    choix = lireInt("Choix: ");

                    switch (choix) {
                        case 1: {
                            string v = lireString("\nNouveau nom: ");
                            e.setNom(v);
                            break;
                        }
                        case 2: {
                            string v = lireString("\nNouveau prenom: ");
                            e.setPrenom(v);
                            break;
                        }
                        case 3: {
                            string v = lireString("\nNouveau login: ");
                            bool deja = false;
                            for (const auto& ee : etudiants) { if (ee.getLogin() == v) { deja = true; break; } }
                            for (const auto& ens : enseignants) { if (ens.getLogin() == v) { deja = true; break; } }
                            for (const auto& a : admins) { if (a.getLogin() == v) { deja = true; break; } }
                            if(deja) cout << "\nLogin existe deja.\n";
                            else e.setLogin(v);
                            break;
                        }
                        case 4: {
                            string v = lireString("\nNouveau mot de passe: ");
                            e.setMdp(v);
                            break;
                        }
                    }
                } while (choix != 0);

                cout << "\nModification terminee.\n";
                return;
            }
        }
        cout << "\nEnseignant introuvable.\n";
    }

    void adminExporterEtudiantsParGroupe() {
        int groupe = lireInt("\nNumero du groupe: ");
        bool existe = false;
        for(auto &g : groupes) { if(g.getId() == groupe) { existe = true; break; } }
        if(!existe) { cout << "\nGroupe introuvable\n"; return; }
        exporterEtudiantsParGroupe(groupe);
    }

    void adminExporterEnseignants() {
        exporterEnseignants();
    }

    Etudiant* trouverEtudiant(int idEtudiant) {
        for(auto &e : etudiants) {
            if(e.getId() == idEtudiant) return &e;
        }
        return nullptr;
    }
};

int main()
{
    Etablissement EMSI;
    int choix;
    bool connecte = false;
    bool programme = true;
    string login, mdp;
    Personne* user;

    EMSI.charger();


    while(programme){
        if(!connecte){
            int role = 0;
            do {
                cout << "\n==================================================\n";
                cout << "||- -- Bienvenue dans le Campus des Nobles - - -||\n";
                cout << "==================================================\n";
                cout << "|| 1. Etudiant                                  ||\n";
                cout << "|| 2. Enseignant                                ||\n";
                cout << "|| 3. Administratif                             ||\n";
                cout << "|| 4. Parent                                    ||\n";
                cout << "|| 0. Quitter                                   ||\n";
                cout << "==================================================\n";
                role = lireInt("Choix: ");
                if(role == 0) { programme = false; break; }
            } while(role < 0 || role > 4);
            if(!programme) break;

            login = lireString("Nom d'utilisateur: ");
            if(login == "0") { programme = false; break; }
            mdp = lireString("Mot de passe: ");

            user = EMSI.authentifier(login, mdp);
            while(!user || (role == 1 && user->getPermissions() != "ETUDIANT") || (role == 2 && user->getPermissions() != "ENSEIGNANT") || (role == 3 && user->getPermissions() != "ADMIN") || (role == 4 && user->getPermissions() != "PARENT")) {
                cout << "\nAuthentification echouee ou role incorrect\n" << endl;
                cout << "Nom d'utilisateur: ";
                if(!getline(cin, login) || login.size() == 0) getline(cin, login);
                if(login == "0") { programme = false; return 0; }
                cout << "Mot de passe: ";
                if(!getline(cin, mdp) || mdp.size() == 0) getline(cin, mdp);
                user = EMSI.authentifier(login, mdp);
            }
            cout << "\n- Connexion etablie en tant que " << user->getNom() << " " << user->getPrenom() << " -" << endl;
            connecte = true;
        } else {
            if(user->getPermissions() == "ETUDIANT") {
                Etudiant *etu = dynamic_cast<Etudiant*>(user);
                    do {
                        cout << "\n+------------------------------------------------+\n";
                        cout << "|                 Menu Etudiant                   |\n";
                        cout << "+------------------------------------------------+\n";
                        cout << "| 1. Consulter mes informations personnelles    |\n";
                        cout << "| 2. Consulter mes notes                        |\n";
                        cout << "| 3. Consulter mes absences                     |\n";
                        cout << "| 4. Consulter les modules                      |\n";
                        cout << "| 5. Consulter ma salle de classe               |\n";
                        cout << "| 6. Se deconnecter                             |\n";
                        cout << "| 7. Quitter le programme                       |\n";
                        cout << "+------------------------------------------------+\n";
                        choix = lireInt("Choix: ");
                        switch(choix) {
                            case 7: programme = false; cout << "\n+ Programme se termine +" << endl; break;
                            case 1: EMSI.consulterDonnees(*etu); break;
                            case 2: EMSI.consulterNotesEtudiant(*etu); break;
                            case 3: EMSI.consulterAbsencesEtudiant(*etu); break;
                            case 4: EMSI.consulterModulesPourEtudiant(*etu); break;
                            case 5: {
                                cout << "\n--- Ma salle de classe ---\n";
                                if(etu->getSalleId() == 0) {
                                    cout << "Vous n'etes pas encore assigne a une salle.\n";
                                } else {
                                    cout << "Salle: " << EMSI.getNomSalle(etu->getSalleId()) << "\n";
                                    int cap = EMSI.capaciteSalle(etu->getSalleId());
                                    int occ = EMSI.nombreEtudiantsDansSalle(etu->getSalleId());
                                    cout << "Occupation: " << occ << "/" << cap << " places\n";
                                }
                                break;
                            }
                            case 6: user = nullptr; cout << "\nUtilisateur se deconnecte.\n" << endl; connecte = false; break;
                            default: cout << "\nChoix invalide\n"; break;
                        }
                    } while (choix != 7 && choix != 6);
            }
            else if(user->getPermissions() == "ENSEIGNANT") {
                Enseignant *ens = dynamic_cast<Enseignant*>(user);
                do {
                        cout << "\n+------------------------------------------------+\n";
                        cout << "|                Menu Enseignant                |\n";
                        cout << "+------------------------------------------------+\n";
                        cout << "| 1. Consulter mon module                       |\n";
                        cout << "| 2. Lister les etudiants de mon module         |\n";
                        cout << "| 3. Ajouter une note                           |\n";
                        cout << "| 4. Modifier une note                          |\n";
                        cout << "| 5. Supprimer une note                         |\n";
                        cout << "| 6. Calculer moyenne du groupe                 |\n";
                        cout << "| 7. Enregistrer une absence                    |\n";
                        cout << "| 8. Enregistrer un avertissement               |\n";
                        cout << "| 9. Consulter les absences                     |\n";
                        cout << "| 10. Se deconnecter                            |\n";
                        cout << "| 0. Quitter le programme                       |\n";
                        cout << "+------------------------------------------------+\n";
                        choix = lireInt("Choix: ");
                        switch(choix) {
                            case 0: programme = false; cout << "\n+ Programme se termine +" << endl; break;
                            case 1: {
                                cout << "\n--- Mon module ---\n";
                                for(const auto &m : EMSI.getModules()) {
                                    if(m.getId() == ens->getModule()) {
                                        cout << "ID: " << m.getId() << " | Nom: " << m.getNom() << "\n";
                                        break;
                                    }
                                }
                                break;
                            }
                            case 2: EMSI.listerEtudiantsDansModule(ens->getModule()); break;
                            case 3: EMSI.enseignantAjouterNote(*ens); break;
                            case 4: EMSI.enseignantModifierNote(*ens); break;
                            case 5: EMSI.enseignantSupprimerNote(*ens); break;
                            case 6: EMSI.enseignantCalculerMoyenneGroupe(*ens); break;
                            case 7: { int idEtu = lireInt("\nID Etudiant: "), hours = lireInt("Heures: "); EMSI.enregistrerAbsence(idEtu, hours); break; }
                            case 8: { int idEtu = lireInt("\nID Etudiant pour avertissement: "); EMSI.enregistrerAvertissement(idEtu); break; }
                            case 9: EMSI.afficherAbsencesPourEnseignant(*ens); break;
                            case 10: user = nullptr; cout << "\nUtilisateur se deconnecte.\n" << endl; connecte = false; break;
                            default: cout << "\nChoix invalide\n"; break;
                        }
                    } while (choix != 0 && choix != 10);
            }
            else if(user->getPermissions() == "ADMIN") {
                Administratif *adm = dynamic_cast<Administratif*>(user);
                do {
                    cout << "\n+------------------------------------------------+\n";
                    cout << "|            Menu Administrateur                 |\n";
                    cout << "+------------------------------------------------+\n";
                    cout << "| 1.  Consulter mes donnees                      |\n";
                    cout << "| 2.  Ajouter un etudiant                        |\n";
                    cout << "| 3.  Ajouter un enseignant                      |\n";
                    cout << "| 4.  Supprimer un etudiant                      |\n";
                    cout << "| 5.  Supprimer un enseignant                    |\n";
                    cout << "| 6.  Modifier un etudiant                       |\n";
                    cout << "| 7.  Modifier un enseignant                     |\n";
                    cout << "| 8.  Exporter etudiants par groupe              |\n";
                    cout << "| 9.  Exporter enseignants                       |\n";
                    cout << "| 10. Ajouter un groupe                          |\n";
                    cout << "| 11. Supprimer un groupe                        |\n";
                    cout << "| 12. Consulter toutes les modules               |\n";
                    cout << "| 13. Ajouter un module                          |\n";
                    cout << "| 14. Supprimer un module                        |\n";
                    cout << "| 16. Gestion des salles                         |\n";
                    cout << "| 15. Se deconnecter                             |\n";
                    cout << "| 0.  Quitter le programme                       |\n";
                    cout << "+------------------------------------------------+\n";
                    choix = lireInt("Choix: ");
                    switch(choix) {
                        case 0:
                            programme = false; cout << "\n+ Programme se termine +" << endl;
                        break;
                        case 1:
                            EMSI.consulterDonnees(*adm);
                        break;
                        case 2:
                            EMSI.adminAjouterEtudiant();
                        break;
                        case 3:
                            EMSI.adminAjouterEnseignant();
                        break;
                        case 4:
                            EMSI.adminSupprimerEtudiant();
                        break;
                        case 5:
                            EMSI.adminSupprimerEnseignant();
                        break;
                        case 6:
                            EMSI.adminModifierEtudiant();
                        break;
                        case 7:
                            EMSI.adminModifierEnseignant();
                        break;
                        case 8:
                            EMSI.adminExporterEtudiantsParGroupe();
                        break;
                        case 9:
                            EMSI.adminExporterEnseignants();
                        break;
                        case 10:
                            EMSI.adminAjouterGroupe();
                        break;
                        case 11:
                            EMSI.adminSupprimerGroupe();
                        break;
                        case 12:
                            EMSI.adminConsulterModules();
                        break;
                        case 13:
                            EMSI.adminAjouterModule();
                        break;
                        case 14:
                            EMSI.adminSupprimerModule();
                        break;
                        case 16: {
                            int sousChoix;
                            do {
                                cout << "\n+------------------------------------------------+\n";
                                cout << "|            GESTION DES SALLES                  |\n";
                                cout << "+------------------------------------------------+\n";
                                cout << "| 1. Lister les salles                          |\n";
                                cout << "| 2. Ajouter une salle                          |\n";
                                cout << "| 3. Modifier une salle                         |\n";
                                cout << "| 4. Supprimer une salle                        |\n";
                                cout << "| 5. Assigner etudiant a une salle              |\n";
                                cout << "| 6. Voir etudiants dans une salle              |\n";
                                cout << "| 0. Retour                                     |\n";
                                cout << "+------------------------------------------------+\n";
                                sousChoix = lireInt("Choix: ");
                                
                                switch(sousChoix) {
                                    case 1: EMSI.listerSalles(); break;
                                    case 2: EMSI.ajouterSalle(); break;
                                    case 3: EMSI.modifierSalle(); break;
                                    case 4: EMSI.supprimerSalle(); break;
                                    case 5: {
                                        int idEtu = lireInt("\nID Etudiant: ");
                                        EMSI.listerSalles();
                                        int idSalle = lireInt("ID Salle: ");
                                        EMSI.assignerEtudiantASalle(idEtu, idSalle);
                                        break;
                                    }
                                    case 6: EMSI.voirEtudiantsDansSalle(); break;
                                }
                            } while(sousChoix != 0);
                            break;
                        }
                        case 15:
                            user = nullptr; cout << "\nUtilisateur se deconnecte.\n" << endl; connecte = false;
                        break;
                        default:
                            cout << "\nChoix invalide\n";
                    }
                } while (choix != 0 && choix != 15);
            }
            else if(user->getPermissions() == "PARENT") {
                Parent *parent = dynamic_cast<Parent*>(user);
                do {
                    cout << "\n+------------------------------------------------+\n";
                    cout << "|                  Menu Parent                   |\n";
                    cout << "+------------------------------------------------+\n";
                    cout << "| 1. Consulter les notes de mon enfant         |\n";
                    cout << "| 2. Consulter les absences de mon enfant      |\n";
                    cout << "| 3. Consulter les informations de mon enfant  |\n";
                    cout << "| 4. Se deconnecter                             |\n";
                    cout << "| 0. Quitter le programme                       |\n";
                    cout << "+------------------------------------------------+\n";
                    choix = lireInt("Choix: ");
                    
                    // Find the child
                    Etudiant* enfant = EMSI.trouverEtudiant(parent->getIdEnfant());
                    
                    if(!enfant && choix != 0 && choix != 4) {
                        cout << "\nErreur: Enfant introuvable dans le systeme.\n";
                        continue;
                    }
                    
                    switch(choix) {
                        case 0: 
                            programme = false; 
                            cout << "\n+ Programme se termine +" << endl; 
                            break;
                        case 1: 
                            if(enfant) EMSI.consulterNotesEtudiant(*enfant); 
                            break;
                        case 2: 
                            if(enfant) EMSI.consulterAbsencesEtudiant(*enfant); 
                            break;
                        case 3: 
                            if(enfant) EMSI.consulterDonnees(*enfant); 
                            break;
                        case 4: 
                            user = nullptr; 
                            cout << "\nUtilisateur se deconnecte.\n" << endl; 
                            connecte = false; 
                            break;
                        default: 
                            cout << "\nChoix invalide\n"; 
                            break;
                    }
                } while (choix != 0 && choix != 4);
            }
        }
    }

    EMSI.sauvegarder();

    return 0;
}

