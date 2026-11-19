module;
// Import rapide de la bibliothèque standard
import std;

// Nommage et exportation de ce module
export module exo1;

// On met toutes les classes du module dans un espace de nom
// ayant le même nom que le module pour plus de clarté et éviter
// les conflits de nommage.
// On exporte la totalité des classe de l'espace de nom.
export namespace exo1 {


    // Exemple de classe utilisée dans la fonction main()
    class Application {
    public:
        // Tout le code de l'exercice doit être dans ce constructeur
        Application() = default;
    };

}