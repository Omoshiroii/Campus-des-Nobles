// Campus des nobles (pour fichiers .txt)
// pour le test initial, on peut se connecter avec l'admin (Nom d'utilisateur: abcd, Mot de passe: 1234)
// pour le test initial, on peut quitter le programme dans le login en entrant (Nom d'utilisateur: 0)

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
    string login;
    string motDePasse;
public:
    Personne(int id, string nom, string prenom, string login, string mdp)
    : id(id), nom(nom), prenom(prenom), login(login), motDePasse(mdp) {}
    virtual ~Personne() {}

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
    : Personne(id, nom, prenom, login, mdp), groupe(groupe) {}

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
    : Personne(id, nom, prenom, login, mdp), poste(poste) {}
};

class Enseignant : public Employe {
private:
    int module;
public:
    Enseignant(int id, string nom, string prenom, int idmod, string login, string mdp)
    : Employe(id, nom, prenom, login, mdp, "Enseignant"), module(idmod) {}

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
    : Employe(id, nom, prenom, login, mdp, "Administratif") {}

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
    : idEtudiant(idEtu), idModule(idMod), valeur(val) {}

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
public:
    Module(int i, string n)
    : id(i), nom(n) {}

    int getId() const { return id; }
    string getNom() const { return nom; }

    string afficher() const {
        return to_string(id) + ";" + nom;
    }
};

// à ajouter
/*class Groupe {
private:
    int id;
public:
    Group(int i) : id(i) {}

    int getId() const { return id; }
};*/

