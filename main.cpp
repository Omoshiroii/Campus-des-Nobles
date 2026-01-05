// Campus des nobles - Alpha - Projet C++ Programmation Orientée Objet
// Taha Zerrad, Salsabil Benhnich, Oussama El Attabi, Rania Mahfoud, Badr Al Fezghari
// Bases de donnéees représentées par des fichiers .txt

// !! pour le test initial, on peut se connecter avec l'admin (Nom d'utilisateur: abcd, Mot de passe: 1234)
// !! pour le test initial, on peut quitter le programme dans le login en entrant (Nom d'utilisateur: 0)

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

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
    Personne(int id, string nom, string prenom,string numTel,string dateNaissance, string login, string mdp)
    : id(id), nom(nom), prenom(prenom),numTel(numTel) , dateNaissance(dateNaissance) , login(login), motDePasse(mdp) { }
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
    void setNumTel(const string& t) { numTel = t; }
    void setDateNaissance(const string& d) { dateNaissance = d; }
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
    Etudiant(int id, string nom, string prenom, string numTel, string dateNaissance,string login, string mdp,  int groupe, float moy, int abs, int avert)
    : Personne(id, nom, prenom, numTel ,dateNaissance, login, mdp), groupe(groupe) , moyenne(moy), nbAbsences(abs), nbAvertissements(avert) { }

    string getPermissions() const override { return "ETUDIANT"; }
    int getGroupe() const { return groupe; }
    float getMoyenne() const { return moyenne; }
    int getNbAbsences() const { return nbAbsences; }
    int getNbAvertissements() const { return nbAvertissements; }

    void setGroupe(int g) { groupe = g; }
    void setMoyenne(float m) { moyenne = m; }
    void setNbAbsences(int a) { nbAbsences = a; }
    void setNbAvertissements(int a) { nbAvertissements = a; }
    string afficher() const override {
        return to_string(id) + ";" + nom + ";" + prenom + ";" + login + ";" + motDePasse + ";" + to_string(groupe);
    }
};

class Employe : public Personne {
protected:
    string poste;
public:
    Employe(int id, string nom, string prenom, string numTel, string dateNaissance, string login, string mdp, string poste)
    : Personne(id, nom, prenom,  numTel ,dateNaissance,login, mdp), poste(poste) { }
};

class Enseignant : public Employe {
private:
    int module;
public:
    Enseignant(int id, string nom, string prenom, string numTel, string dateNaissance, int idmod, string login, string mdp)
    : Employe(id, nom, prenom, numTel ,dateNaissance, login, mdp, "Enseignant"), module(idmod) { }

    string getPermissions() const override { return "ENSEIGNANT"; }
    int getModule() { return module; }

    void setModule(int m) { module =  m; }

    string afficher() const override {
        return to_string(id) + ";" + nom + ";" + prenom + ";" + to_string(module) + ";" + login + ";" + motDePasse;
    }
};

class Administratif : public Employe {
public:
    Administratif(int id, string nom, string prenom,  string numTel, string dateNaissance,string login, string mdp)
    : Employe(id, nom, prenom, numTel ,dateNaissance, login, mdp, "Administratif") { }

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
};

class Module {
private:
    int id;
    string nom;
    float coeff;
    int volumeHoraire;

public:
    Module(int i, string n, float c, int v)
    : id(i), nom(n), coeff(c), volumeHoraire(v) {}


    int getId() const { return id; }
    string getNom() const { return nom; }
    float getCoeff() const { return coeff; }
    int getVolumeHoraire() const { return volumeHoraire; }

    void setCoeff(float c) { coeff = c; }
    void setVolumeHoraire(int v) { volumeHoraire = v; }

    string afficher() const {
        return to_string(id) + ";" + nom;
    }
};

class Groupe {
private:
    int id;
    int effectif;
    int idSalle;

public:
    Groupe(int i, int e ,int s) : id(i), effectif(e) , idSalle(s) { }

    int getId() const { return id; }
    int getEffectif() const { return effectif; }
    int getSalle() const { return idSalle; }
    void setSalle(int s) { idSalle = s; }

    void incrementer() { effectif++; }
    void decrementer() { effectif--; }

