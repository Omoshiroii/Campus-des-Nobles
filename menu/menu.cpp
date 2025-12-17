#include <iostream>
#include "menu.h"
#include "M_formateur.h"
#include "M_etudiant.h"
#include "M_Admin.h"

using namespace std;

Menu::Menu(){}
Menu::~Menu(){}

void Menu::start(){
    int choice;
    bool running = true;
    
    while(running){
        cout << "\n------- Bienvenue dans le Campus des Nobles -------\n";
        cout << "1. Formateur\n";
        cout << "2. Etudiant\n";
        cout << "3. Administrateur\n";
        cout << "4. Quitter\n";
        cout << "Votre choix : ";
        cin >> choice;
        
        switch(choice){
            case 1: {
                M_formateur menuF;
                menuF.menuformateur();
                break;
            }
            case 2: {
                M_etudiant menuE;
                menuE.menuEtudiant();
                break;
            }
            case 3: {
                M_Admin menuA;
                menuA.menuAdmin();
                break;
            }
            case 4:
                running = false;
                cout << "Au revoir\n";
                break;
            default:
                cout << "Choix invalide.\n";
        }
    }
}

int main() {
    Menu menu;
    menu.start();
    return 0;
}