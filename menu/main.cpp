 // Campus des nobles - Alpha - Projet C++ Programmation Orientée Objet
// Taha Zerrad, Salsabile Benhnich, Oussama El Attabi, Rania Mahfoud, Badr Al Fezghari
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

// NOUVEAUX UPDATES:
    // 1. Solution pour boucle après cin >>
    // 2. Importer étudiants d'un fichier .csv si plusieurs étudiants
    // 3. Confirmer les différentes suppressions
    // 4. Journalisation dans fichier journal.log

// à ajouter: polymorphisme dans le menu, les classes d'erreurs try throw, amélioration de lisibilité.

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <chrono>
#include <ctime>

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
    float moyenne;
    int nbAbsences;
    int nbAvertissements;
public:
    Etudiant(int id, string nom, string prenom, string numTel, string dateNaissance, string login, string mdp, int groupe, float moyenne, int nbAbsences, int nbAvertissements)
    : Personne(id, nom, prenom, numTel, dateNaissance, login, mdp), groupe(groupe), moyenne(moyenne), nbAbsences(nbAbsences), nbAvertissements(nbAvertissements) { }

    string getPermissions() const override { return "ETUDIANT"; }
    int getGroupe() const { return groupe; }
    float getMoyenne() const { return moyenne; }
    int getNbAbsences() const { return nbAbsences; }
    int getNbAvertissements() const { return nbAvertissements; }

    void setGroupe(int g) { groupe = g; }
    void setMoyenne(float m) { moyenne = m; }
    void setNbAbsences(int a) { nbAbsences = a; }
    void setNbAvertissements(int av) { nbAvertissements = av; }

    string afficher() const override {
        return to_string(id) + ";" + nom + ";" + prenom + ";" + numTel + ";" + dateNaissance + ";" + login + ";" + motDePasse + ";" + to_string(groupe) + ";" + to_string(moyenne) + ";" + to_string(nbAbsences) + ";" + to_string(nbAvertissements);
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

class Note {
private:
    int idEtudiant;
    int idModule;
    float valeur;
public:
    Note(int idEtu, int idMod, float val)
    : idEtudiant(idEtu), idModule(idMod), valeur(val) { }

    int getIdEtudiant() const { return idEtudiant; }
    int getIdModule() const { return idModule; }
    float getValeur() const { return valeur; }

    string afficher() const {
        return to_string(idEtudiant) + ";" + to_string(idModule) + ";" + to_string(valeur);
    }

    Note operator+(const Note& N) {
        return Note(this->idEtudiant, this->idModule, this->valeur + N.valeur);
    }

    Note operator+(const float n) {
        return Note(this->idEtudiant, this->idModule, this->valeur + n);
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

void journaliser(string action, string user){
    ofstream fichier;
    char buffer[80];
    time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now());
    struct tm *tm_local = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_local);
    string journal = "[ Date: " + string(buffer) + " | Utilisateur: " + user + " ] - Action: " + action;
    fichier.open("journal.log", ios::app);
    fichier << journal << endl;
    fichier.close();
}

class Etablissement {
private:
    vector<Etudiant> etudiants;
    vector<Enseignant> enseignants;
    vector<Administratif> admins;
    vector<Note> notes;
    vector<Module> modules;
    vector<Groupe> groupes;
    vector<pair<int,int>> absences; // pair<idEtudiant, totalHours>
    vector<pair<int,int>> avertissements; // pair<idEtudiant, count>
public:
    void charger() {
        ifstream fichier;
        string ligne;

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
            int id, groupe, nbAbsences, nbAvertissements;
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

            etudiants.emplace_back(id, nom, prenom, numTel, dateNaissance, login, mdp, groupe, moyenne, nbAbsences, nbAvertissements);
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

            getline(ss,token,';'); idEtu = stoi(token);
            getline(ss,token,';'); idMod = stoi(token);
            getline(ss,token,';'); note = stof(token);

            notes.emplace_back(idEtu, idMod, note);
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

        // !! pour le test initial, il existe un admin (Nom d'utilisateur: abcd, Mot de passe: 1234)
        if(!admins.size()){
            ofstream fichier;
            fichier.open("administratifs.txt");
            fichier << "201;Test;Admin;abcd;1234" << endl;
            admins.emplace_back(201, "Test", "Admin", "abcd", "1234");
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
            // Format: id;nom;prenom;numTel;dateNaissance;login;mdp;groupe;moyenne;nbAbsences;nbAvertissements
            fichier << "1;Doe;John;0000;2000-01-01;stu1;1111;1;0;0;0" << endl;
            fichier << "2;Smith;Alice;0000;2000-01-02;stu2;2222;1;0;0;0" << endl;
            etudiants.emplace_back(1, "Doe", "John", "0000", "2000-01-01", "stu1", "1111", 1, 0.0f, 0, 0);
            etudiants.emplace_back(2, "Smith", "Alice", "0000", "2000-01-02", "stu2", "2222", 1, 0.0f, 0, 0);
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
        ofstream fichier;

        fichier.open("groupes.txt");
        for(auto &g : groupes) { fichier << g.afficher() << endl; }
        fichier.close();

        fichier.open("modules.txt");
        for(auto &m : modules) { fichier << m.afficher() << endl; }
        fichier.close();

        fichier.open("etudiants.txt");
        for(auto &e : etudiants) { fichier << e.afficher() << endl; }
        fichier.close();

        fichier.open("enseignants.txt");
        for(auto &ens : enseignants) { fichier << ens.afficher() << endl; }
        fichier.close();

        fichier.open("administratifs.txt");
        for(auto &a : admins) { fichier << a.afficher() << endl; }
        fichier.close();

        fichier.open("notes.txt");
        for(auto &n : notes) { fichier << n.afficher() << endl; }
        fichier.close();
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

        return nullptr;
    }

    bool ajouterNote(int idEtudiant, int idModule, float valeur) {
        bool existe1 = false;
        bool existe2 = false;
        bool existe3 = true;

        for(auto &e : etudiants) { if(e.getId() == idEtudiant) { existe1 = true; break; } }
        if(!existe1) { cout << "\nEtudiant introuvable.\n"; return false; }

        for(auto &m : modules) { if(m.getId() == idModule) { existe2 = true; break; } }
        if(!existe2) { cout << "\nModule introuvable.\n"; return false; }

        for(auto &n : notes) { if(n.getIdEtudiant() == idEtudiant && n.getIdModule() == idModule) { existe3 = false; break; } }
        if(!existe3) { cout << "\nEtudiant deja a une note dans ce module. Essayez de modifier la note.\n"; return false; }

        if(valeur > 20 || valeur < 0){
            cout << "\nNote invalide.\n";
            return false;
        }

        notes.emplace_back(idEtudiant, idModule, valeur);
        cout << "\nNote ajoutee avec succes.\n";

        return true;
    }

    bool supprimerNote(int idEtudiant, int idModule){
        bool existe = false;

        for(auto &e : etudiants) { if(e.getId() == idEtudiant) { existe = true; break; } }
        if(!existe) { cout << "\nEtudiant introuvable.\n"; return false; }

        for(auto e = etudiants.begin(); e != etudiants.end(); ++e) {
            if (e->getId() == idEtudiant) {
                for(auto a = notes.begin(); a != notes.end();) {
                    if (a->getIdEtudiant() == e->getId() && a->getIdModule() == idModule) {
                        int confirm = 0; 
                        cout << "\nEtes-vous sur? (Oui = 1, Non = 0)\n" << endl;
                        while(!(cin >> confirm)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
                        if(confirm){
                            a = notes.erase(a);
                            cout << "\nNote supprimee.\n";
                        } else {
                            cout << "\nLa note n'est pas supprimee.\n";
                            return false;
                        }
                        break;
                    } else {
                        ++a;
                    }
                }
            }
        }

        return true;
    }

    bool modifierNote(int idEtudiant, int idModule){
        bool existe = false;

        for(auto &e : etudiants) { if(e.getId() == idEtudiant) { existe = true; break; } }
        if(!existe) { cout << "\nEtudiant introuvable.\n"; return false; }

        for(auto e = etudiants.begin(); e != etudiants.end(); ++e) {
            if (e->getId() == idEtudiant) {
                for(auto &n : notes) {
                    if (n.getIdEtudiant() == idEtudiant && n.getIdModule() == idModule) {
                        float note;
                        cout << "Donnez la nouvelle note: ";
                        while(!(cin >> note)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
                        if(note > 20 || note < 0){
                            cout << "\nEchec de modification de note.\n";
                            return false;
                        } else {
                            n = note;
                            cout << "\nNote modifiee.\n";
                        }
                    }
                }
            }
        }

        return true;
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
                            return; // stop after modification
                        }
                    }
                }
            }
        }
    }

    void exporterNotesEtudiant(int idEtudiant) {
        string nomfichier = "notes_" + to_string(idEtudiant) + ".csv";
        ofstream fichier(nomfichier);
        fichier << "Module;Note\n";
        for(auto &n : notes) {
            if(n.getIdEtudiant() == idEtudiant) {
                fichier << n.getIdModule() << ";" << n.getValeur() << "\n";
            }
        }
        cout << "\nVos notes sont exportees dans " << nomfichier << "." << endl;
        fichier.close();
    }

    void exporterEtudiantsParGroupe(int groupe) {
        string nomFichier = "etudiants_groupe_" + to_string(groupe) + ".csv";
        ofstream fichier(nomFichier);
        fichier << "sep=;\n";
        fichier << "ID;Nom;Prenom;Groupe\n";
        for(auto &e : etudiants) {
            if(e.getGroupe() == groupe) {
                fichier << e.getId() << ";" << e.getNom() << ";" << e.getPrenom() << ";" << e.getGroupe() << "\n";
            }
        }
        fichier.close();
        cout << "\nExport des etudiants de groupe " << groupe << " effectue vers " << nomFichier << "." << endl;
    }

    void exporterEnseignants() {
        ofstream fichier("enseignants.csv");
        fichier << "sep=;\n";
        fichier << "ID;Nom;Prenom\n";
        for(auto &e : enseignants) {
            fichier << e.getId() << ";" << e.getNom() << ";" << e.getPrenom() << "\n";
        }
        fichier.close();
        cout << "\nExport des enseignants effectue vers enseignants.csv" << endl;
    }

    void etudiantExporterNotes(const Etudiant &e) {
        exporterNotesEtudiant(e.getId());
        journaliser("Exportation des notes",e.getNom() + " " + e.getPrenom());
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
        cout << "\n--- Liste des etudiants (pas d'inscription par module dans la BD actuelle) ---\n";
        for(const auto &stu : etudiants) {
            cout << stu.getId() << " - " << stu.getNom() << " " << stu.getPrenom() << " (Groupe " << stu.getGroupe() << ")\n";
        }
    }

    void enseignantAjouterOuModifierNote(Enseignant &e) {
        int idEtu;
        float note;
        cout << "\nID Etudiant: ";
        while(!(cin >> idEtu)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
        cout << "Note: ";
        while(!(cin >> note)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
        if(ajouterNote(idEtu, e.getModule(), note))
            journaliser("Ajout de note",e.getNom() + " " + e.getPrenom());
    }

    void enseignantSupprimerNote(Enseignant &e) {
        int idEtu;
        cout << "\nID Etudiant: ";
        while(!(cin >> idEtu)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
        if(supprimerNote(idEtu, e.getModule()))
            journaliser("Suppression de note",e.getNom() + " " + e.getPrenom());
    }

    void enseignantModifierNote(Enseignant &e) {
        int idEtu;
        cout << "\nID Etudiant: ";
        while(!(cin >> idEtu)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
        if(modifierNote(idEtu, e.getModule()))
            journaliser("Modification de note",e.getNom() + " " + e.getPrenom());
    }

    void enseignantModifierNote(Enseignant &e) {
        int idEtu = lireInt("\nID Etudiant: ");
        modifierNote(idEtu, e.getModule());
    }

    void enseignantConsulterNotes(Enseignant &e) const {
        cout << "\n--- Liste des notes ---\n";
        for(const auto &n : notes) {
            if(n.getIdModule() == e.getModule()){
                cout << "Etudiant " << n.getIdEtudiant() << " | Note " << n.getValeur() << "\n";
            }
        }
        journaliser("Consultation des notes",e.getNom() + " " + e.getPrenom());
    }

    void enseignantCalculerMoyenneGroupe(Enseignant &ens) const {
        int id;
        bool existe = false;
        bool existe2 = false;
        float moyenne = 0;
        int etudtrouve = 0;
        cout << "\nID du groupe: ";
        while(!(cin >> id)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
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
        journaliser("Calcul de moyenne de groupe",ens.getNom() + " " + ens.getPrenom());
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
        int total = 0;
        for(const auto &a : absences) if(a.first == p.getId()) total += a.second;
        int warn = 0;
        for(const auto &av : avertissements) if(av.first == p.getId()) warn += av.second;
        cout << "Absences (heures): " << total << "\n";
        cout << "Avertissements: " << warn << "\n";
    }

    void consulterDonnees(Enseignant &ens) const {
        cout << "\n--- Mes informations ---\n";
        cout << "ID: " << ens.getId() << "\n";
        cout << "Nom: " << ens.getNom() << "\n";
        cout << "Prenom: " << ens.getPrenom() << "\n";
        cout << "ID de module: " << ens.getModule() << "\n";
        journaliser("Consultation des données",ens.getNom() + " " + ens.getPrenom());
    }

    void consulterDonnees(const Administratif &a) const {
        cout << "\n--- Mes informations ---\n";
        cout << "ID: " << a.getId() << "\n";
        cout << "Nom: " << a.getNom() << "\n";
        cout << "Prenom: " << a.getPrenom() << "\n";
        journaliser("Consultation des données",a.getNom() + " " + a.getPrenom());
    }

    void adminConsulterModules(const Administratif &a) const{
        bool existe = false;
        for(auto &m : modules) { existe = true; cout << "\n" << to_string(m.getId()) << ". " << m.getNom(); }
        cout << "\n";
        if(!existe) cout << "Aucun module.\n";
        journaliser("Consultation des modules",a.getNom() + " " + a.getPrenom());
    }

    void adminAjouterModule(const Administratif &a){
        int id = (!modules.size())?1:modules.back().getId()+1;
        string modu;
        cout << "\nNom de module: ";
        cin >> modu;
        modules.emplace_back(id,modu);
        cout << "\nModule ajoute.\n";
        journaliser("Ajout de module",a.getNom() + " " + a.getPrenom());
    }

    void adminSupprimerModule(const Administratif &a){
        int id;
        cout << "\nID de module a supprimer: ";
        while(!(cin >> id)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
        for(auto it = modules.begin(); it != modules.end(); ++it) {
            if(it->getId() == id) {
                int confirm = 0; 
                cout << "\nEtes-vous sur? (Oui = 1, Non = 0)\n" << endl;
                while(!(cin >> confirm)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
                if(confirm){
                    for(auto e = enseignants.begin(); e != enseignants.end();) { if (e->getModule() == id) { e = enseignants.erase(e); } else { ++e; } }
                    modules.erase(it);
                    cout << "\nModule supprime.\n";
                    journaliser("Suppression de module",a.getNom() + " " + a.getPrenom());
                } else
                    cout << "\nLe module n'est pas supprime.\n";
                return;
            }
        }
        cout << "\nModule introuvable.\n";
    }

    void adminAjouterGroupe(const Administratif &a){
        groupes.emplace_back(groupes.size() + 1, 0);
        cout << "\nGroupe ajoute.\n";
        journaliser("Ajout de groupe",a.getNom() + " " + a.getPrenom());
    }

    void adminSupprimerGroupe(const Administratif &ad){
        int id;
        id = lireInt("\nID de groupe a supprimer: ");
        for(auto it = groupes.begin(); it != groupes.end(); ++it) {
            if(it->getId() == id) {
                int confirm = 0; 
                cout << "\nEtes-vous sur? (Oui = 1, Non = 0)\n" << endl;
                while(!(cin >> confirm)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
                if(confirm){
                    for(auto e = etudiants.begin(); e != etudiants.end();) { if (e->getGroupe() == id) {
                        for(auto a = notes.begin(); a != notes.end();) { if (a->getIdEtudiant() == e->getId()) { a = notes.erase(a); } else { ++a; } }
                        e = etudiants.erase(e);
                    } else { ++e; } }
                    groupes.erase(it);
                    cout << "\nGroupe supprime.\n";
                    journaliser("Suppression de groupe",ad.getNom() + " " + ad.getPrenom());
                } else
                    cout << "\nLe groupe n'est pas supprime.\n";
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

    int importerEtudiants(string f){
        string ligne;
        ifstream fichier;
        int n = 0;
        fichier.open(f);
        if(!fichier.is_open()) {
            cerr << "\nImpossible d'ouvrir le fichier." << endl;
            return 0;
        }
        if(!getline(fichier, ligne)) {
            cerr << "\nFichier vide ou erreur lors de la lecture." << endl;
            return 0;
        }
        while (getline(fichier, ligne)) {
            stringstream ss(ligne);
            string token;
            int id, groupe;
            string nom, prenom, login, mdp;
            getline(ss,token,';'); id = stoi(token);
            getline(ss,nom,';');
            getline(ss,prenom,';');
            getline(ss,login,';');
            getline(ss,mdp,';');
            getline(ss,token,';'); groupe = stoi(token);
            etudiants.emplace_back(id, nom, prenom, login, mdp, groupe);
            n++;
        }
        fichier.close();
        return n;
    }

    void adminAjouterEtudiant(const Administratif &adm){
        int nb;
        cout << "\nDonnez le nombre des etudiants a ajouter: ";
        while(!(cin >> nb)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }

        if(!nb) return;
        else if(nb == 1){
            int groupe;
            string nom, prenom, login, mdp;
            bool deja = false;
            bool existe = false;

            cout << "\nNom: ";
            cin >> nom;
            cout << "Prenom: ";
            cin >> prenom;
            cout << "Login: ";
            cin >> login;
            cout << "Mot de passe: ";
            cin >> mdp;
            cout << "Groupe: ";
            while(!(cin >> groupe)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }

            for(auto &g : groupes) { if(g.getId() == groupe) { existe = true; break; } }
            if(!existe){ cout << "\nGroupe introuvable.\n"; return; }

            for (const auto& e : etudiants) { if (e.getLogin() == login) { deja = true; break; } }
            for (const auto& ens : enseignants) { if (ens.getLogin() == login) { deja = true; break; } }
            for (const auto& a : admins) { if (a.getLogin() == login) { deja = true; break; } }

            if(deja)
                cout << "\nLogin existe deja.\n";
            else {
                etudiants.emplace_back(!etudiants.size()?1:etudiants.back().getId()+1, nom, prenom, login, mdp, groupe);
                cout << "\nEtudiant ajoute avec succes.\n";
                journaliser("Ajout d'étudiant",adm.getNom() + " " + adm.getPrenom());
                for(auto &g : groupes) { if(g.getId() == groupe){ g.incrementer(); break; } }
            }
        } else {
            string fichier;
            cout << "\nDonnez le nom du fichier .csv qu'on importe: ";
            cin >> fichier;
            int imp = importerEtudiants(fichier);
            if(imp) {
                cout << "\nLes " << imp << " etudiants sont ajoutes.\n";
                journaliser("Ajout des étudiants",adm.getNom() + " " + adm.getPrenom());
            }
        }
    }

    void adminAjouterEnseignant(const Administratif &adm){
        int id;
        string nom, prenom, login, mdp;
        bool deja = false;
        bool existe = false;

        cout << "\nNom: ";
        cin >> nom;
        cout << "Prenom: ";
        cin >> prenom;
        cout << "ID de module: ";
        while(!(cin >> id)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
        cout << "Login: ";
        cin >> login;
        cout << "Mot de passe: ";
        cin >> mdp;

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
            journaliser("Ajout d'enseignant",adm.getNom() + " " + adm.getPrenom());
        }
    }

    void adminSupprimerEtudiant(const Administratif &adm){
        int id;
        cout << "\nID de l'etudiant a supprimer: ";
        while(!(cin >> id)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }

        for(auto it = etudiants.begin(); it != etudiants.end(); ++it) {
            if(it->getId() == id) {
                int confirm = 0; 
                cout << "\nEtes-vous sur? (Oui = 1, Non = 0)\n" << endl;
                while(!(cin >> confirm)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
                if(confirm){
                    for(auto &g : groupes) { if(g.getId() == it->getGroupe()){ g.decrementer(); break; } }
                    for(auto a = notes.begin(); a != notes.end();) { if (a->getIdEtudiant() == id) { a = notes.erase(a); } else { ++a; } }
                    etudiants.erase(it);
                    cout << "\nEtudiant supprime.\n";
                    journaliser("Suppression d'étudiant",adm.getNom() + " " + adm.getPrenom());
                } else
                    cout << "\nL'etudiant n'est pas supprime.\n";
                return;
            }
        }
        cout << "\nEtudiant introuvable.\n";
    }

    void adminSupprimerEnseignant(const Administratif &adm){
        int id;
        cout << "\nID de l'enseignant a supprimer: ";
        while(!(cin >> id)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }

        for(auto it = enseignants.begin(); it != enseignants.end(); ++it) {
            if(it->getId() == id) {
                int confirm = 0; 
                cout << "\nEtes-vous sur? (Oui = 1, Non = 0)\n" << endl;
                while(!(cin >> confirm)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
                if(confirm){
                    enseignants.erase(it);
                    cout << "\nEnseignant supprime.\n";
                    journaliser("Suppression d'enseignant",adm.getNom() + " " + adm.getPrenom());
                } else
                    cout << "\nL'enseignant n'est pas supprime.\n";
                return;
            }
        }
        cout << "\nEnseignant introuvable.\n";
    }

    void adminModifierEtudiant(const Administratif &adm){
        int id;
        cout << "\nID de l'etudiant a modifier: ";
        while(!(cin >> id)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }

        for(auto &e : etudiants) {
            if(e.getId() == id) {
                int choix;
                do {
                    cout << "\n1. Modifier nom\n";
                    cout << "2. Modifier prenom\n";
                    cout << "3. Modifier login\n";
                    cout << "4. Modifier mot de passe\n";
                    cout << "5. Modifier groupe\n";
                    cout << "0. Retour\n" << endl;
                    while(!(cin >> choix)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }

                    switch (choix) {
                        case 1: {
                            string v;
                            cout << "\nNouveau nom: ";
                            cin >> v;
                            e.setNom(v);
                            break;
                        }
                        case 2: {
                            string v;
                            cout << "\nNouveau prenom: ";
                            cin >> v;
                            e.setPrenom(v);
                            break;
                        }
                        case 3: {
                            string v;
                            cout << "\nNouveau login: ";
                            cin >> v;
                            bool deja = false;
                            for (const auto& ee : etudiants) { if (ee.getLogin() == v) { deja = true; break; } }
                            for (const auto& ens : enseignants) { if (ens.getLogin() == v) { deja = true; break; } }
                            for (const auto& a : admins) { if (a.getLogin() == v) { deja = true; break; } }
                            if(deja) cout << "\nLogin existe deja.\n";
                            else e.setLogin(v);
                            break;
                        }
                        case 4: {
                            string v;
                            cout << "\nNouveau mot de passe: ";
                            cin >> v;
                            e.setMdp(v);
                            break;
                        }
                        case 5: {
                            int gg;
                            bool existe = false;
                            cout << "\nNouveau groupe: ";
                            while(!(cin >> gg)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
                            for(auto &g : groupes) { if(g.getId() == gg){ existe = true; break; } }
                            if(!existe) { cout << "\nGroupe introuvable.\n"; return; }
                            for(auto &g : groupes) { if(g.getId() == e.getGroupe()){ g.decrementer(); break; } }
                            e.setGroupe(gg);
                            for(auto &g : groupes) { if(g.getId() == gg){ g.incrementer(); break; } }
                            break;
                        }
                    }
                } while (choix != 0);

                cout << "\nModification terminee.\n";
                journaliser("Modification d'étudiant",adm.getNom() + " " + adm.getPrenom());
                return;
            }
        }
        cout << "\nEtudiant introuvable.\n";
    }

    void adminModifierEnseignant(const Administratif &adm){
        int id;
        cout << "\nID de l'enseignant a modifier: ";
        while(!(cin >> id)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }

        for(auto &e : enseignants) {
            if(e.getId() == id) {
                int choix;
                do {
                    cout << "\n1. Modifier nom\n";
                    cout << "2. Modifier prenom\n";
                    cout << "3. Modifier login\n";
                    cout << "4. Modifier mot de passe\n";
                    cout << "0. Retour\n" << endl;
                    while(!(cin >> choix)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }

                    switch (choix) {
                        case 1: {
                            string v;
                            cout << "\nNouveau nom: ";
                            cin >> v;
                            e.setNom(v);
                            break;
                        }
                        case 2: {
                            string v;
                            cout << "\nNouveau prenom: ";
                            cin >> v;
                            e.setPrenom(v);
                            break;
                        }
                        case 3: {
                            string v;
                            cout << "\nNouveau login: ";
                            cin >> v;
                            bool deja = false;
                            for (const auto& ee : etudiants) { if (ee.getLogin() == v) { deja = true; break; } }
                            for (const auto& ens : enseignants) { if (ens.getLogin() == v) { deja = true; break; } }
                            for (const auto& a : admins) { if (a.getLogin() == v) { deja = true; break; } }
                            if(deja) cout << "\nLogin existe deja.\n";
                            else e.setLogin(v);
                            break;
                        }
                        case 4: {
                            string v;
                            cout << "\nNouveau mot de passe: ";
                            cin >> v;
                            e.setMdp(v);
                            break;
                        }
                    }
                } while (choix != 0);

                cout << "\nModification terminee.\n";
                journaliser("Modification d'enseignant",adm.getNom() + " " + adm.getPrenom());
                return;
            }
        }
        cout << "\nEnseignant introuvable.\n";
    }

    void adminExporterEtudiantsParGroupe(const Administratif &a) {
        int groupe;
        bool existe = false;
        cout << "\nNumero du groupe: ";
        while(!(cin >> groupe)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
        for(auto &g : groupes) { if(g.getId() == groupe) { existe = true; break; } }
        if(!existe) { cout << "\nGroupe introuvable\n"; return; }
        exporterEtudiantsParGroupe(groupe);
        journaliser("Exportation des etudiants de groupe",a.getNom() + " " + a.getPrenom());
    }

    void adminExporterEnseignants(const Administratif &a) {
        exporterEnseignants();
        journaliser("Exportation des enseignants",a.getNom() + " " + a.getPrenom());
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
            while(!user || (role == 1 && user->getPermissions() != "ETUDIANT") || (role == 2 && user->getPermissions() != "ENSEIGNANT") || (role == 3 && user->getPermissions() != "ADMIN") || (role == 4 && user->getPermissions() != "ETUDIANT")) {
                cout << "\nAuthentification echouee ou role incorrect\n" << endl;
                cout << "Nom d'utilisateur: ";
                if(!getline(cin, login) || login.size() == 0) getline(cin, login);
                if(login == "0") { programme = false; return 0; }
                cout << "Mot de passe: ";
                if(!getline(cin, mdp) || mdp.size() == 0) getline(cin, mdp);
                user = EMSI.authentifier(login, mdp);
            }
            cout << "\n- Connexion etablie en tant que " << user->getNom() << " " << user->getPrenom() << " -" << endl;
            journaliser("Connexion",user->getNom() + " " + user->getPrenom());
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
                        cout << "| 5. Se deconnecter                             |\n";
                        cout << "| 6. Quitter le programme                       |\n";
                        cout << "+------------------------------------------------+\n";
                        choix = lireInt("Choix: ");
                        switch(choix) {
                            case 6: programme = false; cout << "\n+ Programme se termine +" << endl; break;
                            case 1: EMSI.consulterDonnees(*etu); break;
                            case 2: EMSI.consulterNotesEtudiant(*etu); break;
                            case 3: EMSI.consulterAbsencesEtudiant(*etu); break;
                            case 4: EMSI.consulterModulesPourEtudiant(*etu); break;
                            case 5: user = nullptr; cout << "\nUtilisateur se deconnecte.\n" << endl; connecte = false; break;
                            default: cout << "\nChoix invalide\n"; break;
                        }
                    } while (choix != 6 && choix != 5);
            }
            else if(user->getPermissions() == "ENSEIGNANT") {
                Enseignant *ens = dynamic_cast<Enseignant*>(user);
                do {
                        cout << "\n+------------------------------------------------+\n";
                        cout << "|                Menu Enseignant                |\n";
                        cout << "+------------------------------------------------+\n";
                        cout << "| 1. Consulter mes modules                      |\n";
                        cout << "| 2. Lister les etudiants d'un module           |\n";
                        cout << "| 3. Ajouter ou modifier une note               |\n";
                        cout << "| 4. Enregistrer une absence                    |\n";
                        cout << "| 5. Enregistrer un avertissement               |\n";
                        cout << "| 6. Consulter les absences                     |\n";
                        cout << "| 7. Se deconnecter                             |\n";
                        cout << "| 0. Quitter le programme                       |\n";
                        cout << "+------------------------------------------------+\n";
                        choix = lireInt("Choix: ");
                        switch(choix) {
                            case 0: programme = false; cout << "\n+ Programme se termine +" << endl; break;
                            case 1: cout << "\nMes modules: " << ens->getModule() << "\n"; break;
                            case 2: { int idmod = ens->getModule(); cout << "\nModule choisi (id) [par defaut votre module]: " << idmod << "\n"; EMSI.listerEtudiantsDansModule(idmod); break; }
                            case 3: EMSI.enseignantAjouterOuModifierNote(*ens); break;
                            case 4: { int idEtu, hours; cout << "\nID Etudiant: "; cin >> idEtu; cout << "Heures: "; cin >> hours; EMSI.enregistrerAbsence(idEtu, hours); break; }
                            case 5: { int idEtu; cout << "\nID Etudiant pour avertissement: "; cin >> idEtu; EMSI.enregistrerAvertissement(idEtu); break; }
                            case 6: EMSI.afficherAbsencesPourEnseignant(*ens); break;
                            case 7: user = nullptr; cout << "\nUtilisateur se deconnecte.\n" << endl; connecte = false; break;
                            default: cout << "\nChoix invalide\n"; break;
                        }
                    } while (choix != 0 && choix != 7);
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
                    cout << "| 15. Se deconnecter                             |\n";
                    cout << "| 0.  Quitter le programme                       |\n";
                    cout << "+------------------------------------------------+\n";
                    choix = lireInt("Choix: ");
                    switch(choix) {
                        case 0: programme = false; cout << "\n+ Programme se termine +" << endl; break;
                        case 1: EMSI.consulterDonnees(*adm); break;
                        case 2: EMSI.adminAjouterEtudiant(*adm); break;
                        case 3: EMSI.adminAjouterEnseignant(*adm); break;
                        case 4: EMSI.adminSupprimerEtudiant(*adm); break;
                        case 5: EMSI.adminSupprimerEnseignant(*adm); break;
                        case 6: EMSI.adminModifierEtudiant(*adm); break;
                        case 7: EMSI.adminModifierEnseignant(*adm); break;
                        case 8: EMSI.adminExporterEtudiantsParGroupe(*adm); break;
                        case 9: EMSI.adminExporterEnseignants(*adm); break;
                        case 10: EMSI.adminAjouterGroupe(*adm); break;
                        case 11: EMSI.adminSupprimerGroupe(*adm); break;
                        case 12: EMSI.adminConsulterModules(*adm); break;
                        case 13: EMSI.adminAjouterModule(*adm); break;
                        case 14: EMSI.adminSupprimerModule(*adm); break;
                        case 15:
                            journaliser("Déconnexion",user->getNom() + " " + user->getPrenom());
                            user = nullptr;
                            cout << "\nUtilisateur se deconnecte.\n" << endl;
                            connecte = false;
                        break;
                        default: cout << "\nChoix invalide\n";
                    }
                } while (choix != 0 && choix != 15);
            }
        }
    }

    EMSI.sauvegarder();

    return 0;
}

