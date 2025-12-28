✅ Tous les fichiers doivent exister même s'ils sont vides
✅ Le code crée automatiquement les 3 modules et 1 admin s'ils n'existent pas
✅ Login par défaut : abcd / Mot de passe : 1234
✅ Pour quitter au login : entrer 0 comme nom d'utilisateur
✅ Le séparateur est toujours ; (point-virgule)
✅ Pour les listes (absences, warnings, modules), utiliser | (pipe)


/*
for an admin
exemple (Format : id;nom;prenom;login;motDePasse;salaire)
201;Test;Admin;abcd;1234;5000
*/

/*
for enseignants
exemple: (Format : id;nom;prenom;modules;login;motDePasse;salaire)
101;Mahfoud;Rania;1|2;rania_prof;prof123;8000
102;Al Fezghari;Badr;3;badr_prof;prof456;7500
103;Doe;John;1;john_prof;prof789;9000
*/

/* 

for etudiants:

exemple (Format : id;nom;prenom;login;motDePasse;groupe;absences;warnings)
1;Zerrad;Taha;taha123;pass1;1;25/12/2024;POO|26/12/2024;Developpement Web;24/12/2024;Retard injustifie
2;Benhnich;Salsabil;salsa456;pass2;1;;
3;El Attabi;Oussama;oussama789;pass3;2;27/12/2024;Communication Pro;

Explications :

Absences : Séparées par |, format date;module
Warnings : Séparés par |, format date;raison
Si pas d'absences ou warnings, laisser vide (;)
*/

/* 
for groupes
exemple (Format : id;effectif)
1;0
2;0
3;0
*/

/*
for modules 
exemple (Format : id;nom)
1;POO
2;Developpement Web
3;Communication Pro
*/

/*
for notes 
exemple (Format : idEtudiant;idModule;valeur)
1;1;15.5
1;2;17.0
2;1;14.0
2;2;16.5
3;3;12.0
*/