module;
import std;

export module exo3;

export namespace exo3 {
    struct Vector {
        double x{};
        double y{};
        double z{};

        auto ToString() const {
            return std::format("({:.2f},{:.2f},{:.2f})", x, y, z);
        }

        constexpr Vector operator+(const Vector& other) const {
            return Vector{x + other.x, y + other.y, z + other.z};
        }

        constexpr Vector operator*(const double k) const {
            return Vector{x * k, y * k, z * k};
        }

        friend constexpr bool operator==(const Vector& a, const Vector& b) {
            return a.x == b.x && a.y == b.y && a.z == b.z;
        }

        constexpr double LengthSquared() const {
            return x * x + y * y + z * z;
        }
    };

    consteval Vector CreateUnitX() {
        return Vector{1.0, 0.0, 0.0};
    }
}
