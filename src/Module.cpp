#include "Module.h"

using namespace std;

Module::Module(int i, string n) 
    : id(i), nom(n) {
}

Module::~Module() {
}

int Module::getId() const {
    return id;
}

string Module::getNom() const {
    return nom;
}

string Module::afficher() const {
    return to_string(id) + ";" + nom;
}