module;
import std;

export module exo2;

export namespace exo2 {

    class Vector {
    public:
        Vector(double x, double y, double z)
            : mX{x}, mY{y}, mZ{z} {
            std::println("Création d'un objet Vector");
        }

        // Accesseurs
        auto GetX() const { return mX; }
        auto GetY() const { return mY; }
        auto GetZ() const { return mZ; }

        // Modificateurs
        void SetX(auto x) { mX = x; }
        void SetY(auto y) { mY = y; }
        void SetZ(auto z) { mZ = z; }

        void Homothety(auto k) {
            mX *= k;
            mY *= k;
            mZ *= k;
        }

        void Sum(const auto v) {
            mX += v.mX;
            mY += v.mY;
            mZ += v.mZ;
        }

        // Retourne "(x,y,z)" avec deux décimales
        auto ToString() const {
            return std::format("({:.2f},{:.2f},{:.2f})", mX, mY, mZ);
        }

    private:
        // Coordonnées du vecteur
        double mX;
        double mY;
        double mZ;
    };
    // Exemple de classe utilisée dans la fonction main()
    class Application {
    public:
        // Tout le code de l'exercice doit être dans ce constructeur
        Application() = default;
    };

}