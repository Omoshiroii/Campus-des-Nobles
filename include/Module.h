#ifndef MODULE_H
#define MODULE_H

#include <string>

using namespace std;

class Module {
private:
    int id;
    string nom;

public:
    // Constructor
    Module(int i, string n);
    
    // Destructor
    ~Module();
    
    // Getters
    int getId() const;
    string getNom() const;
    
    // Methods
    string afficher() const;
};

#endif // MODULE_H