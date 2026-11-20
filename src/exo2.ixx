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

        // Constructeur par recopie
        Vector(const Vector& other)
            : mX{other.mX}, mY{other.mY}, mZ{other.mZ} {
            std::println("Recopie d'un objet Vector");
        }

        // Constructeur de déplacement : l'objet source est mis à 0
        Vector(Vector&& other) noexcept
            : mX{other.mX}, mY{other.mY}, mZ{other.mZ} {
            other.mX = 0.0;
            other.mY = 0.0;
            other.mZ = 0.0;
            std::println("Déplacement d'un objet Vector");
        }

        // Affectation par copie
        Vector& operator=(const Vector& other) {
            mX = other.mX;
            mY = other.mY;
            mZ = other.mZ;
            std::println("Affectation par copie d'un objet Vector");
            return *this;
        }

        // Affectation par déplacement : l'objet source est mis à 0
        Vector& operator=(Vector&& other) noexcept {
            mX = other.mX;
            mY = other.mY;
            mZ = other.mZ;
            other.mX = 0.0;
            other.mY = 0.0;
            other.mZ = 0.0;
            std::println("Affectation par déplacement d'un objet Vector");
            return *this;
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

        // Vector passé par copie
        void Sum1(const Vector v) {
            mX += v.mX;
            mY += v.mY;
            mZ += v.mZ;
        }

        // Vector passé par référence
        void Sum2(const Vector& v) {
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

    class Application {
    public:

        Application() {
            auto v1 = Vector{12.34, 34.56, 56.78};
            auto v2 = Vector{1.1, 2.2, 3.3};

            std::println("--- Sum1 (par copie) ---");
            v1.Sum1(v2);
            std::println("--- Sum2 (par référence) ---");
            v1.Sum2(v2);
            std::println("{}", v1.ToString());

            std::println("--- Copie puis déplacement ---");
            auto copy = v1;
            auto moved = std::move(copy);
            std::println("moved = {}, copy = {}", moved.ToString(), copy.ToString());

            std::println("--- Affectations ---");
            auto assigned = Vector{0.0, 0.0, 0.0};
            assigned = moved;
            assigned = std::move(moved);
            std::println("assigned = {}, moved = {}", assigned.ToString(), moved.ToString());
        }
    };

}