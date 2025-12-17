#include <iostream>
#include "M_Admin.h"

using namespace std;

M_Admin::M_Admin(){}

void M_Admin::menuAdmin(){
    int choice;
    bool back = false;

    while(!back){
        cout << "\n--- Menu Administrateur ---\n";
        cout << "1. Login\n";
        cout << "2. Consultation generale des absences\n";
        cout << "3. Recherche\n";
        cout << "4. Appeler les parents\n";
        cout << "5. Retour\n";
        cout << "Choix : ";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "Login administrateur...\n";
                break;
            case 2:
                cout << "Consultation generale des absences...\n";
                break;
            case 3:
                cout << "Recherche...\n";
                break;
            case 4:
                cout << "Appel des parents...\n";
                break;
            case 5:
                back = true;
                break;
            default:
                cout << "Choix invalide.\n";
        }
    }
}
