# Guide Utilisateur - Campus des Nobles

## 🎓 Introduction

Bienvenue dans le système de gestion Campus des Nobles. Ce guide vous aidera à utiliser toutes les fonctionnalités du système selon votre rôle.

## 🚀 Démarrage

### Lancement du Programme
```bash
./campus_nobles
```

### Connexion

Au démarrage, vous verrez :
```
- - - - - - - - - - - - - - - - -
- - - Bienvenue dans l'EMSI - - -
- - - - - - - - - - - - - - - - -

Nom d'utilisateur: 
```

**Compte administrateur par défaut :**
- Nom d'utilisateur : `abcd`
- Mot de passe : `1234`

**Pour quitter :** Entrer `0` comme nom d'utilisateur

---

## 👨‍🎓 Interface Étudiant

### Menu Principal
```
1. Consulter mes donnees
2. Exporter mes notes
3. Consulter mes absences
4. Consulter mes avertissements
5. Deconnexion
0. Quitter
```

### 1. Consulter mes données
Affiche vos informations personnelles :
- ID
- Nom et Prénom
- Groupe

### 2. Exporter mes notes
Génère un fichier CSV `notes_[ID].csv` contenant toutes vos notes.

**Exemple de sortie :**
```csv
Module;Note
1;15.5
2;17.0
```

### 3. Consulter mes absences
Liste toutes vos absences enregistrées.

**Format d'affichage :**
```
--- Mes absences ---
1. 25/12/2024;POO
2. 26/12/2024;Developpement Web
```

### 4. Consulter mes avertissements
Liste tous vos avertissements.

**Format d'affichage :**
```
--- Mes avertissements ---
1. 24/12/2024;Retard injustifie
2. 27/12/2024;Comportement inapproprie
```

---

## 👨‍🏫 Interface Enseignant

### Menu Principal
```
1. Consulter mes donnees
2. Ajouter une note
3. Supprimer une note
4. Consulter toutes les notes
5. Gerer mes modules
6. Deconnexion
0. Quitter
```

### 1. Consulter mes données
Affiche :
- ID, Nom, Prénom
- Salaire
- Modules assignés

### 2. Ajouter une note

**Si vous avez un seul module :**
```
ID Etudiant: 1
Note: 15.5
```

**Si vous avez plusieurs modules :**
```
Vos modules:
1. POO
2. Developpement Web
Choisir le module: 1

ID Etudiant: 1
Note: 15.5
```

**Validations :**
- L'étudiant doit exister
- La note doit être entre 0 et 20

### 3. Supprimer une note
Même processus que l'ajout, mais supprime la note existante.

### 4. Consulter toutes les notes
Affiche toutes les notes pour chacun de vos modules :
```
Module: POO (ID: 1)
  Etudiant 1 | Note 15.5
  Etudiant 2 | Note 14.0

Module: Developpement Web (ID: 2)
  Etudiant 1 | Note 17.0
  Aucune note enregistree.
```

### 5. Gérer mes modules

**Sous-menu :**
```
1. Consulter mes modules
2. Ajouter un module
3. Supprimer un module
0. Retour
```

**Ajouter un module :**
1. Liste des modules disponibles s'affiche
2. Entrez l'ID du module à ajouter
3. Le système vérifie que vous ne l'avez pas déjà

**Supprimer un module :**
1. Vos modules s'affichent
2. Entrez l'ID du module à supprimer

---

## 👨‍💼 Interface Administrateur

### Menu Principal
```
1. Consulter mes donnes
2. Ajouter un etudiant
3. Ajouter un enseignant
4. Supprimer un etudiant
5. Supprimer un enseignant
6. Modifier un etudiant
7. Modifier un enseignant
8. Exporter etudiants par groupe
9. Exporter enseignants
10. Ajouter un groupe
11. Supprimer un groupe
12. Consulter toutes les modules
13. Ajouter un module
14. Supprimer un module
15. Gerer absences d'un etudiant
16. Gerer avertissements d'un etudiant
17. Deconnexion
0. Quitter
```

### 2. Ajouter un étudiant

**Processus :**
```
Nom: Zerrad
Prenom: Taha
Login: taha123
Mot de passe: pass123
Groupe: 1
```

