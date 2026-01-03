// Campus des nobles - Beta - Projet C++ Programmation Orientée Objet
// Taha Zerrad, Salsabil Benhnich, Oussama El Attabi, Rania Mahfoud, Badr Al Fezghari

// !! pour le test initial, on peut se connecter avec l'admin (Nom d'utilisateur: abcd, Mot de passe: 1234)
// !! pour le test initial, on peut quitter le programme dans le login en entrant (Nom d'utilisateur: 0)

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
#include <limits>
#include <chrono>
#include <ctime>

using namespace std;

class Personne {
protected:
    int id;
    string nom;
    string prenom;
    string login;
    string motDePasse;
public:
    Personne(int id, string nom, string prenom, string login, string mdp)
    : id(id), nom(nom), prenom(prenom), login(login), motDePasse(mdp) { }
    virtual ~Personne() { }

    virtual string getPermissions() const = 0;
    int getId() const { return id; }
    string getNom() const { return nom; }
    string getPrenom() const { return prenom; }
    string getLogin() const { return login; }
    string getMotDePasse() const { return motDePasse; }

    void setNom(const string &n) { nom = n; }
    void setPrenom(const string &p) { prenom = p; }
    void setLogin(const string &l) { login = l; }
    void setMdp(const string &m) { motDePasse = m; }

    virtual string afficher() const = 0;
};

class Etudiant : public Personne {
private:
    int groupe;
public:
    Etudiant(int id, string nom, string prenom, string login, string mdp, int groupe)
    : Personne(id, nom, prenom, login, mdp), groupe(groupe) { }

    string getPermissions() const override { return "ETUDIANT"; }
    int getGroupe() const { return groupe; }

    void setGroupe(int g) { groupe = g; }

    string afficher() const override {
        return to_string(id) + ";" + nom + ";" + prenom + ";" + login + ";" + motDePasse + ";" + to_string(groupe);
    }
};

class Employe : public Personne {
protected:
    string poste;
public:
    Employe(int id, string nom, string prenom, string login, string mdp, string poste)
    : Personne(id, nom, prenom, login, mdp), poste(poste) { }
};

class Enseignant : public Employe {
private:
    int module;
public:
    Enseignant(int id, string nom, string prenom, int idmod, string login, string mdp)
    : Employe(id, nom, prenom, login, mdp, "Enseignant"), module(idmod) { }

    string getPermissions() const override { return "ENSEIGNANT"; }
    int getModule() { return module; }

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
public:
    void charger() {
        ifstream fichier;
        string ligne;

        fichier.open("groupes.txt");
        while (getline(fichier, ligne)) {
            stringstream ss(ligne);
            string token;
            int id, effectif;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,token,';'); effectif = stoi(token);

            groupes.emplace_back(id, effectif);
        }
        fichier.close();

        fichier.open("modules.txt");
        while (getline(fichier, ligne)) {
            stringstream ss(ligne);
            string token;
            int id;
            string nom;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,nom,';');