class Etablissement {
private:
    vector<Etudiant> etudiants;
    vector<Enseignant> enseignants;
    vector<Administratif> admins;
    vector<Note> notes;
    vector<Module> modules;
    // vector<Groupe> groupes;
public:
    void charger() {
        ifstream file;
        string ligne;

        file.open("etudiants.txt");
        while (getline(file, ligne)) {
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
        file.close();

        file.open("enseignants.txt");
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

        file.open("administratifs.txt");
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
   
        modules.emplace_back(1,"POO");
        modules.emplace_back(2,"Developpement Web");
        modules.emplace_back(3,"Communication Pro");

        // pour le test initial, il existe un admin (Nom d'utilisateur: abcd, Mot de passe: 1234)
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
        bool existe = false;
        for(auto &e : etudiants) {
            if(e.getId() == idEtudiant) {
                existe = true;
                break;
            }
        }
        if(!existe) {
            cout << "\nEtudiant introuvable.\n";
            return;
        }
        if(idModule > modules.size()) {
            cout << "\nModule introuvable.\n";
            return;
        }
        // à ajouter: test si la valeur est valide (entre 0 et 20)
        notes.emplace_back(idEtudiant, idModule, valeur);
        cout << "\nNote ajoutee avec succes.\n";
    }

    // à ajouter: modifierNote(); supprimerNote(); ajouterModule(); supprimerModule(int idModule);

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

    void etudiantConsulterDonnees(const Etudiant &e) const{
        cout << "\n--- Mes informations ---\n";
        cout << "ID: " << e.getId() << "\n";
        cout << "Nom: " << e.getNom() << "\n";
        cout << "Prenom: " << e.getPrenom() << "\n";
        cout << "Groupe: " << e.getGroupe() << "\n";
    }

    void etudiantExporterNotes(const Etudiant &e) {
        exporterNotesEtudiant(e.getId());
    }

    void enseignantConsulterDonnees(Enseignant &e) const{
        cout << "\n--- Mes informations ---\n";
        cout << "ID: " << e.getId() << "\n";
        cout << "Nom: " << e.getNom() << "\n";
        cout << "Prenom: " << e.getPrenom() << "\n";
        cout << "ID de module: " << e.getModule() << "\n";
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

    void enseignantConsulterNotes(Enseignant &e) const {
        cout << "\n--- Liste des notes ---\n";
        for(const auto &n : notes) {
            if(n.getIdModule() == e.getModule()){
                cout << "Etudiant " << n.getIdEtudiant() << " | Note " << n.getValeur() << "\n";
            }
        }
    }

    void adminConsulterDonnees(const Administratif &a) const{
        cout << "\n--- Mes informations ---\n";
        cout << "ID: " << a.getId() << "\n";
        cout << "Nom: " << a.getNom() << "\n";
        cout << "Prenom: " << a.getPrenom() << "\n";
    }
    
    void adminAjouterEtudiant(){
        int id, groupe;
        string nom, prenom, login, mdp;

        cout << "\nID: "; // à ajouter: rendre les IDs automatiques (etudiants.size() + 1)
        cin >> id;
        cout << "Nom: ";
        cin >> nom;
        cout << "Prenom: ";
        cin >> prenom;
        cout << "Login: ";
        cin >> login;
        cout << "Mot de passe: ";
        cin >> mdp;
        cout << "Groupe: ";
        cin >> groupe;

        // à ajouter: tester si le groupe, l'id et login déjà existent
        etudiants.emplace_back(id, nom, prenom, login, mdp, groupe);
        cout << "\nEtudiant ajoute avec succes.\n";
    }
    void adminAjouterEnseignant(){
        int id,idmod;
        string nom, prenom, login, mdp;

        cout << "\nID: "; // à ajouter: rendre les IDs automatiques (100 + enseignants.size() + 1)
        cin >> id;
        cout << "Nom: ";
        cin >> nom;
        cout << "Prenom: ";
        cin >> prenom;
        cout << "ID de module: ";
        cin >> idmod;
        cout << "Login: ";
        cin >> login;
        cout << "Mot de passe: ";
        cin >> mdp;

        // à ajouter: tester si l'id et login déjà existent
        if(idmod > modules.size())
            cout << "\nModule introuvable.\n";
        else {
            enseignants.emplace_back(id, nom, prenom, idmod, login, mdp);
            cout << "\nEnseignant ajoute avec succes.\n";
        }
    }

    void adminSupprimerEtudiant(){
        int id;
        cout << "\nID de l'etudiant a supprimer: ";
        cin >> id;

        for(auto it = etudiants.begin(); it != etudiants.end(); ++it) {
            if(it->getId() == id) {
                etudiants.erase(it);
                /*for(auto a = notes.begin(); a != notes.end(); ++a){
                    if(a->getIdEtudiant() == id) notes.erase(a);
                }*/ // à ajouter: correction de cette partie, supprimer les notes reliés à l'étudiant supprimé
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
                            e.setLogin(v);
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
                            int g;
                            cout << "\nNouveau groupe: ";
                            cin >> g;
                            e.setGroupe(g);
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
                            e.setLogin(v);
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

    // à ajouter: adminAjouterAdmin(), adminSupprimerAdmin() et adminModifierAdmin() ? ? ?

    void adminExporterEtudiantsParGroupe() {
        int groupe;
        cout << "\nNumero du groupe: ";
        cin >> groupe;
        // à ajouter: teste si le groupe existe
        exporterEtudiantsParGroupe(groupe);
    }

    void adminExporterEnseignants() {
        exporterEnseignants();
    }
};

int main() {
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
            if(login == "0") { programme = false; return 0; } // pour le test initial
            cout << "Mot de passe: ";
            cin >> mdp;
            user = EMSI.authentifier(login, mdp);
            while(!user) {
                cout << "\nAuthentification echouee\n" << endl;
                cout << "Nom d'utilisateur: ";
                cin >> login;
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
                            EMSI.etudiantConsulterDonnees(*etu);
                        break;
                        case 2:
                            EMSI.etudiantExporterNotes(*etu);
                        break;
                        case 3:
                            user = nullptr; cout << "\nUtilisateur se deconnecte\n" << endl; connecte = false;
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
                    cout << "3. Consulter toutes les notes\n";
                    cout << "4. Deconnexion\n";
                    cout << "0. Quitter\n" << endl;
                    cin >> choix;
                    switch(choix) {
                        case 0:
                            programme = false; cout << "\n+ Programme se termine +" << endl;
                        break;
                        case 1:
                            EMSI.enseignantConsulterDonnees(*ens);
                        break;
                        case 2:
                            EMSI.enseignantAjouterNote(*ens);
                        break;
                        case 3:
                            EMSI.enseignantConsulterNotes(*ens);
                        break;
                        case 4:
                            user = nullptr; cout << "\nUtilisateur se deconnecte\n" << endl; connecte = false;
                        break;
                        default:
                            cout << "\nChoix invalide\n";
                    }
                } while (choix != 0 && choix != 4);
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
                    cout << "10. Deconnexion\n";
                    cout << "0. Quitter\n" << endl;
                    cin >> choix;
                    switch(choix) {
                        case 0:
                            programme = false; cout << "\n+ Programme se termine +" << endl;
                        break;
                        case 1:
                            EMSI.adminConsulterDonnees(*adm);
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
                            user = nullptr; cout << "\nUtilisateur se deconnecte\n" << endl; connecte = false;
                        break;
                        default:
                            cout << "\nChoix invalide\n";
                    }
                } while (choix != 0 && choix != 10);
            }
        }
    }
    EMSI.sauvegarder();
    return 0;
}

// des idées supplémentaires à ajouter, on peut les faire après: 
// - fichier .log pour stocker chaque action [Date | Action | User] (supplémentaire, on peut le faire après)
// - surcharge d'opérateur << dans chacune des classes
// - confirmation avant de supprimer étudiant/enseignant
// - autres fonctions qui peuvent être utiles
// - dossiers pour distinguer les rapports, les fichiers de base de donnees, les fichiers de programme et les headers
