# Campus des Nobles - Système de Gestion Scolaire

## 📋 Description

Campus des Nobles est un système de gestion scolaire développé en C++ utilisant la Programmation Orientée Objet (POO). Ce projet permet la gestion complète d'un établissement éducatif incluant les étudiants, enseignants, modules, notes, absences et avertissements.

## 👥 Équipe de Développement

- **Taha Zerrad**
- **Salsabil Benhnich**
- **Oussama El Attabi**
- **Rania Mahfoud**
- **Badr Al Fezghari**

## ✨ Fonctionnalités

### Pour les Étudiants
- ✅ Consulter ses informations personnelles
- ✅ Exporter ses notes en CSV
- ✅ Consulter ses absences
- ✅ Consulter ses avertissements

### Pour les Enseignants
- ✅ Consulter ses informations et modules assignés
- ✅ Ajouter/Supprimer des notes pour ses modules
- ✅ Consulter toutes les notes de ses modules
- ✅ Gérer ses modules (ajouter/supprimer/consulter)

### Pour les Administratifs
- ✅ Gérer les étudiants (ajouter/supprimer/modifier)
- ✅ Gérer les enseignants (ajouter/supprimer/modifier)
- ✅ Gérer les groupes (ajouter/supprimer)
- ✅ Gérer les modules (ajouter/supprimer/consulter)
- ✅ Gérer les absences des étudiants
- ✅ Gérer les avertissements des étudiants
- ✅ Exporter les données (étudiants par groupe, enseignants)

## 🚀 Installation et Compilation

### Prérequis
- Compilateur C++ (g++ recommandé)
- C++11 ou supérieur
- Make (optionnel)

### Compilation avec Make
```bash

### Compilation manuelle
```bash

### Exécution
```bash

## 🔑 Connexion par Défaut

**Administrateur :**
- Nom d'utilisateur : `abcd`
- Mot de passe : `1234`

**Quitter le programme au login :**
- Entrer `0` comme nom d'utilisateur

## 📁 Structure du Projet
CampusDesNobles/
├── include/          # Fichiers d'en-tête (.h)
├── src/              # Fichiers source (.cpp)
├── data/             # Base de données (fichiers .txt)
├── exports/          # Fichiers exportés (.csv)
└──docs/             # Documentation


## 📊 Base de Données

Le système utilise des fichiers texte (.txt) pour stocker les données :
- `etudiants.txt` - Informations des étudiants
- `enseignants.txt` - Informations des enseignants
- `administratifs.txt` - Informations des administratifs
- `notes.txt` - Notes des étudiants
- `modules.txt` - Modules de cours
- `groupes.txt` - Groupes d'étudiants

## 📖 Documentation

- [Architecture du Projet](ARCHITECTURE.md)
- [Guide Utilisateur](USER_GUIDE.md)
- [Référence API](API_REFERENCE.md)

## 🐛 Bugs Connus

Aucun bug majeur identifié pour le moment.

## 📝 License

Projet académique - EMSI 2024

## 📧 Contact

Pour toute question, contactez l'équipe de développement.
