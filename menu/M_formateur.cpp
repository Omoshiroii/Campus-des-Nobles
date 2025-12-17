#include <iostream>
#include "M_formateur.h"

using namespace std;

M_formateur::M_formateur() {}

void M_formateur::menuformateur(){
    int choice;
    bool back = false;

    while(!back){
        cout << "\n--- Menu Formateur ---\n";
        cout << "1. Login\n";
        cout << "2. Saisir une note\n";
        cout << "3. Modifier une note\n";
        cout << "4. Enregistrer une absence\n";
        cout << "5. Consulter les absences\n";
        cout << "6. Retour\n";
        cout << "Choix : ";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "Login formateur...\n";
                break;
            case 2:
                cout << "Saisie de note...\n";
                break;
            case 3:
                cout << "Modification de note...\n";
                break;
            case 4:
                cout << "Enregistrement absence...\n";
                break;
            case 5:
                cout << "Consultation absence...\n";
                break;
            case 6:
                back = true;
                break;
            default:
                cout << "Choix invalide.\n";
        }
    }
}
