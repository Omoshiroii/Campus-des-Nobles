# Architecture du Projet Campus des Nobles

## 🏗️ Vue d'Ensemble

Le projet utilise une architecture orientée objet avec une hiérarchie de classes bien définie et une séparation claire entre les données, la logique métier et l'interface utilisateur.

## 📐 Diagramme de Classes
```
                    Personne (abstract)
                         |
        +----------------+----------------+
        |                                 |
    Etudiant                          Employe
                                          |
                                  +-------+-------+
                                  |               |
                            Enseignant    Administratif
```

## 🗂️ Classes Principales

### **Personne** (Classe Abstraite)
Classe de base pour tous les utilisateurs du système.

**Attributs protégés :**
- `int id` - Identifiant unique
- `string nom` - Nom de famille
- `string prenom` - Prénom
- `string login` - Identifiant de connexion
- `string motDePasse` - Mot de passe

**Méthodes virtuelles pures :**
- `virtual string getPermissions() const = 0`
- `virtual string afficher() const = 0`

### **Etudiant** (hérite de Personne)
Représente un étudiant.

**Attributs privés :**
- `int groupe` - Numéro du groupe
- `vector<string> absences` - Liste des absences (format: "date;module")
- `vector<string> warnings` - Liste des avertissements (format: "date;raison")

**Méthodes principales :**
- `void ajouterAbsence(const string &absence)`
- `void supprimerAbsence(int index)`
- `void ajouterWarning(const string &warning)`
- `void supprimerWarning(int index)`

### **Employe** (hérite de Personne)
Classe de base pour les employés.

**Attributs protégés :**
- `string poste` - Poste occupé
- `double salaire` - Salaire mensuel

### **Enseignant** (hérite de Employe)
Représente un enseignant.

**Attributs privés :**
- `vector<int> modules` - Liste des IDs de modules enseignés

**Méthodes principales :**
- `void ajouterModule(int idModule)`
- `void supprimerModule(int idModule)`

### **Administratif** (hérite de Employe)
Représente un membre du personnel administratif.

**Permissions :** Accès complet au système

### **Classes Utilitaires**

#### **Note**
- `int idEtudiant`
- `int idModule`
- `float valeur` (0-20)

#### **Module**
- `int id`
- `string nom`

#### **Groupe**
- `int id`
- `int effectif`

### **Etablissement**
Classe centrale gérant toutes les opérations.

**Responsabilités :**
- Chargement/Sauvegarde des données
- Authentification des utilisateurs
- Opérations CRUD sur toutes les entités
- Gestion des permissions

## 🔄 Flux de Données
```
Fichiers .txt ──► Etablissement::charger() ──► Vecteurs en mémoire
                                                      │
                                                      ▼
                                              Opérations métier
                                                      │
                                                      ▼
Fichiers .txt ◄── Etablissement::sauvegarder() ◄── Vecteurs modifiés
```

## 📦 Organisation des Fichiers

### **include/** - Headers (.h)
Déclarations des classes et méthodes publiques.

### **src/** - Sources (.cpp)
Implémentations des méthodes.

### **data/** - Base de données
Fichiers texte pour la persistance.

### **exports/** - Exports
Fichiers CSV générés par le système.

## 🔐 Système de Permissions

| Rôle          | Permissions                                    |
|---------------|------------------------------------------------|
| ETUDIANT      | Lecture de ses données, export notes          |
| ENSEIGNANT    | Gestion notes de ses modules, gestion modules  |
| ADMIN         | Accès total au système                         |

## 🎯 Principes de Conception

### **Encapsulation**
- Attributs privés/protégés
- Accès via getters/setters

### **Héritage**
- Hiérarchie Personne → Etudiant/Employe
- Réutilisation du code

### **Polymorphisme**
- Méthodes virtuelles (`getPermissions()`, `afficher()`)
- Dynamic casting pour accès aux méthodes spécifiques

### **Séparation des Responsabilités**
- Classes entités : Données + comportements basiques
- Etablissement : Logique métier
- main.cpp : Interface utilisateur

## 🔧 Extensibilité

Le système est conçu pour être facilement extensible :

1. **Nouveaux types d'utilisateurs** : Créer une nouvelle classe héritant de Personne
2. **Nouvelles fonctionnalités** : Ajouter des méthodes à Etablissement
3. **Nouveaux attributs** : Modifier les classes et les méthodes d'affichage

## 📈 Évolutions Futures Possibles

- Migration vers SQLite/MySQL
- Interface graphique (Qt/wxWidgets)
- API REST pour application web/mobile
- Système de notifications
- Génération de rapports PDF
- Authentification sécurisée (hachage des mots de passe)