#ifndef MENU_H
#define MENU_H

#include "Etablissement.h"
#include <memory>

class Menu {
private:
    Etablissement &ecole;

    void menuEtudiant();
    void menuProfesseur();
public:
    explicit Menu(Etablissement &e);
    void run();
};

#endif // MENU_H