            modules.emplace_back(id, nom);
        }
        fichier.close();

        fichier.open("etudiants.txt");
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
        }
        fichier.close();

        fichier.open("enseignants.txt");
        while (getline(fichier, ligne)) {
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
        fichier.close();

        fichier.open("administratifs.txt");
        while (getline(fichier, ligne)) {
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
        fichier.close();

        fichier.open("notes.txt");
        while (getline(fichier, ligne)) {
            stringstream ss(ligne);
            string token;
            int idEtu, idMod;
            float note;

            getline(ss,token,';'); idEtu = stoi(token);
            getline(ss,token,';'); idMod = stoi(token);
            getline(ss,token,';'); note = stof(token);

            notes.emplace_back(idEtu, idMod, note);
        }
        fichier.close();

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

    void enseignantAjouterNote(Enseignant &e) {
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

    void consulterDonnees(const Etudiant &e) const {
        cout << "\n--- Mes informations ---\n";
        cout << "ID: " << e.getId() << "\n";
        cout << "Nom: " << e.getNom() << "\n";
        cout << "Prenom: " << e.getPrenom() << "\n";
        cout << "Groupe: " << e.getGroupe() << "\n";
        journaliser("Consultation des données",e.getNom() + " " + e.getPrenom());
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
        cout << "\nID de groupe a supprimer: ";
        while(!(cin >> id)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
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

    cout << "- - - - - - - - - - - - - - - - -\n- - - Bienvenue dans l'EMSI - - -\n- - - - - - - - - - - - - - - - -\n" << endl;

    while(programme){
        if(!connecte){
            cout << "Nom d'utilisateur: ";
            if(cin >> login){}else{cin.clear();}
            if(login == "0") { programme = false; break; } // !! pour le test initial
            cout << "Mot de passe: ";
            if(cin >> mdp){}else{cin.clear();}
            user = EMSI.authentifier(login, mdp);
            while(!user) {
                cout << "\nAuthentification echouee\n" << endl;
                cout << "Nom d'utilisateur: ";
                cin >> login;
                if(login == "0") { programme = false; return 0; } // !! pour le test initial
                cout << "Mot de passe: ";
                cin >> mdp;
                user = EMSI.authentifier(login, mdp);
            }
            cout << "\n- Connexion etablie en tant que " << user->getNom() << " " << user->getPrenom() << " -" << endl;
            journaliser("Connexion",user->getNom() + " " + user->getPrenom());
            connecte = true;
        } else {
            if(user->getPermissions() == "ETUDIANT") {
                Etudiant *etu = dynamic_cast<Etudiant*>(user);
                do {
                    cout << "\n1. Consulter mes donnees\n";
                    cout << "2. Exporter mes notes\n";
                    cout << "3. Deconnexion\n";
                    cout << "0. Quitter\n" << endl;
                    while(!(cin >> choix)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
                    switch(choix) {
                        case 0: programme = false; cout << "\n+ Programme se termine +" << endl; break;
                        case 1: EMSI.consulterDonnees(*etu); break;
                        case 2: EMSI.etudiantExporterNotes(*etu); break;
                        case 3:
                            journaliser("Déconnexion",user->getNom() + " " + user->getPrenom());
                            user = nullptr;
                            cout << "\nUtilisateur se deconnecte.\n" << endl;
                            connecte = false;
                        break;
                        default: cout << "\nChoix invalide\n";
                    }
                } while (choix != 0 && choix != 3);
            }
            else if(user->getPermissions() == "ENSEIGNANT") {
                Enseignant *ens = dynamic_cast<Enseignant*>(user);
                do {
                    cout << "\n1. Consulter mes donnees\n";
                    cout << "2. Ajouter une note\n";
                    cout << "3. Supprimer une note\n";
                    cout << "4. Modifier une note\n";
                    cout << "5. Consulter toutes les notes\n";
                    cout << "6. Calculer la moyenne d'une groupe\n";
                    cout << "7. Deconnexion\n";
                    cout << "0. Quitter\n" << endl;
                    while(!(cin >> choix)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
                    switch(choix) {
                        case 0: programme = false; cout << "\n+ Programme se termine +" << endl; break;
                        case 1: EMSI.consulterDonnees(*ens); break;
                        case 2: EMSI.enseignantAjouterNote(*ens); break;
                        case 3: EMSI.enseignantSupprimerNote(*ens); break;
                        case 4: EMSI.enseignantModifierNote(*ens); break;
                        case 5: EMSI.enseignantConsulterNotes(*ens); break;
                        case 6: EMSI.enseignantCalculerMoyenneGroupe(*ens); break;
                        case 7:
                            journaliser("Déconnexion",user->getNom() + " " + user->getPrenom());
                            user = nullptr;
                            cout << "\nUtilisateur se deconnecte.\n" << endl;
                            connecte = false;
                        break;
                        default: cout << "\nChoix invalide\n";
                    }
                } while (choix != 0 && choix != 7);
            }
            else if(user->getPermissions() == "ADMIN") {
                Administratif *adm = dynamic_cast<Administratif*>(user);
                do {
                    cout << "\n1. Consulter mes donnes\n";
                    cout << "2. Ajouter un etudiant\n";
                    cout << "3. Ajouter un enseignant\n";
                    cout << "4. Supprimer un etudiant\n";
                    cout << "5. Supprimer un enseignant\n";
                    cout << "6. Modifier un etudiant\n";
                    cout << "7. Modifier un enseignant\n";
                    cout << "8. Exporter etudiants par groupe\n";
                    cout << "9. Exporter enseignants\n";
                    cout << "10. Ajouter un groupe\n";
                    cout << "11. Supprimer un groupe\n";
                    cout << "12. Consulter toutes les modules\n";
                    cout << "13. Ajouter un module\n";
                    cout << "14. Supprimer un module\n";
                    cout << "15. Deconnexion\n";
                    cout << "0. Quitter\n" << endl;
                    while(!(cin >> choix)){ cout << "\nInvalide\n" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
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