**Validations :**
- Le login doit être unique
- Le groupe doit exister
- L'effectif du groupe s'incrémente automatiquement

### 3. Ajouter un enseignant

**Processus :**
```
Nom: Mahfoud
Prenom: Rania
ID de module: 1
Login: rania_prof
Mot de passe: prof123
Salaire: 8000
```

**Validations :**
- Le module doit exister
- Le login doit être unique

### 6. Modifier un étudiant

**Sous-menu de modification :**
```
1. Modifier nom
2. Modifier prenom
3. Modifier login
4. Modifier mot de passe
5. Modifier groupe
0. Retour
```

**Pour changer de groupe :**
- L'effectif de l'ancien groupe décrémente
- L'effectif du nouveau groupe incrémente

### 8. Exporter étudiants par groupe

Génère `etudiants_groupe_[N].csv` :
```csv
sep=;
ID;Nom;Prenom;Groupe
1;Zerrad;Taha;1
2;Benhnich;Salsabil;1
```

### 9. Exporter enseignants

Génère `enseignants.csv` :
```csv
sep=;
ID;Nom;Prenom
101;Mahfoud;Rania
102;Al Fezghari;Badr
```

### 10-11. Gestion des groupes

**Ajouter un groupe :**
- Crée automatiquement le prochain ID
- Effectif initial : 0

**Supprimer un groupe :**
- ⚠️ ATTENTION : Supprime aussi tous les étudiants du groupe et leurs notes

### 12-14. Gestion des modules

**Consulter les modules :**
```
1. POO
2. Developpement Web
3. Communication Pro
```

**Ajouter un module :**
```
Nom de module: Base de Donnees
```

**Supprimer un module :**
- Le module est retiré de tous les enseignants qui l'avaient

### 15. Gérer absences d'un étudiant

**Processus :**
```
ID de l'etudiant: 1

--- Gestion des absences de Zerrad Taha ---
1. Consulter les absences
2. Ajouter une absence
3. Supprimer une absence
0. Retour
```

**Ajouter une absence :**
```
Date (JJ/MM/AAAA): 28/12/2024
Modules disponibles:
1. POO
2. Developpement Web
3. Communication Pro
ID Module: 1
```

### 16. Gérer avertissements d'un étudiant

Même processus que les absences, mais avec une raison textuelle :
```
Date (JJ/MM/AAAA): 28/12/2024
Raison: Retard de 30 minutes
```

---

## 💡 Conseils et Bonnes Pratiques

### Pour tous les utilisateurs
- ✅ Déconnectez-vous toujours après utilisation (option Déconnexion)
- ✅ Vérifiez vos données après chaque modification
- ✅ Les fichiers CSV sont dans le dossier `exports/`

### Pour les enseignants
- ✅ Vérifiez l'ID de l'étudiant avant d'ajouter une note
- ✅ Les notes vont de 0 à 20
- ✅ Gérez vos modules régulièrement pour rester à jour

### Pour les administrateurs
- ⚠️ La suppression d'un groupe supprime TOUS ses étudiants
- ⚠️ La suppression d'un module le retire de tous les enseignants
- ✅ Exportez régulièrement les données
- ✅ Vérifiez les logins pour éviter les doublons

---

## ❓ FAQ

**Q : Que se passe-t-il si j'oublie mon mot de passe ?**  
R : Contactez un administrateur pour le réinitialiser via l'option "Modifier".

**Q : Puis-je avoir plusieurs modules en tant qu'enseignant ?**  
R : Oui ! Utilisez "Gérer mes modules" pour en ajouter plusieurs.

**Q : Les données sont-elles sauvegardées automatiquement ?**  
R : Oui, toutes les modifications sont sauvegardées à la sortie du programme.

**Q : Où sont stockés les fichiers exportés ?**  
R : Dans le répertoire `exports/` à la racine du projet.

**Q : Peut-on supprimer une note ?**  
R : Oui, les enseignants peuvent supprimer les notes de leurs modules.

---

## 🐛 Signaler un Bug

Si vous rencontrez un problème, notez :
1. Votre rôle (Étudiant/Enseignant/Admin)
2. L'action que vous tentiez
3. Le message d'erreur (si présent)
4. Les étapes pour reproduire

Contactez l'équipe de développement avec ces informations.