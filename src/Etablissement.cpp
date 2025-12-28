#include "Etablissement.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Etablissement::Etablissement() {
}

Etablissement::~Etablissement() {
}

// ============================================
// CHARGEMENT DES FICHIERS
// ============================================

void Etablissement::charger() {
    ifstream file;
    string ligne;

    // Charger groupes.txt (inchangé)
    file.open("groupes.txt");
    while (getline(file, ligne)) {
        stringstream ss(ligne);
        string token;
        int id, effectif;

        getline(ss, token, ';'); id = stoi(token);
        getline(ss, token, ';'); effectif = stoi(token);

        groupes.emplace_back(id, effectif);
    }
    file.close();

    // Charger modules.txt (inchangé)
    file.open("modules.txt");
    while (getline(file, ligne)) {
        stringstream ss(ligne);
        string token;
        int id;
        string nom;

        getline(ss, token, ';'); id = stoi(token);
        getline(ss, nom, ';');

        modules.emplace_back(id, nom);
    }
    file.close();

    // Charger etudiants.txt (avec absences et warnings)
    file.open("etudiants.txt");
    while (getline(file, ligne)) {
        stringstream ss(ligne);
        string token;
        int id, groupe;
        string nom, prenom, login, mdp, absencesStr, warningsStr;

        getline(ss, token, ';'); id = stoi(token);
        getline(ss, nom, ';');
        getline(ss, prenom, ';');
        getline(ss, login, ';');
        getline(ss, mdp, ';');
        getline(ss, token, ';'); groupe = stoi(token);

        Etudiant etu(id, nom, prenom, login, mdp, groupe);

        // Load absences
        if(getline(ss, absencesStr, ';') && !absencesStr.empty()) {
            stringstream absStream(absencesStr);
            string absence;
            while(getline(absStream, absence, '|')) {
                etu.ajouterAbsence(absence);
            }
        }

        // Load warnings
        if(getline(ss, warningsStr, ';') && !warningsStr.empty()) {
            stringstream warnStream(warningsStr);
            string warning;
            while(getline(warnStream, warning, '|')) {
                etu.ajouterWarning(warning);
            }
        }

        etudiants.push_back(etu);
    }
    file.close();

    // Charger enseignants.txt (UPDATED - avec modules multiples)
    file.open("enseignants.txt");
    while (getline(file, ligne)) {
        stringstream ss(ligne);
        string token;
        int id;
        double salaire;
        string nom, prenom, login, mdp, modulesStr;
        vector<int> modulesList;

        getline(ss, token, ';'); id = stoi(token);
        getline(ss, nom, ';');
        getline(ss, prenom, ';');
        getline(ss, modulesStr, ';');

        // Parse modules (can be single or multiple separated by |)
        stringstream modStream(modulesStr);
        string moduleToken;
        while(getline(modStream, moduleToken, '|')) {
            modulesList.push_back(stoi(moduleToken));
        }

        getline(ss, login, ';');
        getline(ss, mdp, ';');

        // Try to read salaire, default to 0 if not present
        if(getline(ss, token, ';')) {
            salaire = stod(token);
        } else {
            salaire = 0.0;
        }

        enseignants.emplace_back(id, nom, prenom, modulesList, login, mdp, salaire);
    }
    file.close();

    // Charger administratifs.txt (UPDATED - avec salaire)
    file.open("administratifs.txt");
    while (getline(file, ligne)) {
        stringstream ss(ligne);
        string token;
        int id;
        double salaire;
        string nom, prenom, login, mdp;

        getline(ss, token, ';'); id = stoi(token);
        getline(ss, nom, ';');
        getline(ss, prenom, ';');
        getline(ss, login, ';');
        getline(ss, mdp, ';');

        // Try to read salaire, default to 0 if not present
        if(getline(ss, token, ';')) {
            salaire = stod(token);
        } else {
            salaire = 0.0;
        }

        admins.emplace_back(id, nom, prenom, login, mdp, salaire);
    }
    file.close();

    // Charger notes.txt (inchangé)
    file.open("notes.txt");
    while (getline(file, ligne)) {
        stringstream ss(ligne);
        string token;
        int idEtu, idMod;
        float note;

        getline(ss, token, ';'); idEtu = stoi(token);
        getline(ss, token, ';'); idMod = stoi(token);
        getline(ss, token, ';'); note = stof(token);

        notes.emplace_back(idEtu, idMod, note);
    }
    file.close();

    // Initialisation pour tests (modules par défaut)
    if(!modules.size()) {
        ofstream fichier;
        fichier.open("modules.txt");
        fichier << "1;POO" << endl;
        fichier << "2;Developpement Web" << endl;
        fichier << "3;Communication Pro" << endl;
        modules.emplace_back(1, "POO");
        modules.emplace_back(2, "Developpement Web");
        modules.emplace_back(3, "Communication Pro");
        fichier.close();
    }

    // Initialisation pour tests (admin par défaut)
    if(!admins.size()) {
        ofstream fichier;
        fichier.open("administratifs.txt");
        fichier << "201;Test;Admin;abcd;1234;5000" << endl;
        admins.emplace_back(201, "Test", "Admin", "abcd", "1234", 5000);
        fichier.close();
    }
}

