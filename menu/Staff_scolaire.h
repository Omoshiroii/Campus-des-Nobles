#ifndef STAFF_SCOLAIRE_H
#define STAFF_SCOLAIRE_H

#include "Employe.h"
#include <string>

using namespace std;

class Staff_scolaire : public Employe {
private:
    string fonction;
    bool estPermanent; // is the staff permanent or not (ex: CDD/CDI)

public:
    Staff_scolaire(string n, string p, int i, string dep, string fonc, bool perm);
    ~Staff_scolaire();

    void saisir_note() override;
    void enregistrement_absence() override;
    void afficher() override;
};

#endif // STAFF_SCOLAIRE_H
