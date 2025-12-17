#include <iostream>
#include "M_etudiant.h"

using namespace std;

M_etudiant::M_etudiant() {}

void M_etudiant::menuEtudiant() {
    int choice;
    bool back = false;

    while(!back) {
        cout << "\n--- Menu Etudiant ---\n";
        cout << "1. Login\n";
        cout << "2. Consulter notes\n";
        cout << "3. Consulter absences\n";
        cout << "4. Inscription\n";
        cout << "5. Retour\n";
        cout << "Choix : ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Login...\n";
                break;
            case 2:
                cout << "Notes...\n";
                break;
            case 3:
                cout << "Absences...\n";
                break;
            case 4:
                cout << "Inscription...\n";
                break;
            case 5:
                back = true;
                break;
            default:
                cout << "Choix invalide\n";
        }
    }
}