// ============================================
// SAUVEGARDE DES FICHIERS
// ============================================

void Etablissement::sauvegarder() {
    ofstream file;

    // Sauvegarder groupes
    file.open("groupes.txt");
    for(auto &g : groupes) {
        file << g.afficher() << endl;
    }
    file.close();

    // Sauvegarder modules
    file.open("modules.txt");
    for(auto &m : modules) {
        file << m.afficher() << endl;
    }
    file.close();

    // Sauvegarder etudiants (avec absences et warnings)
    file.open("etudiants.txt");
    for(auto &e : etudiants) {
        file << e.afficher() << endl;
    }
    file.close();

    // Sauvegarder enseignants (avec modules multiples)
    file.open("enseignants.txt");
    for(auto &ens : enseignants) {
        file << ens.afficher() << endl;
    }
    file.close();

    // Sauvegarder administratifs (avec salaire)
    file.open("administratifs.txt");
    for(auto &a : admins) {
        file << a.afficher() << endl;
    }
    file.close();

    // Sauvegarder notes
    file.open("notes.txt");
    for(auto &n : notes) {
        file << n.afficher() << endl;
    }
    file.close();
}

// ============================================
// ETUDIANT: CONSULTER ABSENCES
// ============================================

void Etablissement::etudiantConsulterAbsences(Etudiant &e) {
    cout << "\n--- Mes absences ---\n";
    if(e.getAbsences().empty()) {
        cout << "Aucune absence enregistree.\n";
        return;
    }
    for(size_t i = 0; i < e.getAbsences().size(); i++) {
        cout << i+1 << ". " << e.getAbsences()[i] << "\n";
    }
}

// ============================================
// ETUDIANT: CONSULTER WARNINGS
// ============================================

void Etablissement::etudiantConsulterWarnings(Etudiant &e) {
    cout << "\n--- Mes avertissements ---\n";
    if(e.getWarnings().empty()) {
        cout << "Aucun avertissement enregistre.\n";
        return;
    }
    for(size_t i = 0; i < e.getWarnings().size(); i++) {
        cout << i+1 << ". " << e.getWarnings()[i] << "\n";
    }
}

// ============================================
// ENSEIGNANT: AJOUTER NOTE
// ============================================

void Etablissement::enseignantAjouterNote(Enseignant &e) {
    if(e.getModules().empty()) {
        cout << "\nVous n'avez aucun module assigne.\n";
        return;
    }

    int idMod;
    if(e.getModules().size() == 1) {
        idMod = e.getModules()[0];
    } else {
        cout << "\nVos modules:\n";
        for(auto &m : e.getModules()) {
            for(auto &mod : modules) {
                if(mod.getId() == m) {
                    cout << m << ". " << mod.getNom() << "\n";
                    break;
                }
            }
        }
        cout << "Choisir le module: ";
        cin >> idMod;

        bool found = false;
        for(auto &m : e.getModules()) {
            if(m == idMod) {
                found = true;
                break;
            }
        }
        if(!found) {
            cout << "\nModule invalide.\n";
            return;
        }
    }

    int idEtu;
    float note;
    cout << "\nID Etudiant: ";
    cin >> idEtu;
    cout << "Note: ";
    cin >> note;
    ajouterNote(idEtu, idMod, note);
}

// ============================================
// ENSEIGNANT: GERER SES MODULES
// ============================================