    string afficher() const {
    return to_string(id) + ";" + to_string(effectif) + ";" + to_string(idSalle);
}

};

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
        ifstream file;
        string ligne;

        file.open("groupes.txt");
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int id, effectif , salle;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,token,';'); effectif = stoi(token);
            getline(ss,token,';'); salle = stoi(token);

            groupes.emplace_back(id, effectif , salle);
        }
        file.close();

        file.open("modules.txt");
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int id , volume;
            float coeff;
            string nom;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,nom,';');
            getline(ss, token, ';'); coeff = stof(token);
            getline(ss, token, ';'); volume = stoi(token);


            modules.emplace_back(id, nom, coeff , volume);
        }
        file.close();

        file.open("etudiants.txt");
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int id, groupe , abs, avert;
            float moy;
            string nom, prenom, login, mdp, tel, naissance;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,nom,';');
            getline(ss,prenom,';');
            getline(ss,tel,';');
            getline(ss,naissance,';');
            getline(ss,login,';');
            getline(ss,mdp,';');
            getline(ss,token,';'); groupe = stoi(token);
            getline(ss,token,';'); moy = stof(token);
            getline(ss,token,';'); abs = stoi(token);
            getline(ss,token,';'); avert = stoi(token);

            etudiants.emplace_back(id, nom, prenom, tel, naissance,login, mdp, groupe , moy, abs, avert);
        }
        file.close();

        file.open("enseignants.txt");
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int id,idmod;
            string nom, prenom, login, mdp, tel, naissance;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,nom,';');
            getline(ss,prenom,';');
            getline(ss,token,';'); idmod = stoi(token);
            getline(ss,login,';');
            getline(ss,mdp,';');
            getline(ss, tel, ';');
            getline(ss, naissance, ';');

            enseignants.emplace_back(id, nom, prenom,,tel, naissance , idmod, login, mdp );
        }
        file.close();

        file.open("administratifs.txt");
        while (getline(file, ligne)) {
            stringstream ss(ligne);
            string token;
            int id;
            string nom, prenom, login, mdp , tel, naissance;

            getline(ss,token,';'); id = stoi(token);
            getline(ss,nom,';');
            getline(ss,prenom,';');
            getline(ss,login,';');
            getline(ss,mdp,';');
            getline(ss, tel, ';');
            getline(ss, naissance, ';');

            admins.emplace_back(id, nom, prenom, , tel, naissance ,login, mdp );
        }
        file.close();

        file.open("notes.txt");
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
        ofstream file;

        file.open("groupes.txt");
        for(auto &g : groupes) {
            file << g.afficher() << endl;
        }
        file.close();

        file.open("modules.txt");
        for(auto &m : modules) {
            file << m.afficher() << endl;
        }
        file.close();

        file.open("etudiants.txt");
        for(auto &e : etudiants) {
            file << e.afficher() << endl;
        }
        file.close();

        file.open("enseignants.txt");
        for(auto &ens : enseignants) {
            file << ens.afficher() << endl;
        }
        file.close();

        file.open("administratifs.txt");
        for(auto &a : admins) {
            file << a.afficher() << endl;
        }
        file.close();

        file.open("notes.txt");
        for(auto &n : notes) {
            file << n.afficher() << endl;
        }
        file.close();
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

    void ajouterNote(int idEtudiant, int idModule, float valeur) {
        bool existe1 = false;
        bool existe2 = false;
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
        if(valeur > 20 || valeur < 0){
            cout << "\nNote invalide.\n";
            return;
        }
        notes.emplace_back(idEtudiant, idModule, valeur);
        cout << "\nNote ajoutee avec succes.\n";
    }

    void supprimerNote(int idEtudiant, int idModule){
        bool existe = false;
        for(auto &e : etudiants) { if(e.getId() == idEtudiant) { existe = true; break; } }
        if(!existe) {
            cout << "\nEtudiant introuvable.\n";
            return;
        }
        for(auto e = etudiants.begin(); e != etudiants.end(); ++e) {
            if (e->getId() == idEtudiant) {
                for(auto a = notes.begin(); a != notes.end();) {
                    if (a->getIdEtudiant() == e->getId() && a->getIdModule() == idModule) {
                        a = notes.erase(a);
                        cout << "\nNote supprimee.\n";
                    } else {
                        ++a;
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

    void enseignantAjouterNote(Enseignant &e) {
        int idEtu;
        float note;
        cout << "\nID Etudiant: ";
        cin >> idEtu;
        cout << "Note: ";
        cin >> note;
        ajouterNote(idEtu, e.getModule(), note);
    }

    void enseignantSupprimerNote(Enseignant &e) {
        int idEtu;
        cout << "\nID Etudiant: ";
        cin >> idEtu;
        supprimerNote(idEtu, e.getModule());
    }

    void enseignantConsulterNotes(Enseignant &e) const {
        cout << "\n--- Liste des notes ---\n";
        for(const auto &n : notes) {
            if(n.getIdModule() == e.getModule()){
                cout << "Etudiant " << n.getIdEtudiant() << " | Note " << n.getValeur() << "\n";
            }
        }
    }

    void consulterDonnees(const Etudiant &p) const {
        cout << "\n--- Mes informations ---\n";
        cout << "ID: " << p.getId() << "\n";
        cout << "Nom: " << p.getNom() << "\n";
        cout << "Prenom: " << p.getPrenom() << "\n";
        cout << "Groupe: " << p.getGroupe() << "\n";
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
        cout << "ID: " << p.getId() << "\n";
        cout << "Nom: " << p.getNom() << "\n";
        cout << "Prenom: " << p.getPrenom() << "\n";
    }

    void adminConsulterModules() const{
        bool existe = false;
        for(auto &m : modules) { existe = true; cout << "\n" << to_string(m.getId()) << ". " << m.getNom(); }
        cout << "\n";
        if(!existe) cout << "Aucun module.\n";
    }

    void adminAjouterModule(){ // a modifier aussi
        int id = (!modules.size())?1:modules.back().getId()+1;
        string modu;
        cout << "\nNom de module: ";
        cin >> modu;
        modules.emplace_back(id,modu);
        cout << "\nModule ajoute.\n";
    }

    void adminSupprimerModule(){
        int id;
        cout << "\nID de module a supprimer: ";
        cin >> id;
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
        cout << "\nID de groupe a supprimer: ";
        cin >> id;
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
        int groupe ,abs, avert;
        string nom, prenom,tel, naissance, login, mdp;
        float moy;
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
        cin >> groupe;
        cout << "Telephone: ";
        cin >> tel;
        cout << "Date de naissance: ";
        cin >> naissance;
        cout << "Moyenne: ";
        cin >> moy;
        cout << "Nombre d'absences: ";
        cin >> abs;
        cout << "Nombre d'avertissements: ";
        cin >> avert;

        for(auto &g : groupes) { if(g.getId() == groupe) { existe = true; break; } }
        if(!existe){ cout << "\nGroupe introuvable.\n"; return; }

        for (const auto& e : etudiants) { if (e.getLogin() == login) { deja = true; break; } }
        for (const auto& ens : enseignants) { if (ens.getLogin() == login) { deja = true; break; } }
        for (const auto& a : admins) { if (a.getLogin() == login) { deja = true; break; } }

        if(deja)
            cout << "\nLogin existe deja.\n";
        else {
            etudiants.emplace_back(!etudiants.size()?1:etudiants.back().getId()+1, nom, prenom, login, mdp,tel, naissance,groupe, moy, abs, avert);
            for(auto &g : groupes) { if(g.getId() == groupe){ g.incrementer(); break; } }
        }
    }

    void adminAjouterEnseignant(){
        int id;
        string nom, prenom, login, mdp;
        bool deja = false;
        bool existe = false;

        cout << "\nNom: ";
        cin >> nom;
        cout << "Prenom: ";
        cin >> prenom;
        cout << "ID de module: ";
        cin >> id;
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
        }
    }

    void adminSupprimerEtudiant(){
        int id;
        cout << "\nID de l'etudiant a supprimer: ";
        cin >> id;

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
        int id;
        cout << "\nID de l'enseignant a supprimer: ";
        cin >> id;

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
        int id;
        cout << "\nID de l'etudiant a modifier: ";
        cin >> id;

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
                    cin >> choix;

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
                            cin >> gg;
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
                return;
            }
        }
        cout << "\nEtudiant introuvable.\n";
    }

    void adminModifierEnseignant(){
        int id;
        cout << "\nID de l'enseignant a modifier: ";
        cin >> id;

        for(auto &e : enseignants) {
            if(e.getId() == id) {
                int choix;
                do {
                    cout << "\n1. Modifier nom\n";
                    cout << "2. Modifier prenom\n";
                    cout << "3. Modifier login\n";
                    cout << "4. Modifier mot de passe\n";
                    cout << "0. Retour\n" << endl;
                    cin >> choix;

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
                return;
            }
        }
        cout << "\nEnseignant introuvable.\n";
    }

    void adminExporterEtudiantsParGroupe() {
        int groupe;
        bool existe = false;
        cout << "\nNumero du groupe: ";
        cin >> groupe;
        for(auto &g : groupes) { if(g.getId() == groupe) { existe = true; break; } }
        if(!existe) { cout << "\nGroupe introuvable\n"; return; }
        exporterEtudiantsParGroupe(groupe);
    }

    void adminExporterEnseignants() {
        exporterEnseignants();
    }
};

ostream& operator<<(ostream& os, const Personne& p){
    os << p.getId() << " | " << p.getNom() << " " << p.getPrenom()
       << " | Tel: " << p.getNumTel();
    return os;
}

ostream& operator<<(ostream& os, const Etudiant& e){
    os << static_cast<const Personne&>(e)
       << " | Groupe: " << e.getGroupe()
       << " | Moyenne: " << e.getMoyenne()
       << " | Absences: " << e.getNbAbsences()
       << " | Avertissements: " << e.getNbAvertissements();
    return os;
}

ostream& operator<<(ostream& os, const Module& m){
    os << m.getId() << " - " << m.getNom()
       << " | Coeff: " << m.getCoeff()
       << " | Volume: " << m.getVolumeHoraire() << "h";
    return os;
}

ostream& operator<<(ostream& os, const Groupe& g){
    os << "Groupe " << g.getId()
       << " | Effectif: " << g.getEffectif()
       << " | Salle: " << g.getSalle();
    return os;
}


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
            cin >> login;
            if(login == "0") { programme = false; break; } // !! pour le test initial
            cout << "Mot de passe: ";
            cin >> mdp;
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
            connecte = true;
        } else {
            if(user->getPermissions() == "ETUDIANT") {
                Etudiant *etu = dynamic_cast<Etudiant*>(user);
                do {
                    cout << "\n1. Consulter mes donnees\n";
                    cout << "2. Exporter mes notes\n";
                    cout << "3. Deconnexion\n";
                    cout << "0. Quitter\n" << endl;
                    cin >> choix;
                    switch(choix) {
                        case 0:
                            programme = false; cout << "\n+ Programme se termine +" << endl;
                        break;
                        case 1:
                            EMSI.consulterDonnees(*etu);
                        break;
                        case 2:
                            EMSI.etudiantExporterNotes(*etu);
                        break;
                        case 3:
                            user = nullptr; cout << "\nUtilisateur se deconnecte.\n" << endl; connecte = false;
                        break;
                        default:
                            cout << "\nChoix invalide\n";
                    }
                } while (choix != 0 && choix != 3);
            }
            else if(user->getPermissions() == "ENSEIGNANT") {
                Enseignant *ens = dynamic_cast<Enseignant*>(user);
                do {
                    cout << "\n1. Consulter mes donnees\n";
                    cout << "2. Ajouter une note\n";
                    cout << "3. Supprimer une note\n";
                    cout << "4. Consulter toutes les notes\n";
                    cout << "5. Deconnexion\n";
                    cout << "0. Quitter\n" << endl;
                    cin >> choix;
                    switch(choix) {
                        case 0:
                            programme = false; cout << "\n+ Programme se termine +" << endl;
                        break;
                        case 1:
                            EMSI.consulterDonnees(*ens);
                        break;
                        case 2:
                            EMSI.enseignantAjouterNote(*ens);
                        break;
                        case 3:
                            EMSI.enseignantSupprimerNote(*ens);
                        break;
                        case 4:
                            EMSI.enseignantConsulterNotes(*ens);
                        break;
                        case 5:
                            user = nullptr; cout << "\nUtilisateur se deconnecte.\n" << endl; connecte = false;
                        break;
                        default:
                            cout << "\nChoix invalide\n";
                    }
                } while (choix != 0 && choix != 5);
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
                    cin >> choix;
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
                        case 15:
                            user = nullptr; cout << "\nUtilisateur se deconnecte.\n" << endl; connecte = false;
                        break;
                        default:
                            cout << "\nChoix invalide\n";
                    }
                } while (choix != 0 && choix != 15);
            }
        }
    }

    EMSI.sauvegarder();

    return 0;
}
