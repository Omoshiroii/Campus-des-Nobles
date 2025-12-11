#include "menu.h"
#include <iostream>

Menu::Menu(Etablissement &e) : ecole(e) {}

void Menu::menuEtudiant() {
    std::cout << "--- Menu Etudiant ---\n";
    std::cout << "Enter student ID: ";
    int id; std::cin >> id;
    auto p = ecole.rechercherParId(id);
    if (!p) { std::cout << "Not found.\n"; return; }
    auto etu = std::dynamic_pointer_cast<Etudiant>(p);
    if (!etu) { std::cout << "Not an Etudiant.\n"; return; }
    etu->afficher();
    std::cout << "Press Enter to continue..."; std::cin.ignore(); std::cin.get();
}

void Menu::menuProfesseur() {
    std::cout << "--- Menu Professeur ---\n";
    std::cout << "1) Register grade to student\n2) Show all persons\n0) Back\nChoice: ";
    int c; std::cin >> c;
    if (c == 1) {
        int sid, mid; double val;
        std::cout << "Student ID: "; std::cin >> sid;
        std::cout << "Module ID: "; std::cin >> mid;
        std::cout << "Value: "; std::cin >> val;
        if (ecole.enregistrerNote(sid, mid, val)) std::cout << "Note registered.\n";
        else std::cout << "Failed to register note.\n";
    } else if (c == 2) {
        ecole.afficherTout();
    }
}

void Menu::run() {
    while (true) {
        std::cout << "\n=== School Management Prototype ===\n";
        std::cout << "1) Etudiant\n2) Professeur\n3) Show all\n0) Quit\nChoice: ";
        int ch; std::cin >> ch;
        if (ch == 0) break;
        switch (ch) {
            case 1: menuEtudiant(); break;
            case 2: menuProfesseur(); break;
            case 3: ecole.afficherTout(); break;
            default: std::cout << "Invalid\n"; break;
        }
    }
}