void Etablissement::enseignantGererModules(Enseignant &e) {
    int choix;
    do {
        cout << "\n--- Gestion de mes modules ---\n";
        cout << "1. Consulter mes modules\n";
        cout << "2. Ajouter un module\n";
        cout << "3. Supprimer un module\n";
        cout << "0. Retour\n" << endl;
        cin >> choix;

        switch(choix) {
            case 1: {
                cout << "\n--- Mes modules ---\n";
                if(e.getModules().empty()) {
                    cout << "Aucun module assigne.\n";
                } else {
                    for(auto &idMod : e.getModules()) {
                        for(auto &m : modules) {
                            if(m.getId() == idMod) {
                                cout << idMod << ". " << m.getNom() << "\n";
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case 2: {
                cout << "\n--- Modules disponibles ---\n";
                for(auto &m : modules) {
                    cout << m.getId() << ". " << m.getNom() << "\n";
                }
                int idMod;
                cout << "\nID du module a ajouter: ";
                cin >> idMod;

                bool existe = false;
                for(auto &m : modules) {
                    if(m.getId() == idMod) {
                        existe = true;
                        break;
                    }
                }
                if(!existe) {
                    cout << "\nModule introuvable.\n";
                } else {
                    e.ajouterModule(idMod);
                }
                break;
            }
            case 3: {
                if(e.getModules().empty()) {
                    cout << "\nVous n'avez aucun module a supprimer.\n";
                    break;
                }
                cout << "\n--- Mes modules ---\n";
                for(auto &idMod : e.getModules()) {
                    for(auto &m : modules) {
                        if(m.getId() == idMod) {
                            cout << idMod << ". " << m.getNom() << "\n";
                            break;
                        }
                    }
                }
                int idMod;
                cout << "\nID du module a supprimer: ";
                cin >> idMod;
                e.supprimerModule(idMod);
                break;
            }
        }
    } while(choix != 0);
}

// ============================================
// ADMIN: AJOUTER ETUDIANT
// ============================================

void Etablissement::adminAjouterEtudiant() {
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
    cin >> groupe;

    for(auto &g : groupes) { 
        if(g.getId() == groupe) { 
            existe = true; 
            break; 
        } 
    }
    if(!existe) { 
        cout << "\nGroupe introuvable.\n"; 
        return; 
    }

    for (const auto& e : etudiants) { 
        if (e.getLogin() == login) { 
            deja = true; 
            break; 
        } 
    }
    for (const auto& ens : enseignants) { 
        if (ens.getLogin() == login) { 
            deja = true; 
            break; 
        } 
    }
    for (const auto& a : admins) { 
        if (a.getLogin() == login) { 
            deja = true; 
            break; 
        } 
    }

    if(deja) {
        cout << "\nLogin existe deja.\n";
    } else {
        etudiants.emplace_back(
            !etudiants.size() ? 1 : etudiants.back().getId() + 1, 
            nom, prenom, login, mdp, groupe
        );
        cout << "\nEtudiant ajoute avec succes.\n";
        for(auto &g : groupes) { 
            if(g.getId() == groupe) { 
                g.incrementer(); 
                break; 
            } 
        }
    }
}

// ============================================
// ADMIN: GERER ABSENCES D'UN ETUDIANT
// ============================================

void Etablissement::adminGererAbsences() {
    int idEtu;
    cout << "\nID de l'etudiant: ";
    cin >> idEtu;

    Etudiant* etu = nullptr;
    for(auto &e : etudiants) {
        if(e.getId() == idEtu) {
            etu = &e;
            break;
        }
    }

    if(!etu) {
        cout << "\nEtudiant introuvable.\n";
        return;
    }

    int choix;
    do {
        cout << "\n--- Gestion des absences de " << etu->getNom() << " " << etu->getPrenom() << " ---\n";
        cout << "1. Consulter les absences\n";
        cout << "2. Ajouter une absence\n";
        cout << "3. Supprimer une absence\n";
        cout << "0. Retour\n" << endl;
        cin >> choix;

        switch(choix) {
            case 1: {
                cout << "\n--- Absences ---\n";
                if(etu->getAbsences().empty()) {
                    cout << "Aucune absence enregistree.\n";
                } else {
                    for(size_t i = 0; i < etu->getAbsences().size(); i++) {
                        cout << i+1 << ". " << etu->getAbsences()[i] << "\n";
                    }
                }
                break;
            }
            case 2: {
                string date, moduleStr;
                int idModule;
                cout << "\nDate (JJ/MM/AAAA): ";
                cin >> date;

                cout << "Modules disponibles:\n";
                for(auto &m : modules) {
                    cout << m.getId() << ". " << m.getNom() << "\n";
                }
                cout << "ID Module: ";
                cin >> idModule;

                bool existe = false;
                for(auto &m : modules) {
                    if(m.getId() == idModule) {
                        moduleStr = m.getNom();
                        existe = true;
                        break;
                    }
                }

                if(!existe) {
                    cout << "\nModule introuvable.\n";
                } else {
                    string absence = date + ";" + moduleStr;
                    etu->ajouterAbsence(absence);
                    cout << "\nAbsence ajoutee.\n";
                }
                break;
            }
            case 3: {
                if(etu->getAbsences().empty()) {
                    cout << "\nAucune absence a supprimer.\n";
                    break;
                }
                cout << "\n--- Absences ---\n";
                for(size_t i = 0; i < etu->getAbsences().size(); i++) {
                    cout << i+1 << ". " << etu->getAbsences()[i] << "\n";
                }
                int index;
                cout << "\nNumero de l'absence a supprimer: ";
                cin >> index;
                if(index > 0 && index <= etu->getAbsences().size()) {
                    etu->supprimerAbsence(index - 1);
                    cout << "\nAbsence supprimee.\n";
                } else {
                    cout << "\nNumero invalide.\n";
                }
                break;
            }
        }
    } while(choix != 0);
}

// ============================================
// ADMIN: GERER WARNINGS D'UN ETUDIANT
// ============================================

void Etablissement::adminGererWarnings() {
    int idEtu;
    cout << "\nID de l'etudiant: ";
    cin >> idEtu;

    Etudiant* etu = nullptr;
    for(auto &e : etudiants) {
        if(e.getId() == idEtu) {
            etu = &e;
            break;
        }
    }

    if(!etu) {
        cout << "\nEtudiant introuvable.\n";
        return;
    }

    int choix;
    do {
        cout << "\n--- Gestion des avertissements de " << etu->getNom() << " " << etu->getPrenom() << " ---\n";
        cout << "1. Consulter les avertissements\n";
        cout << "2. Ajouter un avertissement\n";
        cout << "3. Supprimer un avertissement\n";
        cout << "0. Retour\n" << endl;
        cin >> choix;

        switch(choix) {
            case 1: {
                cout << "\n--- Avertissements ---\n";
                if(etu->getWarnings().empty()) {
                    cout << "Aucun avertissement enregistre.\n";
                } else {
                    for(size_t i = 0; i < etu->getWarnings().size(); i++) {
                        cout << i+1 << ". " << etu->getWarnings()[i] << "\n";
                    }
                }
                break;
            }
            case 2: {
                string date, raison;
                cout << "\nDate (JJ/MM/AAAA): ";
                cin >> date;
                cout << "Raison: ";
                cin.ignore();
                getline(cin, raison);

                string warning = date + ";" + raison;
                etu->ajouterWarning(warning);
                cout << "\nAvertissement ajoute.\n";
                break;
            }
            case 3: {
                if(etu->getWarnings().empty()) {
                    cout << "\nAucun avertissement a supprimer.\n";
                    break;
                }
                cout << "\n--- Avertissements ---\n";
                for(size_t i = 0; i < etu->getWarnings().size(); i++) {
                    cout << i+1 << ". " << etu->getWarnings()[i] << "\n";
                }
                int index;
                cout << "\nNumero de l'avertissement a supprimer: ";
                cin >> index;
                if(index > 0 && index <= etu->getWarnings().size()) {
                    etu->supprimerWarning(index - 1);
                    cout << "\nAvertissement supprime.\n";
                } else {
                    cout << "\nNumero invalide.\n";
                }
                break;
            }
        }
    } while(choix != 0);
}

// ============================================
// HELPER METHOD: AJOUTER NOTE
// ============================================

void Etablissement::ajouterNote(int idEtudiant, int idModule, float valeur) {
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
    
    if(valeur > 20 || valeur < 0) {
        cout << "\nNote invalide.\n";
        return;
    }
    
    notes.emplace_back(idEtudiant, idModule, valeur);
    cout << "\nNote ajoutee avec succes.\n";
}